#include <stdio.h>
#include <new>

template <typename Type>
class Link {
public:
    Link<Type> next; // To make sure this is what we think it is.
    void* data;

    Link(void* data) {
        this->data = data;
    }
};

template <typename Type>
class List {
private:
    Type *pointer; //------------------ Assignment Modification
    Link<Type> *first;
    Link<Type> *last;

public:
    /* Constructor and Destructors */
    List() {
        first = NULL;
        last = NULL;
    }
    
    List(Type *pointer) {
        this->pointer = pointer; //---- Assignment Modification
    }
    
    ~List() {
        Link<Type> *current = first;
        Link<Type> *next;
        while(current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
    }
    
    /* Accessors */
    int inline isEmpty() { return first == NULL; }

//  const Link<Type> *getFirst() { return first; } // Bad encapsulation
//  const Link<Type> *getLast() { return last; }   // Bad encapsulation
    
    int search(void* data) {
        if (isEmpty())
            return 0;
        
        Link<Type> *current;
        for (current = first; current != NULL; current = current->next)
            if (current.data == data)
                return 1;
        return 0;
    }
    
    /* Mutators */
    int add(void* data) {
        if(search(data)) // No duplicates - remove for preformace
            return 0;
        
        if (isEmpty()) {
            first = new Link<Type>(data);
            last = first;
        } else {
            last->next = new Link<Type>(data);
            last = last->next;
        }
        return 1;
    }
    
    void del(void* del) {
        if (isEmpty())
            return;
        
        Link<Type> *prev;
        Link<Type> *current = first;
        
        while (current != NULL) {
            if (current.data == del) {
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

