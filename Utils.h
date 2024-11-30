#ifndef CRYPTOMASTER_UTILS_H
#define CRYPTOMASTER_UTILS_H

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

class CRYPTOMASTER_API Utils {
public:
    enum class Algorithm {
        AES,
        XOR
    };

    static std::string encrypt(const std::string &data, const std::string &key, Algorithm algorithm);
    static std::string decrypt(const std::string &data, const std::string &key, Algorithm algorithm);
    static std::string hash(const std::string &data);
    static std::string sign(const std::string &data, const std::string &key);
    static bool verify(const std::string &data, const std::string &signature, const std::string &key);
    static std::string generateKey(size_t length);
    static std::string generateIV();
    static std::string generateSalt();
    static std::string generateNonce();
};

#endif //CRYPTOMASTER_UTILS_H
