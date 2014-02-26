## What is it ? ##
This module is the main event loop system. Other module relly on this module to allow event programming.

## API ##

```C

class IOService {
      IOService(); //Create a new IOService. Becarefull not to create multiple IOService object.
      static IOService& instance(); //Retrun the previously created IOService object.
      void addTimer(const unsigned long& time, Callback cb, void* data); //Add a timer to the event loop. The function cb will be called after time milliseconds with data as parameter.
      void exec(); //This start the event loop. This function will never return.
}

```
## Exemple ##

```C

#include "aio/IOService.h"
#include "aio/IOStream.h"

using namespace aio;

void onTimeout(void* data) {
     cout << "A timeout occur" << endl;
}


IOService service;
service.addTimer(1000, &onTimeout, NULL);

service.run();

```

## Warning ##

  * You MUST NOT create multiple instance of IOService.
  * You MUST create an instance before calling IOService::instance()
  * You can only add 30 timers at the same time.
