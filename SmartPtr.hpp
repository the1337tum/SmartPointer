#include "List.hpp"

#include <stdio.h>
#include <stdlib.h>

/** 
 * To explain:
 *  List<Type> *pointer; - the smart pointers (which this is one of)
 *  pointer->pointer;    - the what is being pointed to
**/

using namespace std;

// A SmartPtr class
template <typename Type>
class SmartPtr{
private:
    List<Type> *pointer; // The root pointer - don't touch!
    
    /* Mutators */
    void inline assign_pointer(List<Type> *new_ptr) {
        if (pointer == new_ptr) // a = a
            return;
        
        if (pointer)
            delete_pointer();
        
        pointer = new_ptr;
        
        if (pointer)
            pointer->add(this);
    }
    
    void inline delete_pointer() {
        if (! pointer)
            return;
        
        pointer->del(this);
        
        if (pointer->isEmpty())
            delete pointer;
        
        pointer = NULL;
    }

public:
    /* Constructors and Destructors */
    SmartPtr(Type *pointee) {
        assign_pointer(new List<Type>(pointee));
    }
    
    ~SmartPtr() {
        delete pointer;
    }
    
    /* Accessors */
    List<Type> *get_pointer() {
        return pointer;
    }
    
    /* Operators */
    void operator delete(void *memory) {
        delete_pointer();
        
        if (memory)
            free(memory);
    }

    Type& operator=(Type &new_ptr) {
        SmartPtr(&new_ptr);
         
        return *this;
    }
    
    SmartPtr<Type>& operator=(SmartPtr<Type> &copy) {
        assign_pointer(copy.get_pointer());
        
        return *this;
    }
    
    Type &operator*() {
        return (*pointer->pointer);
    }
    
    Type *operator->() {
        return pointer->pointer;
    }
    
    bool operator==(const SmartPtr<Type> &other) {
        return pointer->pointer == other.get_pointer();
    }
    
    bool operator!=(const SmartPtr<Type> &other) {
        return pointer->pointer != other.get_pointer();
    }
    
    bool operator<(const SmartPtr<Type> &other) {
        return pointer->pointer < other.get_pointer();
    }
    
    bool operator<=(const SmartPtr<Type> &other) {
        return pointer->pointer <= other.get_pointer();
    }
    
    bool operator>(const SmartPtr<Type> &other) {
        return pointer->pointer > other.get_pointer();
    }
    
    bool operator>=(const SmartPtr<Type> &other) {
        return pointer->pointer >= other.get_pointer();
    }
};/* End SmartPtr - By Tum. */

