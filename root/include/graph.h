#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"

#include <unordered_map>
#include <exception>
#include <vector>

class Node;
class Graph {
    private:
        static Graph* instance;
        std::unordered_map<std::string, Node*> nodes;
        std::unordered_map<std::string, std::vector<Edge*> > edges;

        Graph();
        ~Graph();

        void clear_memory();
        void delete_pointers();
        double gradientRecursive(Node* node);

    public:
        static Graph* getInstance();

        double gradient(const Node& out, const Node& in);
        std::vector<double> gradient(const Node& out, const std::vector<Node>& in);
        std::vector<std::vector<double> > gradient(const Node& out, const std::vector<std::vector<Node> >& in);

        void new_recording();

        bool has(const std::string& uid) const;
        Node* get(const std::string& uid) const;
        Node* create(const Node& node);
        void add(const Edge& edge);

        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
};

#endif /* end of include guard: GRAPH_H */
