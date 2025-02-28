# libbcrypt
A c++ wrapper around bcrypt password hashing

## How to build this
This is a CMake based project:

```bash
git clone https://github.com/trusch/libbcrypt
cd libbcrypt
mkdir build
cd build
cmake ..
make
sudo make install
sudo ldconfig
```

## How to use this

Here an example how to use this wrapper class (you can find a slightly edited example in src/ subdirectory)

```cpp
#include "bcrypt/BCrypt.hpp"
#include <iostream>

int main(){
	std::string password = "test";
	std::string hash = BCrypt::generateHash(password);

	std::cout << BCrypt::validatePassword(password,hash) << std::endl;
	std::cout << BCrypt::validatePassword("test1",hash) << std::endl;

	return 0;
}
```

build this with something like this:

```bash
g++ --std=c++11 -lbcrypt main.cpp
```

## Qt actual compilation

- Open CMakeLists.txt with Qt5.12.12.
- As toolchain select only Qt5.12.12 Ming32 bit.
- Compile.

- Open CMakeLists.txt with Qt5.5.1.
- As toolchain select only Qt5.5.1 Ming32 bit.
- Compile.
(usually qt creator of qt 5.12.12 builds smoothly also with mingw compiler of qt 5.5.1, but in this case there is an incompatibility of path generation, so we have to use different QtCreators!).

- TODO: Make msvc15 compilation work.
