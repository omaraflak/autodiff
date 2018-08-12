#include "../include/node.h"

Node::Node() : value(0), uid(utils::uid()), backprop(false), gradient(0){}
Node::Node(const double& val) : value(val), uid(utils::uid()), backprop(false), gradient(0){}
Node::Node(const Node& node) : value(node.value), uid(node.uid), backprop(node.backprop), gradient(node.gradient){}

double Node::get_value() const      { return value; }
std::string Node::get_uid() const   { return uid; }
double Node::get_gradient() const   { return gradient; }
bool Node::did_backprop() const     { return backprop; }

void Node::set_value(const double& value)           { this->value = value; }
void Node::set_gradient(const double& gradient)     { this->gradient = gradient; }
void Node::set_backprop(const bool& backprop)       { this->backprop = backprop; }

Node Node::binaryOperation(const Node& l, const Node& r, const std::function<BinaryOperationResult(const Node&, const Node&)>& fun){
    Graph* graph = Graph::getInstance();
    BinaryOperationResult res = fun(l, r);
    Node result(res.value);

    if(graph!=NULL){
        Node* lnode = graph->has(l.uid) ? graph->get(l.uid) : graph->get(graph->create(l));
        Node* rnode = graph->has(r.uid) ? graph->get(r.uid) : graph->get(graph->create(r));
        Node* enode = graph->get(graph->create(result));
        graph->add(Edge(lnode->uid, enode->uid, res.left_grad));
        graph->add(Edge(rnode->uid, enode->uid, res.right_grad));
    }

    return result;
}

Node Node::unaryOperation(const Node& n, const std::function<UnaryOperationResult(const Node&)>& fun){
    Graph* graph = Graph::getInstance();
    UnaryOperationResult res = fun(n);
    Node result(res.value);

    if(graph!=NULL){
        Node* node = graph->has(n.get_uid()) ? graph->get(n.get_uid()) : graph->get(graph->create(n));
        Node* enode = graph->get(graph->create(result));
        graph->add(Edge(node->get_uid(), enode->get_uid(), res.grad));
    }

    return result;
}

Node& Node::operator+=(const Node& n){
    *this = *this + n;
    return *this;
}

Node& Node::operator-=(const Node& n){
    *this = *this - n;
    return *this;
}

Node& Node::operator*=(const Node& n){
    *this = *this * n;
    return *this;
}

Node& Node::operator/=(const Node& n){
    *this = *this / n;
    return *this;
}

Node operator+(const Node& a, const Node& b){
    return Node::binaryOperation(a, b, [](const Node& a, const Node& b){
        return BinaryOperationResult(a.value+b.value, 1, 1);
    });
}

Node operator-(const Node& a, const Node& b){
    return Node::binaryOperation(a, b, [](const Node& a, const Node& b){
        return BinaryOperationResult(a.value-b.value, 1, -1);
    });
}

Node operator*(const Node& a, const Node& b){
    return Node::binaryOperation(a, b, [](const Node& a, const Node& b){
        return BinaryOperationResult(a.value*b.value, b.value, a.value);
    });
}

Node operator/(const Node& a, const Node& b){
    return Node::binaryOperation(a, b, [](const Node& a, const Node& b){
        return BinaryOperationResult(a.value/b.value, 1.0/b.value, -1.0*a.value/(b.value*b.value));
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
    return log(x, 10);
}

Node ln(const Node& x){
    return log(x, ::exp(1));
}

Node pow(const Node& x, const Node& base){
    return Node::binaryOperation(x, base, [](const Node& a, const Node& b){
        return BinaryOperationResult(::pow(a.value, b.value), b.value*::pow(a.value, b.value-1), ::log(a.value)*::exp(b.value*::log(a.value)));
    });
}

Node exp(const Node& x){
    return pow(::exp(1), x);
}

Node sqrt(const Node& x){
    return pow(x, 0.5);
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
