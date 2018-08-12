#ifndef NODE_H
#define NODE_H

#include <functional>
#include <iostream>
#include <string>
#include <cmath>

#include "utils.h"
#include "graph.h"
#include "binary_operation_result.h"
#include "unary_operation_result.h"

class Graph;
class Node {
    private:
        double value;
        bool user_node;
        std::string uid;
        double gradient;
        bool backprop;

        Graph* graph;

        static Node binaryOperation(const Node& l, const Node& r, const std::function<BinaryOperationResult(const Node&, const Node&)>& fun);
        static Node unaryOperation(const Node& n, const std::function<UnaryOperationResult(const Node&)>& fun);

    public:
        Node();
        Node(const double& value);
        Node(const double& value, const bool& user_node);
        Node(const Node& node);

        double get_value() const;
        bool is_user_node() const;
        std::string get_uid() const;
        double get_gradient() const;
        bool did_backprop() const;
        Graph* get_graph() const;

        void set_value(const double& value);
        void set_user_node(const bool& user_node);
        void set_gradient(const double& gradient);
        void set_backprop(const bool& backprop);
        void set_graph(Graph* graph);

        friend Node operator+(const Node& a, const Node& b);
        friend Node operator-(const Node& a, const Node& b);
        friend Node operator*(const Node& a, const Node& b);
        friend Node operator/(const Node& a, const Node& b);

        friend Node sin(const Node& x);
        friend Node cos(const Node& x);
        friend Node tan(const Node& x);
        friend Node sinh(const Node& x);
        friend Node cosh(const Node& x);
        friend Node tanh(const Node& x);

        friend Node log(const Node& x, const Node& base);
        friend Node log(const Node& x);
        friend Node ln(const Node& x);

        friend Node pow(const Node& x, const Node& p);
        friend Node exp(const Node& x);
        friend Node sqrt(const Node& x);

        friend Node abs(const Node& x);

        friend std::ostream& operator<<(std::ostream& os, const Node& node);
};

#endif /* end of include guard: NODE_H */
