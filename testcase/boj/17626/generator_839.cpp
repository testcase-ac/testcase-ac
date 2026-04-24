#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int T1 = 1, T2 = 100, T3 = 50000;
    int t = rnd.next(0, 1), n;
    if(t == 0) {
        n = rnd.next(T1, T2);
    } else {
        n = rnd.next(T2, T3);
    }
    println(n);
}
