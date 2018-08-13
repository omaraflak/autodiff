#ifndef NODE_H
#define NODE_H

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
        std::string uid;
        double gradient;
        bool backprop;

        template <typename BINOP>
        static Node binaryOperation(const Node& l, const Node& r, const BINOP& fun);

        template <typename UNOP>
        static Node unaryOperation(const Node& n, const UNOP& fun);

    public:
        Node();
        Node(const double& value);
        Node(const Node& node, const bool& copy_uid=false);

        double get_value() const;
        std::string get_uid() const;
        double get_gradient() const;
        bool did_backprop() const;

        void set_value(const double& value);
        void set_gradient(const double& gradient);
        void set_backprop(const bool& backprop);

        Node& operator+=(const Node& r);
        Node& operator-=(const Node& r);
        Node& operator*=(const Node& r);
        Node& operator/=(const Node& r);

        friend Node operator+(const Node& l, const Node& r);
        friend Node operator-(const Node& l, const Node& r);
        friend Node operator*(const Node& l, const Node& r);
        friend Node operator/(const Node& l, const Node& r);

        friend Node sin(const Node& x);
        friend Node cos(const Node& x);
        friend Node tan(const Node& x);
        friend Node sinh(const Node& x);
        friend Node cosh(const Node& x);
        friend Node tanh(const Node& x);
        friend Node asin(const Node& x);
        friend Node acos(const Node& x);
        friend Node atan(const Node& x);

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
