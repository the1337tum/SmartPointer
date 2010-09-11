#ifndef _Link_H_
#define _Link_H_

#include <stdio.h>
#include <new>

// God damn that name is annoying..
template <typename Type>
class MyLink {
public:
    MyLink<Type> *next; // To make sure this is what we think it is.
    Type data;

    MyLink(Type data) {
        this->data = data;
    }
};

template <typename Type>
class List {
private:
    MyLink<Type> *first;
    MyLink<Type> *last;

public:
    void *pointer; //------------------ Assignment Modification

    /* Constructor and Destructors */
    List() {
        first = NULL;
        last = NULL;
    }
    
    List(void *pointer) {
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

    MyLink<Type> *getFirst() { return first; }
    MyLink<Type> *getLast() { return last; }
    
    int search(Type data) {
        if (isEmpty())
            return 0;
        
        MyLink<Type> *current;
        for (current = first; current != NULL; current = current->next)
            if (current->data == data)
                return 1;
        return 0;
    }
    
    /* Mutators */
    int add(Type data) {
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
    
    void del(Type del) {
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
#endif
