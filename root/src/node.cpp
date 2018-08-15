#include "../include/node.h"

Node::Node(const double& value) {
    this->value = value;
    this->uid = Graph::uid();
}

Node::Node(const Node& node){
    this->value = node.value;
    this->uid = node.uid;
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

Node Node::unary_operation(const Node& n, UnaryOperationResult (*fun)(const double&)){
    UnaryOperationResult res = fun(n.value);
    Node result(res.value);
    Graph* graph = Graph::getInstance();
    graph->connect(result.uid, std::make_pair(res.grad, n.uid));
    return result;
}

Node Node::binary_operation(const Node& left, const Node& right, BinaryOperationResult (*fun)(const double&, const double&)){
    BinaryOperationResult res = fun(left.value, right.value);
    Node result(res.value);
    Graph* graph = Graph::getInstance();
    graph->connect(result.uid, std::make_pair(res.left_grad, left.uid));
    graph->connect(result.uid, std::make_pair(res.right_grad, right.uid));
    return result;
}

Node operator+(const Node& left, const Node& right){
    return Node::binary_operation(left, right, [](const double& l, const double& r){
        return BinaryOperationResult(l+r, 1.0, 1.0);
    });
}

Node operator-(const Node& left, const Node& right){
    return Node::binary_operation(left, right, [](const double& l, const double& r){
        return BinaryOperationResult(l-r, 1.0, -1.0);
    });
}

Node operator*(const Node& left, const Node& right){
    return Node::binary_operation(left, right, [](const double& l, const double& r){
        return BinaryOperationResult(l*r, r, l);
    });
}

Node operator/(const Node& left, const Node& right){
    return Node::binary_operation(left, right, [](const double& l, const double& r){
        return BinaryOperationResult(l/r, 1.0/r, -1.0*l/(r*r));
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

bool operator==(const Node& left, const Node& right){
    return left.value==right.value;
}

bool operator<(const Node& left, const Node& right){
    return left.value<right.value;
}

bool operator>(const Node& left, const Node& right){
    return left.value>right.value;
}

bool operator<=(const Node& left, const Node& right){
    return left.value<=right.value;
}

bool operator>=(const Node& left, const Node& right){
    return left.value>=right.value;
}

Node sin(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::sin(n), ::cos(n));
    });
}

Node cos(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::cos(n), -1.0*::sin(n));
    });
}

Node tan(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::tan(n), 1.0/::pow(::cos(n), 2));
    });
}

Node sinh(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::sinh(n), ::cosh(n));
    });
}

Node cosh(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::cosh(n), ::sinh(n));
    });
}

Node asin(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::asin(n), 1.0/(::sqrt(1-n*n)));
    });
}

Node acos(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::acos(n), -1.0/(::sqrt(1-n*n)));
    });
}

Node atan(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::atan(n), 1.0/(1+n*n));
    });
}

Node tanh(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::tanh(n), 1.0-::pow(::tanh(n), 2));
    });
}

Node log(const Node& x, const Node& base){
    return Node::binary_operation(x, base, [](const double& a, const double& b){
        return BinaryOperationResult(::log(a)/::log(b), 1.0/(a*::log(b)), -1.0*::log(a)/(b*::log(b)));
    });
}

Node log10(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::log(n)/::log(10), 1.0/(n*::log(10)));
    });
}

Node ln(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::log(n), 1.0/::log(n));
    });
}

Node pow(const Node& x, const Node& base){
    return Node::binary_operation(x, base, [](const double& a, const double& b){
        if(a<=0){
            return BinaryOperationResult(::pow(a,b), b*::pow(a,b-1), 0);
        }
        return BinaryOperationResult(::pow(a,b), b*::pow(a,b-1), ::log(a)*::pow(a,b));
    });
}

Node exp(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::exp(n), ::exp(n));
    });
}

Node sqrt(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        return UnaryOperationResult(::sqrt(n), 1.0/(2*::sqrt(n)));
    });
}

Node abs(const Node& x){
    return Node::unary_operation(x, [](const double& n){
        int sign = n==0 ? 0 : n/::abs(n);
        return UnaryOperationResult(::abs(n), sign);
    });
}

Node min(const Node& left, const Node& right){
    return Node::binary_operation(left, right, [](const double& a, const double& b){
        if(a<b){
            return BinaryOperationResult(a, 1, 0);
        }
        if(a>b){
            return BinaryOperationResult(b, 0, 1);
        }
        return BinaryOperationResult(a, 0, 0);
    });
}

Node max(const Node& left, const Node& right){
    return Node::binary_operation(left, right, [](const double& a, const double& b){
        if(a>b){
            return BinaryOperationResult(a, 1, 0);
        }
        if(a<b){
            return BinaryOperationResult(b, 0, 1);
        }
        return BinaryOperationResult(a, 0, 0);
    });
}

std::ostream& operator<<(std::ostream& os, const Node& node){
    os << node.value;
    return os;
}
