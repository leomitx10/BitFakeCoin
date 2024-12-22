# Cryptocurrency Project

This is a C++ implementation of a basic cryptocurrency system with blockchain, mining, and wallet functionality.

## Features

- Blockchain implementation with proof-of-work mining
- Wallet management with public/private key pairs
- Transaction handling
- SHA-256 hashing
- Secure key generation using OpenSSL

## Dependencies

- C++17 or higher
- OpenSSL library
- CMake 3.10 or higher

## Building the Project

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Generate build files:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

## Project Structure

- `src/blockchain/` - Contains blockchain implementation
- `src/wallet/` - Wallet and transaction management
- `src/utils/` - Utility functions and helpers

## Usage

After building, you can run the application:
```bash
./crypto_app
```

## License

This project is open source and available under the MIT License.
