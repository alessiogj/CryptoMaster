#ifndef CRYPTOMASTER_FILEHANDLER_H
#define CRYPTOMASTER_FILEHANDLER_H

#include <string>
#include "Utils.h"

#ifdef _WIN32
#ifdef CRYPTOMASTER_EXPORTS
    #define CRYPTOMASTER_API __declspec(dllexport)
  #else
    #define CRYPTOMASTER_API __declspec(dllimport)
  #endif
#else
#define CRYPTOMASTER_API __attribute__((visibility("default")))
#endif

class CRYPTOMASTER_API FileHandler {
public:
    static bool encryptFile(const std::string &inputFilePath, const std::string &outputFilePath,
                            const std::string &key, Utils::Algorithm algorithm);

    static bool decryptFile(const std::string &inputFilePath, const std::string &outputFilePath,
                            const std::string &key, Utils::Algorithm algorithm);

private:
    static std::string readFile(const std::string &filePath);
    static bool writeFile(const std::string &filePath, const std::string &data);
};

#endif //CRYPTOMASTER_FILEHANDLER_H
