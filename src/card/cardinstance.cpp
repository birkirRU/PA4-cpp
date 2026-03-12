
#include "cardinstance.h"

int CardInstance::_nextId() {
    static int count = 1;
    return count++;
}