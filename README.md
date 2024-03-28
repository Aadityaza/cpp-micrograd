# Micro Grad

This is a C++ implementation of a simple automatic differentiation library inspired by Andrej Karpathy's micrograd project. The library provides a `Value` class that allows for automatic differentiation of scalar functions, making it easier to compute gradients for optimization tasks in machine learning and other domains.



## Features

- Automatic computation of gradients for scalar functions
- Support for basic arithmetic operations (`+`, `-`, `*`, `^`)
- Topological sorting of the computational graph for efficient backward propagation
- Overloaded `<<` operator for printing `Value` objects

## Usage

To use the library, you need to include the necessary header files and create instances of the `Value` class. Here's a simple example:

```cpp
#include <iostream>
#include "micrograd.h"

int main() {
   Value a = Value(4);
   Value b = Value(2);
   Value c = a * b;  // c = 8

   c.backward();

   std::cout << "Gradient of a: " << a.getGrad() << std::endl;  // Output: 2
   std::cout << "Gradient of b: " << b.getGrad() << std::endl;  // Output: 4

   return 0;
}
