[![License: BSD3](https://img.shields.io/badge/License-BSD3-yellow.svg)](https://opensource.org/licenses/bsd-3-clause)

# PString: A C++ String Library with Python-style Operations

PString is a C++ string library designed to emulate the behavior and functionality of Python's str type. Developed as a modified component of the [sapy](https://github.com/CairBin/sapy)
project.


# Install
```sh
git clone https://github.com/EPTansuo/PString
cd PString && mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make && make install 
```

# Example
`demo.cpp`:
```cpp
#include <iostream>
#include <pstring.h>

int main(){
    PString str = "Hello World!";
    auto str_splited = str.split(" ");
    for(auto item: str_splited){
        cout << item << std::endl;
    }
    if(str.startswith("Hello")){
        cout << "$str starts with \"Hello\"" << std::endl;
    }
    if(str.endswith('!')){
        cout << "$str ends with \'!\'" << std::endl;
    }
    return 0;
}
```
Compile and run:
```
g++ demo.cpp -lpstring -o demo
./demo
```
