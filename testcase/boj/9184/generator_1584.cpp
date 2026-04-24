#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 3);
    if(rnd.next() < 0.5 ) T = 10;
    int mn = rnd.next(0, 20), mx = rnd.next(mn, 20);
    vector<int> pool;
    for(int i = mn; i <= mx; i++) pool.push_back(i);
    if(rnd.next() < 0.5) {
        pool.push_back(rnd.next(-9, -2));
    }
    if(rnd.next() < 0.5) {
        pool.push_back(rnd.next(21, 30));
    }
    while (T--) {
        int a = rnd.any(pool);
        int b = rnd.any(pool);
        int c = rnd.any(pool);
        println(a, b, c);
    }
    println(-1, -1, -1);
}
