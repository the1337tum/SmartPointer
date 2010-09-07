/**
 * The Smart Pointer Class - Used for automatic memory allocation.
 * 
 *      --- Requirements ---
 * 
 * The operators provided here must be provided by the substructure 
 * as well.
 * 
 *      --- Use ---
 * 
 * Used and initilised like normal templates, but instead of deleting
 * the object on delete and initilising as you would expect, it 
 * simply keeps track of the number of pointers allocated with an 
 * itterable data structure which records the addresses of what 
 * variables addressing it.
 * 
 * Declare the substructure node as you would normally, then pass 
 * the pointer into the constructor to keep memory of the same type 
 * in a common place.
 * 
 *                 local variable
 *  class declaration    |    constructor function, with the an address
 *       | pointer type  |    to an instance of the sub structure
 *       |    |          |                   |
 * |--------|***| |-------|   |--------------------------------|
 * Smart_ptr<int> itterator = new Smart_ptr<int>(&sub_structure);
 * 
 * When used with already declared variables, the address it's given 
 * is the address of the smart pointer you're using. Here we have a 
 * Structure class storing an address to our smart pointer.
 * 
 * Smart_ptr<int> = Structure.some_smart_int = iterator;
 * 
 *      --- Preformance ---
 * 
 * The memory allocation scheme of the sub structure has a higher 
 * effect on preformance, with respect to both memory and time than
 * the interface provided by this class; so keep in mind what
 * substructure you're using.
 *
 * The default substructure - a singly linked list (SLL) - is very 
 * lightweight and is very adaptive memory, but suffers from memory
 * fragmentation.
 *
 * Accessors and Mutators
 *  Log(n)   n = the number of pointers
 *
 * Constructors
 *  Sub structure root node is constructed
 * 
 * Destructors
 *  You *must* remember to use the destructor if you plan to use this 
 *  in highly variable, long running objects or functions. This is very
 *  very stupid garbage collection.
 *  If you're not clearing up after yourself, you'll get a preformance
 *  hit at destruction.
 *   
 *  Will not destroy cycles where both 
 *     e.g  a = b;     pointers refer to  
 *          b = a;     each other.
 **/

#include "../data_structures/SLL.hpp"

using namespace std;
/* To explain:
 *  List<Type> *pointer;    - the smart pointers
 *  pointer->pointer;       - the what is being pointed to
 */
template <typename Type>
class Smart_ptr{
private:
    List<Type> *pointer; // The root pointer - don't touch!
    
    /* Mutators */
    void inline create_pointer(List<Type> *pointer) {
        if (this->pointer)
            delete_list();
        
        this->pointer = pointer;
        
        if (this->pointer)
            pointer->add(this);
    }
    
    void inline delete_pointer() {
        if (! pointer)
            return;
        
        pointer->del(this)
        
        if (pointer->isEmpty())
            delete pointer;
        
        pointer = NULL;
    }

public:
    /* Constructors and Destructors */
    Smart_ptr(Type *pointee) {
        pointer = new List<Type>(pointee);
    }
    
    ~Smart_ptr() {
        delete pointer;
    }
    
    /* Accessors */
    const List<Type> *get_pointer() {
        return pointer;
    }
    
    /* Operators */
    void operator delete(void *memory) {
        delete_pointer();
        
        if (memory)
            free(memory);
    }
    
    Smart_ptr<Type>& operator=(Smart_ptr<Type> const &copy) {
        if (this == &copy) // a = a
            return *this;
        
        delete_pointer();
        create_pointer(copy.get_pointer());
        
        return *this;
    }
    
    Type &operator*() {
        return &(*(pointer->pointer));
    }
    
    Type *operator->() {
        return pointer->pointer;
    }
    
    int operator==() {
        
    }
    
    int operator!=() {
        
    }
    
    int operator<() {
        
    }
    
    int operator<=() {
        
    }
    
    int operator>() {
        
    }
    
    int operator>=() {
        
    }
};

