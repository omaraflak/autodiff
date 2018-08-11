# Reverse Autodiff

Reverse automatic differentiation tool in C++.

# Example

```c++
Node x=2, y=3;
Graph graph({&x, &y});

Node f = x*y + sin(x);

double dx = graph.gradient(f, x);
double dy = graph.gradient(f, y);
```
