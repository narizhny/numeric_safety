# Numeric cast
Library for fast answering frequent interview questions

### Cast numeric

```c++
#include "numeric_cast.h"
uint32_t a1 = 4000000000;
uint32_t b1 = 10;
std::cout << numeric_cast<int32_t>(a1) << std::endl; // throws std::overflow_error
std::cout << numeric_cast<char16_t>(b1) << std::endl; // Ok
```

### Signed/unsigned comparison

```c++
#include <stdint.h>
#include "compare.h"

int32_t a = -123;
uint32_t b = 4000000000;
std::cout << std::boolalpha << less(a, b) << std::endl; //true
```

### Floating point values comparison
```c++
#include "floating_point_compare.h"
double d1 = 8.0000001;
double d2 = 8.0000005;

std::cout << std::boolalpha << floating_point_compare(d1, d2) << std::endl;     //false
std::cout << std::boolalpha << floating_point_compare<4>(d1, d2) << std::endl;	//true
```