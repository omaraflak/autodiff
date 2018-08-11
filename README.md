# Reverse Autodiff

Reverse automatic differentiation tool in C++.

# Example

```c++
Node x=2, y=3;

Graph graph({&x, &y});
graph.start_new_recording();

Node f = x*y + sin(x);

double dx = graph.gradient(f, x);
double dy = graph.gradient(f, y);
```