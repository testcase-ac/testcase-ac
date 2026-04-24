/* generator code */
#include "testlib.h"
#include <vector>
#include <cstdio>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of employees
    int N = rnd.next(2, 10);

    // Choose structure: chain, star or random
    string mode = rnd.next("chain|star|random");

    vector<int> parent(N);
    parent[0] = -1;
    for (int i = 1; i < N; i++) {
        if (mode == "chain") {
            parent[i] = i - 1;
        } else if (mode == "star") {
            parent[i] = 0;
        } else { // random
            parent[i] = rnd.next(0, i - 1);
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%d%c", parent[i], i + 1 == N ? '\n' : ' ');
    }

    return 0;
}
