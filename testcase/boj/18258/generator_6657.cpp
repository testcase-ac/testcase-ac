#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of commands: 1 to 50, biased towards smaller values
    int N = rnd.wnext(50, -2) + 1;
    // Probability (in %) to generate a push command
    int pushBias = rnd.next(30, 80);
    vector<string> others = {"pop", "size", "empty", "front", "back"};
    // Output number of commands
    println(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next(100) < pushBias) {
            int x = rnd.next(1, 100000);
            printf("push %d\n", x);
        } else {
            println(rnd.any(others));
        }
    }
    return 0;
}
