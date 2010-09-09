#include <stdio.h>
#include <new>

// God damn that name is annoying..
template <typename Type>
class MyLink {
public:
    MyLink<Type> *next; // To make sure this is what we think it is.
    void* data;

    MyLink(void* data) {
        this->data = data;
    }
};

template <typename Type>
class List {
private:
    MyLink<Type> *first;
    MyLink<Type> *last;

public:
    Type *pointer; //------------------ Assignment Modification

    /* Constructor and Destructors */
    List() {
        first = NULL;
        last = NULL;
    }
    
    List(Type *pointer) {
        this->pointer = pointer; //---- Assignment Modification
    }
    
    ~List() {
        MyLink<Type> *current = first;
        MyLink<Type> *next;
        while(current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
    }
    
    /* Accessors */
    int inline isEmpty() { return first == NULL; }

//  const MyLink<Type> *getFirst() { return first; } // Bad encapsulation
//  const MyLink<Type> *getLast() { return last; }   // Bad encapsulation
    
    int search(void* data) {
        if (isEmpty())
            return 0;
        
        MyLink<Type> *current;
        for (current = first; current != NULL; current = current->next)
            if (current->data == data)
                return 1;
        return 0;
    }
    
    /* Mutators */
    int add(void* data) {
        if(search(data)) // No duplicates - remove for preformace
            return 0;
        
        if (isEmpty()) {
            first = new MyLink<Type>(data);
            last = first;
        } else {
            last->next = new MyLink<Type>(data);
            last = last->next;
        }
        return 1;
    }
    
    void del(void* del) {
        if (isEmpty())
            return;
        
        MyLink<Type> *prev;
        MyLink<Type> *current = first;
        
        while (current != NULL) {
            if (current->data == del) {
                if (prev == NULL) {                 // First
                    first = current->next;
                    delete current;
                    return; 
                } else if (current->next == NULL) { // Last
                    prev->next = NULL;
                    last = prev;
                    delete current; 
                    return;
                } else {                            // Middle
                    prev->next = current->next;
                    delete current;
                    return;
                }
            }
            prev = current;
            current = current->next; 
        }
    }
};/* End List - By Tum. */

