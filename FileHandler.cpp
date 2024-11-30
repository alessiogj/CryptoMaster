//
// Created by Alessio Gjergji on 30/11/24.
//

#include "FileHandler.h"
#include <fstream>
#include <stdexcept>

/**
 * Reads the content of the specified file and returns it as a string.
 *
 * @param filePath The path to the file to be read.
 * @return A string containing the content of the file.
 * @throws std::runtime_error If the file cannot be opened.
 */
std::string FileHandler::readFile(const std::string &filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Impossible to open the file: " + filePath);
    }
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

/**
 * Writes the provided data to the specified file.
 *
 * @param filePath The path to the file where data should be written.
 * @param data The data to write into the file.
 * @return True if the operation is successful, false otherwise.
 * @throws std::runtime_error If the file cannot be opened.
 */
bool FileHandler::writeFile(const std::string &filePath, const std::string &data) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Impossible to open the file: " + filePath);
    }
    file.write(data.c_str(), data.size());
    return true;
}

/**
 * Encrypts the content of an input file and writes the encrypted data to an output file.
 *
 * @param inputFilePath The path to the input file whose content needs to be encrypted.
 * @param outputFilePath The path to the output file where encrypted content will be written.
 * @param key The encryption key to be used.
 * @param algorithm The encryption algorithm to apply (defined in Utils::Algorithm).
 * @return True if the operation completes successfully, false otherwise.
 * @throws std::runtime_error If the input file cannot be read or the output file cannot be written.
 */
bool FileHandler::encryptFile(const std::string &inputFilePath, const std::string &outputFilePath,
                              const std::string &key, Utils::Algorithm algorithm) {
    std::string data = readFile(inputFilePath);
    std::string encryptedData = Utils::encrypt(data, key, algorithm);
    return writeFile(outputFilePath, encryptedData);
}

/**
 * Decrypts the content of an input file and writes the decrypted data to an output file.
 *
 * @param inputFilePath The path to the input file whose content needs to be decrypted.
 * @param outputFilePath The path to the output file where decrypted content will be written.
 * @param key The decryption key to be used.
 * @param algorithm The decryption algorithm to apply (defined in Utils::Algorithm).
 * @return True if the operation completes successfully, false otherwise.
 * @throws std::runtime_error If the input file cannot be read or the output file cannot be written.
 */
bool FileHandler::decryptFile(const std::string &inputFilePath, const std::string &outputFilePath,
                              const std::string &key, Utils::Algorithm algorithm) {
    std::string data = readFile(inputFilePath);
    std::string decryptedData = Utils::decrypt(data, key, algorithm);
    return writeFile(outputFilePath, decryptedData);
}
