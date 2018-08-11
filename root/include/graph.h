#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"

#include <exception>
#include <vector>
#include <map>

class Node;
class Graph {
    private:
        std::map<std::string, Node*> nodes;
        std::map<std::string, std::vector<Edge*> > edges;

        void clear_memory();
        double gradientRecursive(Node* node, const std::string& stop_uid);

    public:
        Graph();
        Graph(std::initializer_list<Node*> list);
        Graph(std::vector<Node>& list);
        ~Graph();

        double gradient(const Node& out, const Node& in);
        std::vector<double> gradient(const Node& out, const std::vector<Node>& in);
        
        void start_recording(std::initializer_list<Node*> list);
        void start_recording(std::vector<Node>& list);
        void start_recording();

        bool has(const std::string& uid) const;
        Node* get(const std::string& uid) const;
        std::string create(const Node& node);
        void add(const Edge& edge);

        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
};

#endif /* end of include guard: GRAPH_H */
