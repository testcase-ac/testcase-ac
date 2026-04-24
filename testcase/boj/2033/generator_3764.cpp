#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXP = 8;
    int p10[MAXP + 1];
    p10[0] = 1;
    for (int i = 1; i <= MAXP; i++)
        p10[i] = p10[i - 1] * 10;
    int maxN = p10[MAXP] - 1;  // 10^8 - 1 = 99,999,999

    // Three modes: uniform, near below a power of ten, near above a power of ten
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        // Uniform random over full range
        N = rnd.next(0, maxN);
    } else {
        // Pick a power p between 10^1 and 10^8
        int p = rnd.next(1, MAXP);
        // Window size up to 5 or up to one tenth of the power, whichever is smaller
        int cmax = (p10[p] / 10 < 5 ? p10[p] / 10 : 5);
        int C = rnd.next(0, cmax);
        if (mode == 1) {
            // Just below the boundary
            N = p10[p] - C;
        } else {
            // Just above the boundary
            N = p10[p] + C;
        }
        if (N < 0) N = 0;
        if (N > maxN) N = maxN;
    }

    println(N);
    return 0;
}
