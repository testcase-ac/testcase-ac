#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    // Register the generator
    registerGen(argc, argv, 1);

    // Generate the number of testcases (N) between 2 and 6
    int T = rnd.next(1, 2);
    println(T);

    // Generate each change due, C, in [1, 500]
    for (int i = 0; i < T; i++) {
        int C = rnd.next(1, 500);
        println(C);
    }

    return 0;
}
