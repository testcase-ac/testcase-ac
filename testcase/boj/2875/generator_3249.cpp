#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters to diversify N and M in [0,10]
    int t1 = rnd.next(-1, 1);
    int t2 = rnd.next(-1, 1);
    int N = rnd.wnext(11, t1);  // number of female students
    int M = rnd.wnext(11, t2);  // number of male students

    // Determine K (intern count) with small/medium/large modes
    int total = N + M;
    int K;
    if (total == 0) {
        K = 0;
    } else {
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            // few interns
            K = rnd.next(0, total / 3);
        } else if (mode == 1) {
            // moderate interns
            K = rnd.next(total / 3, (2 * total) / 3);
        } else {
            // many interns
            K = rnd.next((2 * total) / 3, total);
        }
    }

    // Output a single test case
    println(N, M, K);
    return 0;
}
