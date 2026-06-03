#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int t;
    vector<int> queries;

    if (mode == 0) {
        t = rnd.next(1, 12);
        for (int i = 0; i < t; ++i) {
            queries.push_back(rnd.next(1, 20));
        }
    } else if (mode == 1) {
        t = rnd.next(10, 80);
        for (int i = 0; i < t; ++i) {
            queries.push_back(rnd.next(1, 3000));
        }
    } else if (mode == 2) {
        t = rnd.next(20, 100);
        for (int i = 0; i < t; ++i) {
            queries.push_back(rnd.next(2500, 3000));
        }
    } else if (mode == 3) {
        t = rnd.next(20, 120);
        int values = rnd.next(1, 8);
        vector<int> pool;
        for (int i = 0; i < values; ++i) {
            pool.push_back(rnd.next(1, 3000));
        }
        for (int i = 0; i < t; ++i) {
            queries.push_back(rnd.any(pool));
        }
    } else {
        t = 1000;
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 4) == 0) {
                queries.push_back(rnd.next(1, 50));
            } else {
                queries.push_back(rnd.next(2950, 3000));
            }
        }
    }

    println(t);
    for (int n : queries) {
        println(n);
    }

    return 0;
}
