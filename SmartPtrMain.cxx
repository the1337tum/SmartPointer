#include "SmartPtr.h"

using namespace SmartPtrNames;

// an extremely simple linked list class
class Link {
public:
    SmartPtr<Link> next;
    int data;
};

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
