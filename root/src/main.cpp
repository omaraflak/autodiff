#include <iostream>
#include "../include/graph.h"

int main(int argc, char const *argv[]) {
    Node x=2, y=3;
    Graph graph({&x, &y});

    Node f = x*y + sin(x);

    std::cout << "f(x,y) = x*y + sin(x)" << std::endl;
    std::cout << "f(" << x << "," << y << ") = " << f << std::endl;
    std::cout << "∂f/∂x = " << graph.gradient(f, x) << std::endl;
    std::cout << "∂f/∂y = " << graph.gradient(f, y) << std::endl;
    return 0;
}
