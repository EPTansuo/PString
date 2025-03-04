[![License: BSD3](https://img.shields.io/badge/License-BSD3-yellow.svg)](https://opensource.org/licenses/bsd-3-clause)

# PString: A C++ String Library with Python-style Operations

PString is a C++ string library designed to emulate the behavior and functionality of Python's str type. Developed as a modified component of the [sapy](https://github.com/CairBin/sapy)
project.


# Install
```sh
git clone https://github.com/EPTansuo/PString
cd PString && mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make && sudo make install 
```

# Example
`demo.cpp`:
```cpp
#include <iostream>
#include <pstring.h>

int main(){
    PString str = "  Hello, World!  ";

    // Python-style split
    auto str_split = str.split(",");
    std::cout << str_split[0].upper() << std::endl;
    
    // Python-style join
    auto str_joined = PString(":").join(str_split);
    std::cout << str_joined << std::endl;

    // Python-style slice
    auto str_sliced = str.slice(6, 1, -1);
    std::cout << str_sliced << std::endl;

    // Python-style strip
    auto str_stripped = str.strip();
    std::cout << str_stripped << std::endl;

    // ...
}
```
Compile and run:
```
g++ demo.cpp -lpstring -o demo
./demo
```

## Bug List 
- [x] `" \r\n\thello world\t\r\n ".rstrip`
- [x] `" \r\n\thello world\t\r\n ".rsplit`
- [ ] `" \r\n\thello world\t\r\n ".expandtabs`
- [x] `"'\"\\".strip`
- [x] `"'\"\\".lstrip`
- [x] `"\t\n\r\x0b\x0c".strip`
- [x] `"\t\n\r\x0b\x0c".lstrip`
- [x] `"\t\n\r\x0b\x0c".rstrip`
- [x] `"\t\n\r\x0b\x0c".split`
- [x] `"\t\n\r\x0b\x0c".rsplit`
- [x] `"\t\n\r\x0b\x0c".splitlines`

Description:
- [ ] means the bug haven't fixed yet.
- [x] means the bug have been fixed.

## Limitations

- No support for Unicode character operations.


