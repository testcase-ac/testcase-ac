#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> ns;

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        int count = rnd.next(1, 6);
        for (int i = 0; i < count; ++i) {
            ns.push_back(rnd.next(1, 12));
        }
    } else if (mode == 1) {
        int start = rnd.next(1, 20);
        int count = rnd.next(4, 10);
        for (int i = 0; i < count; ++i) {
            ns.push_back(min(10000000, start + i));
        }
    } else if (mode == 2) {
        int count = rnd.next(3, 8);
        for (int i = 0; i < count; ++i) {
            ns.push_back(rnd.next(50, 2000));
        }
    } else if (mode == 3) {
        int count = rnd.next(3, 8);
        for (int i = 0; i < count; ++i) {
            ns.push_back(rnd.next(1000000, 10000000));
        }
    } else {
        ns.push_back(1);
        ns.push_back(2);
        ns.push_back(3);
        ns.push_back(4);
        ns.push_back(rnd.next(5, 30));
        ns.push_back(rnd.next(9999900, 10000000));
    }

    shuffle(ns.begin(), ns.end());

    println((int)ns.size());
    for (int n : ns) {
        println(n);
    }

    return 0;
}
