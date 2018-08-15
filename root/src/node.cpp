#include "../include/node.h"

Node::Node(const double& value) {
    this->value = value;
    this->uid = Graph::uid();
}

Node::Node(const Node& node){
    this->value = node.value;
    this->uid = node.uid;
}

long int Node::get_uid() const{
    return this->uid;
}

double Node::gradient_recursive(Graph* graph, const long int& current_uid, const long int& stop_uid) const{
    if(current_uid==stop_uid){
        return 1.0;
    }

    double sum=0.0;
    if(graph->has(current_uid)){
        for(auto& pair : graph->get(current_uid)){
            sum += pair.first*gradient_recursive(graph, pair.second, stop_uid);
        }
    }
    return sum;
}

double Node::gradient(const Node& node) const{
    Graph* graph = Graph::getInstance();
    return gradient_recursive(graph, this->uid, node.uid);
}

std::vector<double> Node::gradient(const std::vector<Node>& nodes) const{
    Graph* graph = Graph::getInstance();
    std::vector<double> grad(nodes.size());
    for(size_t i=0 ; i<nodes.size() ; i++){
        grad[i] = gradient_recursive(graph, this->uid, nodes[i].uid);
    }
    return grad;
}

std::vector<std::vector<double> > Node::gradient(const std::vector<std::vector<Node> >& nodes) const{
    Graph* graph = Graph::getInstance();
    std::vector<std::vector<double> > grad(nodes.size());
    for(size_t i=0 ; i<nodes.size() ; i++){
        grad[i].resize(nodes[i].size());
        for(size_t j=0 ; j<nodes[i].size() ; j++){
            grad[i][j] = gradient_recursive(graph, this->uid, nodes[i][j].uid);
        }
    }
    return grad;
}

template <typename Fun>
Node Node::unary_operation(const Node& n, const Fun& fun){
    UnaryOperationResult res = fun(n);
    Node result(res.value);
    Graph* graph = Graph::getInstance();
    graph->connect(result.uid, std::make_pair(res.grad, n.uid));
    return result;
}

template <typename Fun>
Node Node::binary_operation(const Node& l, const Node& r, const Fun& fun){
    BinaryOperationResult res = fun(l,r);
    Node result(res.value);
    Graph* graph = Graph::getInstance();
    graph->connect(result.uid, std::make_pair(res.left_grad, l.uid));
    graph->connect(result.uid, std::make_pair(res.right_grad, r.uid));
    return result;
}

Node operator+(const Node& l, const Node& r){
    return Node::binary_operation(l, r, [](const Node& l, const Node& r){
        return BinaryOperationResult(l.value+r.value, 1.0, 1.0);
    });
}

Node operator-(const Node& l, const Node& r){
    return Node::binary_operation(l, r, [](const Node& l, const Node& r){
        return BinaryOperationResult(l.value-r.value, 1.0, -1.0);
    });
}

Node operator*(const Node& l, const Node& r){
    return Node::binary_operation(l, r, [](const Node& l, const Node& r){
        return BinaryOperationResult(l.value*r.value, r.value, l.value);
    });
}

Node operator/(const Node& l, const Node& r){
    return Node::binary_operation(l, r, [](const Node& l, const Node& r){
        return BinaryOperationResult(l.value/r.value, 1.0/r.value, -1.0*l.value/(r.value*r.value));
    });
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

bool operator==(const Node& l, const Node& r){
    return l.value==r.value;
}

bool operator<(const Node& l, const Node& r){
    return l.value<r.value;
}

bool operator>(const Node& l, const Node& r){
    return l.value>r.value;
}

bool operator<=(const Node& l, const Node& r){
    return l.value<=r.value;
}

bool operator>=(const Node& l, const Node& r){
    return l.value>=r.value;
}

Node sin(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::sin(n.value), ::cos(n.value));
    });
}

Node cos(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::cos(n.value), -1.0*::sin(n.value));
    });
}

Node tan(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::tan(n.value), 1.0/::pow(::cos(n.value), 2));
    });
}

Node sinh(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::sinh(n.value), ::cosh(n.value));
    });
}

Node cosh(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::cosh(n.value), ::sinh(n.value));
    });
}

Node asin(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::asin(n.value), 1.0/(::sqrt(1-n.value*n.value)));
    });
}

Node acos(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::acos(n.value), -1.0/(::sqrt(1-n.value*n.value)));
    });
}

Node atan(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::atan(n.value), 1.0/(1+n.value*n.value));
    });
}

Node tanh(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::tanh(n.value), 1.0-::pow(::tanh(n.value), 2));
    });
}

Node log(const Node& x, const Node& base){
    return Node::binary_operation(x, base, [](const Node& a, const Node& b){
        return BinaryOperationResult(::log(a.value)/::log(b.value), 1.0/(a.value*::log(b.value)), -1.0*::log(a.value)/(b.value*::log(b.value)));
    });
}

Node log(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::log(n.value)/::log(10), 1.0/(n.value*::log(10)));
    });
}

Node ln(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::log(n.value), 1.0/::log(n.value));
    });
}

Node pow(const Node& x, const Node& base){
    return Node::binary_operation(x, base, [](const Node& a, const Node& b){
        if(a.value<=0){
            return BinaryOperationResult(::pow(a.value, b.value), b.value*::pow(a.value, b.value-1), 0);
        }
        return BinaryOperationResult(::pow(a.value, b.value), b.value*::pow(a.value, b.value-1), ::log(a.value)*::pow(a.value, b.value));
    });
}

Node exp(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::exp(n.value), ::exp(n.value));
    });
}

Node sqrt(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        return UnaryOperationResult(::sqrt(n.value), 1.0/(2*::sqrt(n.value)));
    });
}

Node abs(const Node& x){
    return Node::unary_operation(x, [](const Node& n){
        int sign = n.value==0 ? 0 : n.value/::abs(n.value);
        return UnaryOperationResult(::abs(n.value), sign);
    });
}

std::ostream& operator<<(std::ostream& os, const Node& node){
    os << node.value;
    return os;
}
