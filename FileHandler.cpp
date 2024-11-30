//
// Created by Alessio Gjergji on 30/11/24.
//

#include "FileHandler.h"
#include <fstream>
#include <stdexcept>

std::string FileHandler::readFile(const std::string &filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Impossibile aprire il file: " + filePath);
    }
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

bool FileHandler::writeFile(const std::string &filePath, const std::string &data) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Impossibile scrivere sul file: " + filePath);
    }
    file.write(data.c_str(), data.size());
    return true;
}

bool FileHandler::encryptFile(const std::string &inputFilePath, const std::string &outputFilePath,
                              const std::string &key, Utils::Algorithm algorithm) {
    std::string data = readFile(inputFilePath);
    std::string encryptedData = Utils::encrypt(data, key, algorithm);
    return writeFile(outputFilePath, encryptedData);
}

bool FileHandler::decryptFile(const std::string &inputFilePath, const std::string &outputFilePath,
                              const std::string &key, Utils::Algorithm algorithm) {
    std::string data = readFile(inputFilePath);
    std::string decryptedData = Utils::decrypt(data, key, algorithm);
    return writeFile(outputFilePath, decryptedData);
}
