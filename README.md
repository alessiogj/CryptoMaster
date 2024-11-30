Steps to install the library:
1. Clone the repository
2. Run the following command:
```bash
pip install conan
```
3. Run the following command:
```bash
conan create . user/channel
```
4. Run the following command:
```bash
conan create . --name=cryptomaster --version=1.0.0
```

Remove the library:
```bash
conan remove cryptomaster/1.0.0 --confirm
```

Compile the example:
```bash
conan install . --output-folder=build --build=missing
cmake -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -B build -S .
cmake --build build
```

TODO
