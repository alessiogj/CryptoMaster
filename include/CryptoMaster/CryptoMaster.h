#ifndef CRYPTOMASTER_CRYPTOMASTER_H
#define CRYPTOMASTER_CRYPTOMASTER_H

#include <string>

#ifdef _WIN32
#ifdef CRYPTOMASTER_EXPORTS
    #define CRYPTOMASTER_API __declspec(dllexport)
  #else
    #define CRYPTOMASTER_API __declspec(dllimport)
  #endif
#else
#define CRYPTOMASTER_API __attribute__((visibility("default")))
#endif

/**
 * Utility class for encryption and decryption.
 */
class CRYPTOMASTER_API CryptoMaster {
public:
    /**
     * Supported encryption algorithms.
     */
    enum class Algorithm {
        AES_GCM
    };

    /**
     * Encrypts the data using the specified key and algorithm.
     * IV is generated internally and included in the result.
     * @param data The plaintext to encrypt.
     * @param key The encryption key.
     * @param algorithm The encryption algorithm to use (default AES_GCM).
     * @return The encrypted data including IV and authentication tag.
     */
    static std::string encrypt(const std::string &data, const std::string &key, Algorithm algorithm = Algorithm::AES_GCM);

    /**
     * Decrypts the data using the specified key and algorithm.
     * The IV and tag are extracted from the input data.
     * @param data The encrypted data (including IV and tag).
     * @param key The decryption key.
     * @param algorithm The decryption algorithm to use (default AES_GCM).
     * @return The decrypted plaintext.
     */
    static std::string decrypt(const std::string &data, const std::string &key, Algorithm algorithm = Algorithm::AES_GCM);

    /**
     * Signs the data using the specified key with HMAC-SHA256.
     * @param data The data to sign.
     * @param key The key to use for signing.
     * @return The signature (HMAC-SHA256).
     */
    static std::string sign(const std::string &data, const std::string &key);

    /**
     * Verifies the signature of the data using the specified key with HMAC-SHA256.
     * @param data The data to verify.
     * @param signature The signature to verify against.
     * @param key The key to use for verification.
     * @return True if the signature matches, false otherwise.
     */
    static bool verify(const std::string &data, const std::string &signature, const std::string &key);

    /**
     * Generates a random encryption key of the specified length.
     * @param length The length of the key in bytes (default 32 for AES-256).
     * @return The generated key.
     */
    static std::string generateKey(size_t length = 32);

private:
    /**
     * Encrypts the plaintext using AES-GCM.
     * @param data The plaintext.
     * @param key The encryption key.
     * @param iv The initialization vector (12 bytes).
     * @return The ciphertext including the authentication tag.
     */
    static std::string aesGcmEncrypt(const std::string &data, const std::string &key, const std::string &iv);

    /**
     * Decrypts the ciphertext using AES-GCM.
     * @param data The ciphertext including the authentication tag.
     * @param key The decryption key.
     * @param iv The initialization vector (12 bytes).
     * @return The plaintext.
     */
    static std::string aesGcmDecrypt(const std::string &data, const std::string &key, const std::string &iv);
};

#endif //CRYPTOMASTER_CRYPTOMASTER_H