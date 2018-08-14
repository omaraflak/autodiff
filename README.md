# Autodiff

Reverse automatic differentiation tool in C++.

# Install

Normal make sequence

```
make
make install
```

# Use

In a main.cpp file :

```c++
#include <iostream>
#include <autodiff/graph.h>

int main(int argc, char const *argv[]) {
    // Should be declared before any calculation
    Graph* graph = Graph::getInstance();

    Node x=2, y=3;
    Node f = x*y + sin(x);

    std::cout << "f(x,y) = x*y + sin(x)" << std::endl;
    std::cout << "f(" << x << "," << y << ") = " << f << std::endl;
    std::cout << "∂f/∂x = " << graph->gradient(f, x) << std::endl;
    std::cout << "∂f/∂y = " << graph->gradient(f, y) << std::endl;
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
graph->new_recording();
```
