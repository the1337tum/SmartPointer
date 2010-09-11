#ifndef SMARTPTRNAMES_H_
#define SMARTPTRNAMES_H_
// I hate this header file. So much.
#include <string.h>
#include "List.hpp"
#include <iostream>

using namespace std;


class SmartPtrNames {
private:
    static List<void*> pointers;
public:
    SmartPtrNames() {
        pointers = new List<void*>();
    }
    void static add_pointer(void *pointer) {
        pointers.add(pointer);
    }
    void static del_pointer(void *pointer) {
        pointers.del(pointer);
    }
    void static printAllCounts(char *header); 
};
namespace SmartPtrNames {
    void SmartPtrNames::printAllCounts(){
        cout << header << endl;
        MyLink<void*> *current = pointers.getFirst();
        while(current != NULL) {
            cout << current << endl;
            current = current->next;
        }
    }
};
#endif
