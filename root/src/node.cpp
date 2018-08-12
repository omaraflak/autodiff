#include "../include/node.h"

Node::Node() : value(0), user_node(true), graph(NULL), uid(utils::uid()), backprop(false){}
Node::Node(const double& val) : value(val), user_node(true), graph(NULL), uid(utils::uid()), backprop(false){}
Node::Node(const double& val, const bool& user) : value(val), user_node(user), graph(NULL), uid(utils::uid()), backprop(false){}
Node::Node(const Node& node) : value(node.value), user_node(node.user_node), graph(node.graph), uid(node.uid), backprop(node.backprop){}

double Node::get_value() const      { return value; }
bool Node::is_user_node() const     { return user_node; }
std::string Node::get_uid() const   { return uid; }
double Node::get_gradient() const   { return gradient; }
bool Node::did_backprop() const     { return backprop; }
Graph* Node::get_graph() const      { return graph; }

void Node::set_value(const double& value)           { this->value = value; }
void Node::set_user_node(const bool& user_node)     { this->user_node = user_node; }
void Node::set_gradient(const double& gradient)     { this->gradient = gradient; }
void Node::set_backprop(const bool& backprop)       { this->backprop = backprop; }
void Node::set_graph(Graph* graph)                  { this->graph = graph; }

Node Node::binaryOperation(const Node& l, const Node& r, const std::function<BinaryOperationResult(const Node&, const Node&)>& fun){
    Graph* graph = l.graph;
    if(graph==NULL){
        graph = r.graph;
    }

    BinaryOperationResult res = fun(l, r);
    Node result(res.value);
    result.graph = graph;

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
    Graph* graph = n.get_graph();
    UnaryOperationResult res = fun(n);
    Node result(res.value);
    result.set_graph(graph);

    if(graph!=NULL){
        Node* node = graph->has(n.get_uid()) ? graph->get(n.get_uid()) : graph->get(graph->create(n));
        Node* enode = graph->get(graph->create(result));
        graph->add(Edge(node->get_uid(), enode->get_uid(), res.grad));
    }

    return result;
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
        return BinaryOperationResult(::pow(a.value, b.value), (b.value*::exp(b.value*::log(a.value)))/a.value, ::log(a.value)*::exp(b.value*::log(a.value)));
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
