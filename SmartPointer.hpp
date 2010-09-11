
#include <map>
#include <string>
#include <iostream>
#include "Pointers.hpp"

using namespace std;

template <typename Type>
class SmartPtr {
private:
    Pointers *smart_pointer;
    Type *pointer;

   void inline assign_pointer(Type *new_ptr) {
        if (pointer == new_ptr)
            return;

        if (pointer)
            delete_pointer();

        pointer = new_ptr;

        if (pointer)
            smart_pointer->add(pointer);
    }

    void inline delete_pointer() {
        if (! pointer)
            return;

        if (smart_pointer->del(pointer))
            delete pointer;

        pointer = NULL;
    }

public:
    SmartPtr<Type>() {
        smart_pointer = Pointers::getInstance();
        pointer = NULL;
    }

    SmartPtr<Type>(Type *copy) {
        smart_pointer = Pointers::getInstance();
        pointer = NULL;
        assign_pointer(copy);
    }

    SmartPtr<Type>(const SmartPtr<Type> &copy) {
        smart_pointer = Pointers::getInstance();
        pointer = NULL;
        assign_pointer(copy.pointer);
    }

    ~SmartPtr<Type>() {
        if (pointer)
            delete_pointer();
    }

    SmartPtr<Type>& operator=(Type *other) {
        assign_pointer(other);

        return *this;
    }

    SmartPtr<Type>& operator=(const SmartPtr<Type> &other) {
        assign_pointer(other.pointer);

        return *this;
    }

    Type &operator*() {
        return *pointer;
    }

    Type *operator->() {
        return pointer;
    }
    // Smart Pointer operators
    bool operator==(const SmartPtr<Type> &other) {
        return pointer == other.pointer;
    }
    bool operator!=(const SmartPtr<Type> &other) {
        return pointer != other.pointer;
    }
    bool operator>(const SmartPtr<Type> &other) {
        return pointer > other.pointer;
    }
    bool operator>=(const SmartPtr<Type> &other) {
        return pointer >= other.pointer;
    }
    bool operator<(const SmartPtr<Type> &other) {
        return pointer < other.pointer;
    }
    bool operator<=(const SmartPtr<Type> &other) {
        return pointer <= other.pointer;
    }

    // Type operators
    bool operator==(const Type &other) {
        return pointer == other;
    }
    bool operator!=(const Type &other) {
        return pointer != other;
    }
    bool operator>(const Type &other) {
        return pointer > other;
    }
    bool operator>=(const Type &other) {
        return pointer >= other;
    }
    bool operator<(const Type &other) {
        return pointer < other;
    }
    bool operator<=(const Type &other) {
        return pointer <= other;
    }
};
/* By Tum. */
