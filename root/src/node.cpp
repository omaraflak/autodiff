#include "../include/node.h"

Node::Node() : value(0), uid(utils::uid()), backprop(false), gradient(0){}
Node::Node(const double& val) : value(val), uid(utils::uid()), backprop(false), gradient(0){}
Node::Node(const Node& node, const bool& copy_uid) : value(node.value), uid(copy_uid?node.uid:utils::uid()), backprop(node.backprop), gradient(node.gradient){}

double Node::get_value() const      { return value; }
std::string Node::get_uid() const   { return uid; }
double Node::get_gradient() const   { return gradient; }
bool Node::did_backprop() const     { return backprop; }

void Node::set_value(const double& value)           { this->value = value; }
void Node::set_gradient(const double& gradient)     { this->gradient = gradient; }
void Node::set_backprop(const bool& backprop)       { this->backprop = backprop; }

template <typename BINOP>
Node Node::binaryOperation(const Node& l, const Node& r, const BINOP& fun){
    Graph* graph = Graph::getInstanceNoCheck();
    BinaryOperationResult res = fun(l, r);
    Node result(res.value);
    Node* lnode = graph->has(l.uid) ? graph->get(l.uid) : graph->create(l);
    Node* rnode = graph->has(r.uid) ? graph->get(r.uid) : graph->create(r);
    Node* enode = graph->create(result);
    graph->create(Edge(lnode->uid, enode->uid, res.left_grad));
    graph->create(Edge(rnode->uid, enode->uid, res.right_grad));
    return result;
}

template <typename UNOP>
Node Node::unaryOperation(const Node& n, const UNOP& fun){
    Graph* graph = Graph::getInstanceNoCheck();
    UnaryOperationResult res = fun(n);
    Node result(res.value);
    Node* node = graph->has(n.uid) ? graph->get(n.uid) : graph->create(n);
    Node* enode = graph->create(result);
    graph->create(Edge(node->uid, enode->uid, res.grad));
    return result;
}

Node& Node::operator+=(const Node& r){
    *this = *this + r;
    return *this;
}

Node& Node::operator-=(const Node& r){
    *this = *this - r;
    return *this;
}

Node& Node::operator*=(const Node& r){
    *this = *this * r;
    return *this;
}

Node& Node::operator/=(const Node& r){
    *this = *this / r;
    return *this;
}

Node operator+(const Node& l, const Node& r){
    return Node::binaryOperation(l, r, [](const Node& l, const Node& r){
        return BinaryOperationResult(l.value+r.value, 1, 1);
    });
}

Node operator-(const Node& l, const Node& r){
    return Node::binaryOperation(l, r, [](const Node& l, const Node& r){
        return BinaryOperationResult(l.value-r.value, 1, -1);
    });
}

Node operator*(const Node& l, const Node& r){
    return Node::binaryOperation(l, r, [](const Node& l, const Node& r){
        return BinaryOperationResult(l.value*r.value, r.value, l.value);
    });
}

Node operator/(const Node& l, const Node& r){
    return Node::binaryOperation(l, r, [](const Node& l, const Node& r){
        return BinaryOperationResult(l.value/r.value, 1.0/r.value, -1.0*l.value/(r.value*r.value));
    });
}

Node sin(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::sin(n.value), ::cos(n.value));
    });
}

Node cos(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::cos(n.value), -1.0*::sin(n.value));
    });
}

Node tan(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::tan(n.value), 1.0/::pow(::cos(n.value), 2));
    });
}

Node sinh(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::sinh(n.value), ::cosh(n.value));
    });
}

Node cosh(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::cosh(n.value), ::sinh(n.value));
    });
}

Node asin(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::asin(n.value), 1.0/(::sqrt(1-n.value*n.value)));
    });
}

Node acos(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::acos(n.value), -1.0/(::sqrt(1-n.value*n.value)));
    });
}

Node atan(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::atan(n.value), 1.0/(1+n.value*n.value));
    });
}

Node tanh(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::tanh(n.value), 1.0-::pow(::tanh(n.value), 2));
    });
}

Node log(const Node& x, const Node& base){
    return Node::binaryOperation(x, base, [](const Node& a, const Node& b){
        return BinaryOperationResult(::log(a.value)/::log(b.value), 1.0/(a.value*::log(b.value)), -1.0*::log(a.value)/(b.value*::log(b.value)));
    });
}

Node log(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::log(n.value)/::log(10), 1.0/(n.value*::log(10)));
    });
}

Node ln(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::log(n.value), 1.0/::log(n.value));
    });
}

Node pow(const Node& x, const Node& base){
    return Node::binaryOperation(x, base, [](const Node& a, const Node& b){
        return BinaryOperationResult(::pow(a.value, b.value), b.value*::pow(a.value, b.value-1), ::log(a.value)*::exp(b.value*::log(a.value)));
    });
}

Node exp(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::exp(n.value), ::exp(n.value));
    });
}

Node sqrt(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        return UnaryOperationResult(::sqrt(n.value), 1.0/(2*::sqrt(n.value)));
    });
}

Node abs(const Node& x){
    return Node::unaryOperation(x, [](const Node& n){
        int sign = n.value==0 ? 0 : n.value/::abs(n.value);
        return UnaryOperationResult(::abs(n.value), sign);
    });
}

std::ostream& operator<<(std::ostream& os, const Node& node){
    os << node.value;
    return os;
}
