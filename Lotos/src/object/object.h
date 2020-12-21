//
// Created by Lado on 21/5/20.
//

#ifndef LOTOS_OBJECT_H
#define LOTOS_OBJECT_H

#include <string>

class object {
public:
    object();
    std::string getClass();
    bool equals(object& obj);
    object clone();
    std::string toString();
};

object::object() {}

std::string object::getClass() {
    return "";
}

bool object::equals(object &obj) {
    if (this == &obj) {
        return true;
    } else {
        return false;
    }
}

object object::clone() {
    return *this;
}

std::string object::toString() {
    return typeid(object).name();
}


#endif //LOTOS_OBJECT_H
