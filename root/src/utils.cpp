#include "../include/utils.h"

namespace utils {
    unsigned long int uid(){
        return id_counter++;
    }
}
