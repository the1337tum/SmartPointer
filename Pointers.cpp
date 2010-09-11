#include "Pointers.hpp"

using namespace std;

Pointers* Pointers::pointers = 0;

void Pointers::add(void *ptr) {
    pointer[ptr]++;
}

Pointers::~Pointers() {
    delete pointers;
}   

// returns true if needs deleted
int Pointers::del(void *ptr) {
    pointer[ptr]--;
    
    if (! pointer[ptr]) {
        pointer.erase(ptr);
        return 1;
    }
    return 0;
}   
    
void Pointers::print(string str) {
    cout << str << "begin" << endl;
    for(map<void*, int>::iterator it = pointer.begin();
        it != pointer.end();
        it++){
        cout << "location = " << it->first << ", count = "
             << it->second << endl;
    }
    cout << str << "end" << endl;
}

