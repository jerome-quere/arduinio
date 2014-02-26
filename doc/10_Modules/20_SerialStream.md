## What is it ? ##
  SerialStream is a module that allow you to use the arduino serial in a similar way that you use std::cout in C++.

## API ##

```C

class SerialStream {
      void start(const long& speed = 9600); //Initialise the serial connection with the specified speed.

      template <typename T>
      Logger& operator<<(const T& p); //Send data of various type through the serial

      Logger& operator<<(const Endl&); //Send an end of line charactere and flush the serial.
}

extern SerialStream cout; //A cout interface.
extern struct SerialStream::Endl endl; // A endl that can be used in a c++ like style.


```

## Exemple ##
```C

#include "aio/IOStream.h"

using namespace aio;

cout.start(9600);
cout << "This is a string:" << "toto" << endl;
cout << "This is an integer:" << 42 << endl;

```