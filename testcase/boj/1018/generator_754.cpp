#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = rnd.next(8, 16);
    int M = rnd.next(8, 16);

    println(N, M);

    double density = rnd.next();
    for (int i = 0; i < N; i++) {
        string row = "";
        for (int j = 0; j < M; j++) {
            row += (rnd.next() < density ? 'B' : 'W');
        }
        println(row);
    }

    return 0;
}
