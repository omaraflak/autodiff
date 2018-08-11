#include "../include/graph.h"

Graph::Graph(){}

Graph::Graph(std::initializer_list<Node*> list){
    start_recording(list);
}

Graph::Graph(std::vector<Node>& list){
    start_recording(list);
}

Graph::~Graph(){
    clear_memory();
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

double Graph::gradientRecursive(Node* node, const std::string& stop_uid){
    if(node->get_uid()==stop_uid)
        return 1.0;

    double sum = 0.0;
    for(auto& edgePtr : edges[node->get_uid()]){
        sum += edgePtr->weight*gradientRecursive(nodes[edgePtr->end_uid], stop_uid);
    }

    return sum;
}

double Graph::gradient(const Node& out, const Node& in){
    if(nodes.find(out.get_uid())==nodes.end())
        throw std::invalid_argument("Graph::gradient() : output node doesn't exist in graph.");
    if(nodes.find(in.get_uid())==nodes.end())
        throw std::invalid_argument("Graph::gradient() : input node doesn't exist in graph.");

    Node* inPtr = nodes[in.get_uid()];
    return gradientRecursive(inPtr, out.get_uid());
}

std::vector<double> Graph::gradient(const Node& out, const std::vector<Node>& in){
    if(nodes.find(out.get_uid())==nodes.end())
        throw std::invalid_argument("Graph::gradient() : output node doesn't exist in graph.");

    std::vector<double> grad(in.size());
    for(size_t i=0 ; i<in.size() ; i++){
        if(nodes.find(in.at(i).get_uid())==nodes.end())
            throw std::invalid_argument("Graph::gradient() : input node doesn't exist in graph.");

        Node* inPtr = nodes[in.at(i).get_uid()];
        grad[i] = gradientRecursive(inPtr, out.get_uid());
    }
    return grad;
}

void Graph::restart_recording(){
    clear_memory();
    edges.clear();
    for(auto it=nodes.begin() ; it!=nodes.end(); it++){
        if(!it->second->is_user_node()){
            nodes.erase(it);
        }
    }
}

void Graph::start_recording(std::initializer_list<Node*> list){
    clear_memory();
    nodes.clear();
    edges.clear();

    for(auto& item : list){
        item->set_graph(this);
        nodes[item->get_uid()] = item;
    }
}

void Graph::start_recording(std::vector<Node>& list){
    clear_memory();
    nodes.clear();
    edges.clear();

    for(auto& item : list){
        item.set_graph(this);
        nodes[item.get_uid()] = &item;
    }
}

bool Graph::has(const std::string& uid) const{
    return nodes.find(uid)!=nodes.end();
}

Node* Graph::get(const std::string& uid) const{
    return nodes.at(uid);
}

std::string Graph::create(const Node& node){
    Node* n = new Node(node);
    n->set_graph(this);
    n->set_user_node(false);
    nodes[n->get_uid()] = n;
    return n->get_uid();
}

void Graph::add(const Edge& edge){
    edges[edge.start_uid].push_back(new Edge(edge));
}

std::ostream& operator<<(std::ostream& os, const Graph& graph){
    for(const auto& pair : graph.nodes){
        os << "(" << pair.first << " = " << *pair.second << ")" << std::endl;
        if(graph.edges.find(pair.first)!=graph.edges.end()){
            for(const auto& e : graph.edges.at(pair.first)){
                os << "\t" << *e << std::endl;
            }
        }
    }
    return os;
}
