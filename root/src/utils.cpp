#include "../include/utils.h"

std::string utils::uid(size_t length){
    std::string allowed_chars = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, allowed_chars.size()-1);
    std::string id(length, '\0');

    for (std::string::value_type& c : id) {
        c = allowed_chars[dis(gen)];
    }

    return id;
}