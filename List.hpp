/**
 * Singly Linked List (SLL) - This is a heavy root class when compared
 * to the extreme lightweight lists, so multi dimensional cost shoots up
 * and must be used sparingly.
 * 
 * --- Requirements ---
 * 
 * None.
 * 
 * --- Use ---
 * 
 *  Using an identifier (ID) is entirely optional
 * 
 *  Note: >> is the right shift operator, to get around this put a space 
 *        in between the greater than signs > >
 *  
 *                local variable
 *  class declaration |
 *    | pointer type  |     constructor function
 *    |     |         |              |
 * |------|***|-| |-----|   |------------------|
 * SLL<SLL<int> > 2d_list = new SLL<SLL<int> >();
 *  
 * Or you can add dimensions manually for nicer syntax.. 
 *  but is it *really* worth it..?
 * 
 * --- Preformance ---
 * 
 * SLLs preform well when used with small amounts of frequently constructed 
 * and destructed data. They are prone to fragmentation, so excel in 
 * environments where data is already fragmented, frequently changing and 
 * highly varable in size/quantity.
 * 
 * Accessors and mutators
 *  Log(n)  n = the length of the list
 *  But: Lists are extremely cheap to construct, so has a low constant
 *  value, and the list is stored in memory runs 
 *      - taking advantage of fast sequencial access.
 * 
 * Constructors
 *  Substructures are not constructed, so cheap initilisation
 * 
 * Destructors
 *  If you're not clearing up after yourself, you'll get a preformance hit 
 *  at destruction.
**/

#include <stdio.h>
#include <new>

// In this version, pointers are used for identification

template <typename Type>
class Link {
public:
    Link<Type> next;
    void *data;
};

template <typename Type>
class List {
private:
    Type *pointee; //------------------ Assignment Modification
    List<Type> *first;
    List<Type> *last;

public:
    /* Constructor and Destructors */
    SLL() {
        first = NULL;
        last = NULL;
    }
    
    SLL(Type *pointee) {
        this->pointee = pointee; //---- Assignment Modification
    }
    
    ~SLL() {
        List<Type> *current = first;
        List<Type> *next;
        while(current != NULL) {
            next = current->next;
            delete current;
            current = next;
        }
    }
    
    /* Accessors */
    int inline isEmpty() { return first == NULL; }
    
    const List<Type> *getFirst() { return first; }
    
    const List<Type> *getLast() { return last; }
    
    int search(void *data) {
        if (isEmpty())
            return 0;
        
        List<Type> *current;
        for (current = first; current != NULL; current = current->next)
            if (current.data == data)
                return 1;
        return 0;
    }
    
    /* Mutators */
    int add(void *data) {
        if(search(data)) // No duplicates - remove for preformace
            return 0;
        
        if (isEmpty()) {
            first = new List<Type>();
            first.data = data;
        } else {
            last->next = new List<Type>();
            last->next.data = data;
            last = last->next;
        }
        return 1;
    }
    
    void del(void *del) {
        if (isEmpty())
            return;
        
        List<Type> *prev;
        List<Type> *current = first;
        
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
};/*End List*/

