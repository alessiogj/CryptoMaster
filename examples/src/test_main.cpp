#include <CryptoMaster/CryptoMaster/CryptoMaster.h>
#include <CryptoMaster/CryptoMaster/FileHandler.h>
#include <CryptoMaster/CryptoMaster/Utils.h>

#include <iostream>

int main() {
    std::string data = "Hello, CryptoMaster!";
    std::string key = Utils::generateKey();

    std::cout << "Original: " << data << std::endl;

    std::string encrypted = Utils::encrypt(data, key);
    std::cout << "Encrypted: " << encrypted << std::endl;

    std::string decrypted = Utils::decrypt(encrypted, key);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}
