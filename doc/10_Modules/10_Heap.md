## What is it ? ##
  Heap is a memory optimized heap (priority queue) using an array to store all the nodes. The heap allow you to store object of different priority.

## API ##

```C

template <typename T, unsigned short MAXSIZE>
class Heap {
      Heap(); //Create an empty heap that can store up to SIZE object of type T.
      iterator insert(const T& obj); //Insert a new object in the heap and return an iterator to the new element. The object will be copied.
      T& top(); //Access the top priority object in the heap.
      const T& top() const; //Same as the nonconst version.
      void pop(); //Remove the top priority object.
      const unsigned long& size() const; //Get the number of object present in the heap.


      iterator begin(); //Get the begin iterator.
      iterator end(); //Get the end iterator.

      const_iterator begin() const; //Get the begin const_iterator
      const_iterator end() const; //Get the end const_iterator.

      typedef iterator; //Type to iterate through an heap.
      typedef const_iterator; //Type to iterate through a const heap.
}
```

## Complexity ##
  * insert: O(logN)
  * top: O(1)
  * pop: O(logN)

## Exemple ##
```C

#include "aio/Heap.h"

using namespace aio;

Heap<int, 20> heap;

heap.insert(10);
heap.insert(40);
heap.insert(20);
heap.insert(20);

while (heap.size() > 0) {
  std::cout << heap.top() << std::endl;
  heap.pop();
}

```

```
$> a.out
40
30
20
10
```