#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <random>

namespace utils {
    static std::string allowed_chars = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, allowed_chars.size()-1);

    std::string uid(size_t length=16);
}

#endif /* end of include guard: UTILS_H */
