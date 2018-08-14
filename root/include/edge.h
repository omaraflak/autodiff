#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <string>

struct Edge {
    unsigned long int start_uid;
    unsigned long int end_uid;
    double weight;

    Edge(const unsigned long int& start_uid, const unsigned long int& end_uid, const double& weight){
        this->start_uid = start_uid;
        this->end_uid = end_uid;
        this->weight = weight;
    }

    Edge(const Edge& edge){
        this->start_uid = edge.start_uid;
        this->end_uid = edge.end_uid;
        this->weight = edge.weight;
    }

    friend std::ostream& operator<<(std::ostream& os, const Edge& edge){
        os << "(" << edge.start_uid << ", " << edge.end_uid << ", " << edge.weight << ")";
        return os;
    }
};

#endif /* end of include guard: EDGE_H */
