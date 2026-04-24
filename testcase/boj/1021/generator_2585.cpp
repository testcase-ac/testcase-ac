/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N in [2..10] with slight bias toward larger
    int N = rnd.wnext(9, 2) + 2;
    // M between 1 and N
    int M = rnd.next(1, N);
    // Prepare positions 1..N
    vector<int> pos(N);
    for (int i = 0; i < N; i++) pos[i] = i + 1;
    // Shuffle and take first M as the extraction order
    shuffle(pos.begin(), pos.end());
    pos.resize(M);
    // Output
    println(N, M);
    for (int i = 0; i < M; i++) {
        if (i) printf(" ");
        printf("%d", pos[i]);
    }
    printf("\n");
    return 0;
}
