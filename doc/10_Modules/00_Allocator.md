## What is it ##
Has you know the use of malloc with arduino can be tricky. The allocator allow you to create and destroy object without using malloc.

## API ##

```C

class Allocator<T, SIZE> {
      Allocator(); //Create an allocator that create up to SIZE object of type T.
      T* alloc() //Alloc a new object. If there is no more space available retrun NULL.
      void free(T*) //Destroy a previously allocated object. Deleting an invalid pointer causes undefined behaviour.
};

```

## Exemple ##

```C

#include "aio/Allocator.h"

using namespace aio;

Allocator<int, 20> allocator; //Create the allocator that can create up to 20 int

int* ptr = allocator.alloc(); //Allocate an int from the allocator

allocator.free(ptr); //Destroy the previously allocated int

```

## Warning ##

 * When you create the allocator it automatically allocated the space to store up to SIZE object