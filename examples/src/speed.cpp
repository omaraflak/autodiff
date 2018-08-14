#include <iostream>
#include <iomanip>
#include <cassert>
#include <ctime>
#include <chrono>

#include "../../root/include/graph.h"

template <class T>
std::vector<std::vector<T> > dot(const std::vector<std::vector<T> > & a, const std::vector<std::vector<T> >& b){
    assert(a[0].size()==b.size());

    T w=0;
    std::vector<std::vector<T> > result(a.size(), std::vector<T>(b[0].size()));
    for (int i=0 ; i<a.size() ; i++){
        for (int j=0 ; j<b[0].size() ; j++){
            for (int h=0 ; h<b.size() ; h++){
                w += a[i][h]*b[h][j];
            }
            result[i][j] = w;
            w=0;
        }
    }

    return result;
}

template <class T>
std::vector<std::vector<T> > getRandom(const int& height, const int& width, T t){
    std::vector<std::vector<T> > mat(height, std::vector<T>(width));
    for(auto& v : mat){
        for(auto& e : v){
            e = rand()/(double)RAND_MAX;
        }
    }
    return mat;
}

int main(int argc, char const *argv[]) {
    srand(time(0));

    Graph* graph = Graph::getInstance();

    int size = 30;
    std::vector<std::vector<double> > a = getRandom(size, size, double());
    std::vector<std::vector<double> > b = getRandom(size, size, double());
    std::vector<std::vector<Node> > c = getRandom(size, size, Node());
    std::vector<std::vector<Node> > d = getRandom(size, size, Node());

    std::cout << std::fixed;
    std::cout << std::setprecision(10);

    std::cout << "Running with double... ";
    std::cout.flush();
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<double> > ab = dot(a, b);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s" << std::endl;

    std::cout << "Running with Node... ";
    std::cout.flush();
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<Node> > cd = dot(c, d);
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s" << std::endl;

    std::cout << "Yet to be improved..." << std::endl;
    return 0;
}
