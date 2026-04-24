#include "testlib.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5); 
    println(T);

    for (int t = 0; t < T; ++t) {
        int M = rnd.next(1, 40);
        int N = rnd.next(1, 40);
        int x = rnd.next(1, M);
        int y = rnd.next(1, N);
        println(M, N, x, y);
    }

    return 0;
}
