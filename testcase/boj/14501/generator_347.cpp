#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N;
    if(rnd.next() < 0.5) {
        N = rnd.next(1, 5);
    } else {
        N = rnd.next(6, 15);
    }
    println(N);
    for(int i = 0; i < N; i++) {
        int T = rnd.next(1, 5);
        int p = rnd.next(1, 10);
        println(T, p);
    }
}
