#include "../include/utils.h"

std::string utils::uid(size_t length){
    std::string id(length, '\0');
    for (std::string::value_type& c : id) {
        c = allowed_chars[dis(gen)];
    }
    return id;
}
