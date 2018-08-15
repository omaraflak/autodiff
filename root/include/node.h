#ifndef NODE_H
#define NODE_H

#include <cmath>
#include <iostream>

#include "graph.h"
#include "bor.h"
#include "uor.h"

class Node {
    private:
        double value;
        long int uid;

        double gradient_recursive(Graph* graph, const long int& current_uid, const long int& stop_uid) const;

    public:
        Node(const double& value=0);
        Node(const Node& node);

        static Node unary_operation(const Node& n, UnaryOperationResult (*)(const double&));
        static Node binary_operation(const Node& l, const Node& r, BinaryOperationResult (*)(const double&, const double&));

        double gradient(const Node& node) const;
        std::vector<double> gradient(const std::vector<Node>& nodes) const;
        std::vector<std::vector<double> > gradient(const std::vector<std::vector<Node> >& nodes) const;

        friend Node operator+(const Node& l, const Node& r);
        friend Node operator-(const Node& l, const Node& r);
        friend Node operator*(const Node& l, const Node& r);
        friend Node operator/(const Node& l, const Node& r);

        Node& operator+=(const Node& r);
        Node& operator-=(const Node& r);
        Node& operator*=(const Node& r);
        Node& operator/=(const Node& r);

        friend bool operator==(const Node& l, const Node& r);
        friend bool operator<(const Node& l, const Node& r);
        friend bool operator>(const Node& l, const Node& r);
        friend bool operator<=(const Node& l, const Node& r);
        friend bool operator>=(const Node& l, const Node& r);

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
        friend Node log10(const Node& x);
        friend Node ln(const Node& x);

        friend Node pow(const Node& x, const Node& p);
        friend Node exp(const Node& x);
        friend Node sqrt(const Node& x);

        friend Node abs(const Node& x);
        friend Node min(const Node& l, const Node& r);
        friend Node max(const Node& l, const Node& r);

        friend std::ostream& operator<<(std::ostream& os, const Node& node);
};

#endif /* end of include guard: NODE_H */
