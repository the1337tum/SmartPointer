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
 *  class declaration     |    constructor function, with the an address
 *       |  pointer type  |    to an instance of the sub structure
 *       |    |       |                          |
 * |-------| |-|  |-------|   |--------------------------------|
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

#include "SmartPtr.h"

using namespace SmartPtrNames;

// a class that takes up a lot of memory
class Big {
public:
    int bigArray[1000000];
};

// a function to test whether scope is handled properly
void testScope()
{
    SmartPtr<Big> b = new Big();
    SmartPtr<Big> b2 = b;
    printAllCounts("testScope");
}

// an extremely simple linked list class
template <typename Type>
class Link {
public:
    Link<Type> next;
    int data;
};

template <typename Type>
struct List {
    Link <SmartPtr<Type>*> list; // The pointers (**)
    Type *pointer;               // The pointer  (*)
};

// a smart pointer class
template <typename Type>
class SmartPtr{
private:
    List<Type> *list; // The root pointer - don't touch!
    
    /* Mutators */
    void create_list(List<Type> *pointer) {
        if (this->list)
            delete_list();

        this->list = list;
        list->add(this);
    }

    void delete_list() {
        if (! list)
            return;
        
        list->del(this)
        if (list->isEmpty())
            delete list;

        >list = NULL;
    }

public:
    /* Accessors */
    const List<Type> *get_list() {
        return list;
    }
    
    /* Operators */
    void operator delete (void *pointer) {
        delete_list();       

        if (pointer)
            free(pointer);
    }

    Smart_ptr<Type>& operator=(Smart_ptr<Type> const &copy) {
        if (this == &copy) // a = a
            return *this;
        
        delete_list();
        create_list(copy.get_list());
        
        return *this;
    }
    
    Type &operator*() {
        return &(*(list->pointer));
    }

    Type *operator->() {
        return list->pointer;
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
}

int main(int argc, char *argv[])
{
    // some simple tests
    SmartPtr<int> p = new int();
    *p = 5;
    printAllCounts("first");
    SmartPtr<int> q = p;
    cout << "p = " << *p << " q = " << *q << endl;
    printAllCounts("second");
    SmartPtr<int> r = new int();
    *r = 2;
    printAllCounts("third");
    p = r;
    cout << "p = " << *p << " q = " << *q << " r = " << *r << endl;
    printAllCounts("fourth");
    q = p;
    cout << "p = " << *p << " q = " << *q << " r = " << *r << endl;
    q = p = r = 0;
    printAllCounts("fifth");

    // test a circular linked list, there should be no way of deleting
    // this list - in other words, garbage is created
    SmartPtr<Link> l = new Link();
    l->data = 1;
    assert(l->data == (*l).data);
    l->next = new Link();
    l->next->next = new Link();
    l->next->next->next = l;
    l = 0;
    printAllCounts("after linked list");

    // test the allocation/deletion of big objects
    // Warning: make sure that your code deallocates properly before
    // trying to do this. If it doesn't deallocate, then you will be
    // trying to allocate 1G of memory which will usually mean bad
    // things. If it does deallocate, you'll only use 1M of memory for
    // this part.
    SmartPtr<Big> b = new Big();
    for (int i=0; i<1000; i++)
    {
        b = new Big();
    }
    printAllCounts("after big");

    // test that scoping doesn't cause any problem
    testScope();
    printAllCounts("last");

    return 1;
}
