#include "../include/graph.h"

Graph::Graph(){}

Graph::Graph(std::initializer_list<Node*> list){
    for(auto& item : list){
        item->set_graph(this);
        nodes[item->get_uid()] = item;
    }
}

Graph::~Graph(){
    clear_memory();
}

double Graph::gradientRecursive(Node* node){
    double sum = 0.0;
    std::vector<Edge*> e = edges[node->get_uid()];
    if(e.size()>0){
        for(auto& edgePtr : e){
            sum += edgePtr->weight*gradientRecursive(nodes[edgePtr->end_uid]);
        }
    } else{
        return node->is_first_node() ? 1.0 : 0.0;
    }
}

void Graph::clear_memory(){
    for(auto& pair : edges){
        for(auto& edgePtr : pair.second){
            delete edgePtr;
        }
    }

    for(auto& pair : nodes){
        if(!pair.second->is_user_node()){
            delete pair.second;
        }
    }
}

double Graph::gradient(const Node& out, const Node& in){
    Node* outPtr = nodes[out.get_uid()];
    Node* inPtr = nodes[in.get_uid()];
    outPtr->set_first_node(true);
    double grad = gradientRecursive(inPtr);
    outPtr->set_first_node(false);
    return grad;
}

void Graph::start_recording(){
    clear_memory();
    nodes.clear();
    edges.clear();
}

void Graph::start_recording(std::initializer_list<Node*> list){
    start_recording();
    for(auto& item : list){
        item->set_graph(this);
        nodes[item->get_uid()] = item;
    }
}

bool Graph::has(const std::string& uid) const{
    return nodes.find(uid)!=nodes.end();
}

Node* Graph::get(const std::string& uid) const{
    return nodes.at(uid);
}

std::string Graph::create(const Node& node){
    Node* n = new Node(node, node.get_uid());
    n->set_user_node(false);
    nodes[n->get_uid()] = n;
    return n->get_uid();
}

void Graph::add(const Edge& edge){
    edges[edge.start_uid].push_back(new Edge(edge));
}

std::ostream& operator<<(std::ostream& os, const Graph& graph){
    for(const auto& pair : graph.edges){
        std::cout << pair.first << " : " << std::endl;
        for(const auto& edge : pair.second)
            os << "\t" << *edge << std::endl;
    }

    std::cout << std::endl;

    for(const auto& pair : graph.nodes){
        std::cout << *pair.second << std::endl;
    }
    return os;
}
