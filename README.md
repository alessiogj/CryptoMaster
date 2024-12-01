# CryptoMaster

<p align="center">
  <img src="img/logo.png" alt="CryptoMaster Logo" width="250" style="border-radius: 15px; box-shadow: 0 4px 
  8px rgba(0, 0, 0, 0.2);">
</p>

## Overview of the Library
CryptoMaster is a high-performance cryptography library designed to provide easy-to-use tools for file encryption, 
decryption, and digital signature generation.
It supports advanced encryption algorithms such as `AES-GCM` and provides seamless integration with OpenSSL for 
robust cryptographic operations.

### Key Features:
- **File Encryption and Decryption**: Securely encrypt and decrypt files using advanced cryptographic algorithms.
- **`HMAC-SHA256` Signing**: Generate and verify message signatures for data integrity.
- **Random Key Generation**: Create secure random encryption keys with customizable lengths.
- **Cross-Platform Support**: Compatible with major operating systems, including Windows, macOS, and Linux.

---

### File Decryption Feature

<p align="center">
  <img src="img/Decrypt.svg" alt="Decrypt Feature" width="500" style="box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1); 
  margin-bottom: 20px;">
</p>

The decryption feature allows users to seamlessly decrypt files encrypted using `AES-GCM` or other supported algorithms. 
It's designed to handle large files efficiently and securely.

---

### Cryptography Algorithms

<p align="center">
  <img src="img/Cryptography.svg" alt="Cryptography Feature" width="500" style="box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1); 
   margin-bottom: 20px;">
</p>

CryptoMaster supports a range of cryptographic algorithms to ensure the highest level of data security. The default 
`AES-GCM` algorithm is ideal for secure file encryption and decryption.


## Steps to Install the Library

1. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```

2. **Install Conan**
   Run the following command to install Conan:
   ```bash
   pip install conan
   ```

3. **Create the Library Package**
   To create the library package using Conan 2.x, use:
   ```bash
   conan create . --name=cryptomaster --version=1.0.0 --user=user --channel=stable
   ```

   **Note:** Ensure that `--user` and `--channel` are specified correctly as Conan now requires explicit declaration.

   - If you encounter warnings about deprecated features (e.g., `cpp_info.names`, `cpp_info.build_modules`, `env_info`), 
   - consider updating dependencies to versions compatible with Conan 2.x.

## Steps to Remove the Library

If you need to remove the library package, use the following command:
```bash
conan remove cryptomaster/1.0.0 --confirm
```

## Compiling the Example

1. **Install Dependencies**
   Install the necessary dependencies with Conan, ensuring missing packages are built:
   ```bash
   conan install . --output-folder=build --build=missing
   ```

2. **Configure with CMake**
   Configure the project using the Conan-generated toolchain file:
   ```bash
   cmake -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -B build -S .
   ```

3. **Build the Project**
   Build the project using CMake:
   ```bash
   cmake --build build
   ```

## Alternative Compilation Methods

### Method 1: Using a Single Conan Install and Build Command
Combine dependency installation and build steps into a single command:
   ```bash
   conan install . --build=missing
   cmake . -B build -DCMAKE_BUILD_TYPE=Release
   cmake --build build
   ```

### Method 2: Direct Build Without Conan Package Management
If you want to build directly without creating Conan packages:
   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   cmake --build build
   ```

### Method 3: System-Wide OpenSSL
If OpenSSL is installed system-wide and Conan is not used, specify the library paths manually:
   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DOPENSSL_ROOT_DIR=/path/to/openssl
   cmake --build build
   ```

## Using the Library

### File Encryption Example

```cpp
#include "CryptoMaster/CryptoMaster.h"

int main() {
    const std::string inputFilePath = "example.txt";
    const std::string outputFilePath = "example_encrypted.txt";
    const std::string key = Utils::generateKey();

    if (FileHandler::encryptFile(inputFilePath, outputFilePath, key, Utils::Algorithm::AES_GCM)) {
        std::cout << "File encrypted successfully." << std::endl;
    } else {
        std::cerr << "Failed to encrypt file." << std::endl;
    }

    return 0;
}
```

### File Decryption Example

```cpp
#include "CryptoMaster/CryptoMaster.h"

int main() {
    const std::string inputFilePath = "example_encrypted.txt";
    const std::string outputFilePath = "example_decrypted.txt";
    const std::string key = "your-encryption-key";

    if (FileHandler::decryptFile(inputFilePath, outputFilePath, key, Utils::Algorithm::AES_GCM)) {
        std::cout << "File decrypted successfully." << std::endl;
    } else {
        std::cerr << "Failed to decrypt file." << std::endl;
    }

    return 0;
}
```

### Generate a Key and Sign Data

```cpp
#include "CryptoMaster/CryptoMaster.h"

int main() {
    const std::string data = "Hello, world!";
    const std::string key = Utils::generateKey();
    
    std::string signature = Utils::sign(data, key);
    if (Utils::verify(data, signature, key)) {
        std::cout << "Signature verified successfully!" << std::endl;
    } else {
        std::cerr << "Signature verification failed!" << std::endl;
    }

    return 0;
}
```

## Handling Deprecated Features

- If you see warnings about deprecated features like `cpp_info.names` or `env_info`, update the dependencies (e.g., 
- OpenSSL) to newer versions compatible with Conan 2.x.
- Ensure your `conanfile.py` uses `from conan.tools.cmake import CMake` and related modern tools.

## Additional Notes

- Ensure that you have `CMake` installed and accessible in your system.
- Make sure Conan is properly configured for your environment. If using a specific remote, add it with `conan remote add` 
- before installing dependencies.
- For troubleshooting or feature enhancements, consult the 
- [official Conan 2.x migration guide](https://docs.conan.io/latest/migrating_to_2.0.html).

Feel free to reach out to the project maintainers for further assistance or troubleshooting.

