#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N = rnd.next(5, 8);
    cout << N << "\n";
    
    vector<int> pool;
    int mn = rnd.next(1, 99);
    int mx = rnd.next(mn + 1, 100);
    for (int i = mn; i <= mx; i++) {
        pool.push_back(i);
    }
    if(rnd.next(0, 1)) {
        pool.push_back(1);
    }
    if(rnd.next(0, 1)) {
        pool.push_back(100);
    }
    for (int i = 0; i < N; i++) {
        vector<int> row;
        for (int j = 0; j < N; j++) {
            row.push_back(rnd.any(pool));
        }
        println(row);
    }
    
    return 0;
}
