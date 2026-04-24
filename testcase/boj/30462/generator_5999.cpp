#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N for manual check, but variable
    int N = rnd.next(3, 12);
    vector<int> B(N + 1);
    // First mex can be 1 or 2
    B[1] = rnd.next(1, 2);
    // Build non-decreasing B, with random jumps allowed
    for (int i = 2; i <= N - 1; i++) {
        // Mostly keep same mex, occasionally increase
        if (rnd.next(0, 2) > 0) {
            B[i] = B[i - 1];
        } else {
            // Can jump to any valid mex up to i+1
            B[i] = rnd.next(B[i - 1] + 1, i + 1);
        }
    }
    // Final mex must be N+1
    B[N] = N + 1;
    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        printf("%d%c", B[i], i == N ? '\n' : ' ');
    }
    return 0;
}
