#include "CryptoMaster/CryptoMaster.h"
#include <openssl/err.h>
#include <sstream>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

namespace {
    /**
     * Handles OpenSSL errors by printing them to stderr and aborting the program.
     */
    void handleOpenSSLErrors() {
        ERR_print_errors_fp(stderr);
        abort();
    }

    /**
     * Generates random bytes of the specified length.
     *
     * @param length The length of the random bytes to generate.
     * @return The generated random bytes.
     */
    std::string generateRandomBytes(size_t length) {
        std::string randomBytes(length, '\0');
        if (1 != RAND_bytes(reinterpret_cast<unsigned char*>(&randomBytes[0]), length)) {
            handleOpenSSLErrors();
        }
        return randomBytes;
    }
}

/**
 * Encrypts the data using the specified key and algorithm.
 * IV is generated internally and included in the result.
 *
 * @param data The plaintext to encrypt.
 * @param key The encryption key.
 * @param algorithm The encryption algorithm to use (default AES_GCM).
 * @return The encrypted data including IV and authentication tag.
 */
std::string CryptoMaster::encrypt(const std::string &data, const std::string &key, Algorithm algorithm) {
    if (algorithm == Algorithm::AES_GCM) {
        std::string iv = generateRandomBytes(12); // AES-GCM standard IV size
        return iv + aesGcmEncrypt(data, key, iv);
    }
    throw std::invalid_argument("Algorithm not supported.");
}

/**
 * Decrypts the data using the specified key and algorithm.
 * The IV and tag are extracted from the input data.
 *
 * @param data The encrypted data (including IV and tag).
 * @param key The decryption key.
 * @param algorithm The decryption algorithm to use (default AES_GCM).
 * @return The decrypted plaintext.
 */
std::string CryptoMaster::decrypt(const std::string &data, const std::string &key, Algorithm algorithm) {
    if (algorithm == Algorithm::AES_GCM) {
        std::string iv = data.substr(0, 12);
        std::string ciphertext = data.substr(12);
        return aesGcmDecrypt(ciphertext, key, iv);
    }
    throw std::invalid_argument("Algorithm not supported.");
}

/**
 * Encrypts the plaintext using AES-GCM.
 *
 * @param data The plaintext.
 * @param key The encryption key.
 * @param iv The initialization vector (12 bytes).
 * @return The ciphertext including the authentication tag.
 */
std::string CryptoMaster::aesGcmEncrypt(const std::string &data, const std::string &key, const std::string &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleOpenSSLErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr)) {
        handleOpenSSLErrors();
    }

    if (1 != EVP_EncryptInit_ex(ctx, nullptr, nullptr,
                                reinterpret_cast<const unsigned char*>(key.data()),
                                reinterpret_cast<const unsigned char*>(iv.data()))) {
        handleOpenSSLErrors();
    }

    std::string ciphertext(data.size(), '\0');
    int len;

    if (1 != EVP_EncryptUpdate(ctx,
                               reinterpret_cast<unsigned char*>(&ciphertext[0]),
                               &len,
                               reinterpret_cast<const unsigned char*>(data.data()),
                               data.size())) {
        handleOpenSSLErrors();
    }

    int ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx,
                                 reinterpret_cast<unsigned char*>(&ciphertext[0]) + len,
                                 &len)) {
        handleOpenSSLErrors();
    }

    ciphertext_len += len;
    ciphertext.resize(ciphertext_len);

    std::string tag(16, '\0');
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, &tag[0])) {
        handleOpenSSLErrors();
    }

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext + tag;
}

/**
 * Decrypts the ciphertext using AES-GCM.
 *
 * @param data The ciphertext including the authentication tag.
 * @param key The decryption key.
 * @param iv The initialization vector (12 bytes).
 * @return The plaintext.
 */
std::string CryptoMaster::aesGcmDecrypt(const std::string &data, const std::string &key, const std::string &iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handleOpenSSLErrors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr)) {
        handleOpenSSLErrors();
    }

    if (1 != EVP_DecryptInit_ex(ctx, nullptr, nullptr,
                                reinterpret_cast<const unsigned char*>(key.data()),
                                reinterpret_cast<const unsigned char*>(iv.data()))) {
        handleOpenSSLErrors();
    }

    std::string ciphertext = data.substr(0, data.size() - 16);
    std::string tag = data.substr(data.size() - 16);

    std::string plaintext(ciphertext.size(), '\0');
    int len;

    if (1 != EVP_DecryptUpdate(ctx,
                               reinterpret_cast<unsigned char*>(&plaintext[0]),
                               &len,
                               reinterpret_cast<const unsigned char*>(ciphertext.data()),
                               ciphertext.size())) {
        handleOpenSSLErrors();
    }

    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, const_cast<char*>(tag.data()))) {
        handleOpenSSLErrors();
    }

    int plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx,
                                 reinterpret_cast<unsigned char*>(&plaintext[0]) + len,
                                 &len)) {
        handleOpenSSLErrors();
    }

    plaintext_len += len;
    plaintext.resize(plaintext_len);

    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
}

/**
 * Signs the data using the specified key with HMAC-SHA256.
 *
 * @param data The data to sign.
 * @param key The key to use for signing.
 * @return The signature (HMAC-SHA256).
 */
std::string CryptoMaster::sign(const std::string &data, const std::string &key) {
    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int result_len;

    HMAC(EVP_sha256(), key.data(), key.size(),
         reinterpret_cast<const unsigned char*>(data.data()), data.size(),
         result, &result_len);

    return std::string(reinterpret_cast<char*>(result), result_len);
}

/**
 * Verifies the signature of the data using the specified key with HMAC-SHA256.
 *
 * @param data The data to verify.
 * @param signature The signature to verify against.
 * @param key The key to use for verification.
 * @return True if the signature matches, false otherwise.
 */
bool CryptoMaster::verify(const std::string &data, const std::string &signature, const std::string &key) {
    return sign(data, key) == signature;
}

/**
 * Generates a random encryption key of the specified length.
 *
 * @param length The length of the key in bytes (default 32 for AES-256).
 * @return The generated key.
 */
std::string CryptoMaster::generateKey(size_t length) {
    return generateRandomBytes(length);
}