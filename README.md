# Autodiff

Reverse automatic differentiation tool in C++.

# Examples

Examples you may find helpful.

* [Neural Network](https://github.com/OmarAflak/autodiff/blob/master/examples/src/ann.cpp)
* [Gradient Descent](https://github.com/OmarAflak/autodiff/blob/master/examples/src/gradient_descent.cpp)
* [Derivatives](https://github.com/OmarAflak/autodiff/blob/master/examples/src/simple.cpp)
* [Gradient](https://github.com/OmarAflak/autodiff/blob/master/examples/src/gradient.cpp)

# Install & Use

Normal make sequence

```
make
make install
```

Then in a new `main.cpp` file :

```c++
#include <iostream>
#include <autodiff/node.h>

int main(int argc, char const *argv[]) {
    Node x=2, y=3;
    Node f = x*y + sin(x);

    std::cout << "f(x,y) = x*y + sin(x)" << std::endl;
    std::cout << "f(" << x << "," << y << ") = " << f << std::endl;
    std::cout << "∂f/∂x = " << f.gradient(x) << std::endl;
    std::cout << "∂f/∂y = " << f.gradient(y) << std::endl;
    return 0;
}
```

Compile it :

```
g++ main.cpp -o main -std=c++11 -lautodiff
```

# Clear the computational graph

You should clear the computational graph whenever a new calculation happens.

```c++
Graph::getInstance()->new_recording();
```
