#ifndef CRYPTOMASTER_FILEHANDLER_H
#define CRYPTOMASTER_FILEHANDLER_H

#include <string>
#include "CryptoMaster.h"

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
    /**
     * Encrypts the content of the input file and writes the result to the output file.
     * @param inputFilePath The path of the input file.
     * @param outputFilePath The path of the output file.
     * @param key The encryption key.
     * @param algorithm The encryption algorithm to use.
     * @return True if the operation was successful, false otherwise.
     */
    static bool encryptFile(const std::string &inputFilePath, const std::string &outputFilePath,
                            const std::string &key, CryptoMaster::Algorithm algorithm);

    /**
     * Decrypts the content of the input file and writes the result to the output file.
     * @param inputFilePath The path of the input file.
     * @param outputFilePath The path of the output file.
     * @param key The decryption key.
     * @param algorithm The decryption algorithm to use.
     * @return True if the operation was successful, false otherwise.
     */
    static bool decryptFile(const std::string &inputFilePath, const std::string &outputFilePath,
                            const std::string &key, CryptoMaster::Algorithm algorithm);

private:
    /**
     * Reads the content of a file.
     * @param filePath The path of the file to read.
     * @return The content of the file.
     */
    static std::string readFile(const std::string &filePath);
    /**
     * Writes data to a file.
     * @param filePath The path of the file to write.
     * @param data The data to write.
     * @return True if the operation was successful, false otherwise.
     */
    static bool writeFile(const std::string &filePath, const std::string &data);
};

#endif //CRYPTOMASTER_FILEHANDLER_H
