#include <iostream>

#include "vectmath.h"
#include "../../root/include/graph.h"

Node function(std::vector<Node>& x){
    return pow(x[0]-x[1], 2) + x[0]*x[1]*x[2]; // (x-y)^2 + x*y*z
}

int main(int argc, char const *argv[]) {
    Graph* graph = Graph::getInstance();
    std::vector<Node> x = {5,6,7};
    Node f = function(x);
    std::cout << "grad(f) = " << graph->gradient(f, x) << std::endl;
    return 0;
}
