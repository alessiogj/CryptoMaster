from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class CryptomasterConan(ConanFile):
    name = "cryptomaster"
    version = "1.0.0"
    license = "MIT"
    author = "Alessio GJERGJI <alessiovr1@gmail.com>"
    url = "https://github.com/alessiogj/CryptoMaster"
    description = "A cryptography library for file encryption and decryption."
    topics = ("cryptography", "openssl", "encryption")
    settings = "os", "compiler", "build_type", "arch"
    requires = "openssl/3.3.2"
    generators = "CMakeDeps", "CMakeToolchain"
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "Config/*"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["cryptomaster"]
