#ifndef POINTERS_H_
#define POINTERS_H_

#include <map>
#include <string>
#include <iostream>

using namespace std;

class Pointers {
private: 
    map<void*, int> pointer;
    static Pointers* pointers;

public:
    ~Pointers();
    
    void add(void *ptr);
    
    int del(void *ptr);
        
    void print(string str);
    
    // This is in the header for clarity
    static Pointers *getInstance() {
        if(! pointers)
            pointers = new Pointers();
        
        return pointers;
    }   
        
};           
#endif

