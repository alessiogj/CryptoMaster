#include <iostream>
#include <CryptoMaster/CryptoMaster.h>

int main() {
    std::string data = "Hello, CryptoMaster!";
    std::string key = CryptoMaster::generateKey();

    std::cout << "Original: " << data << std::endl;

    std::string encrypted = CryptoMaster::encrypt(data, key);
    std::cout << "Encrypted: " << encrypted << std::endl;

    std::string decrypted = CryptoMaster::decrypt(encrypted, key);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}
