//
// Created by Alessio Gjergji on 30/11/24.
//

#include "Utils.h"
#include <random>
#include <stdexcept>
#include <sstream>
#include <iomanip>

// Funzione privata per generare stringhe casuali
namespace {
    std::string generateRandomString(size_t length) {
        const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);

        std::string result;
        for (size_t i = 0; i < length; ++i) {
            result += charset[dist(generator)];
        }
        return result;
    }

    std::string xorEncryptDecrypt(const std::string &data, const std::string &key) {
        std::string result = data;
        for (size_t i = 0; i < data.size(); ++i) {
            result[i] ^= key[i % key.size()];
        }
        return result;
    }
}

std::string Utils::encrypt(const std::string &data, const std::string &key, Algorithm algorithm) {
    if (algorithm == Algorithm::AES || algorithm == Algorithm::XOR) {
        return xorEncryptDecrypt(data, key); // Placeholder per AES
    }
    throw std::invalid_argument("Algoritmo non supportato.");
}

std::string Utils::decrypt(const std::string &data, const std::string &key, Algorithm algorithm) {
    return encrypt(data, key, algorithm); // Simmetrico per XOR
}

std::string Utils::hash(const std::string &data) {
    uint64_t checksum = 0;
    for (char c : data) {
        checksum += static_cast<uint64_t>(c);
    }
    std::ostringstream oss;
    oss << std::hex << checksum;
    return oss.str();
}

std::string Utils::sign(const std::string &data, const std::string &key) {
    return xorEncryptDecrypt(hash(data), key);
}

bool Utils::verify(const std::string &data, const std::string &signature, const std::string &key) {
    return signature == sign(data, key);
}

std::string Utils::generateKey(size_t length) {
    return generateRandomString(length);
}

std::string Utils::generateIV() {
    return generateRandomString(16); // 16-byte IV
}

std::string Utils::generateSalt() {
    return generateRandomString(16);
}

std::string Utils::generateNonce() {
    return generateRandomString(12);
}
