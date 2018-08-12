# Reverse Autodiff

Reverse automatic differentiation tool in C++.

# Example

```c++
// Should be declared before any calculation
Graph* graph = Graph::getInstance();

Node x=2, y=3;
Node f = x*y + sin(x);

double dx = graph->gradient(f, x);
double dy = graph->gradient(f, y);
```

# Clear the computational graph

You should clear the computational graph whenever a new calculation happens.

```c++
graph->new_recording();
```
