#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose a max bound for x and y ranges
    vector<long long> choicesX = {10, 20, 50, 100};
    vector<long long> choicesY = {10, 20, 50, 100};
    long long Xmax = rnd.any(choicesX);
    long long Ymax = rnd.any(choicesY);

    // Hyper-parameter: pick a case type
    // 0 = general range, 1 = A==B, 2 = C==D
    int type = rnd.next(0, 2);

    long long A, B, C, D;
    if (type == 0) {
        A = rnd.next(1LL, Xmax);
        B = rnd.next(A, Xmax);
        C = rnd.next(1LL, Ymax);
        D = rnd.next(C, Ymax);
    } else if (type == 1) {
        // Single x-value
        A = rnd.next(1LL, Xmax);
        B = A;
        C = rnd.next(1LL, Ymax);
        D = rnd.next(C, Ymax);
    } else {
        // Single y-value
        A = rnd.next(1LL, Xmax);
        B = rnd.next(A, Xmax);
        C = rnd.next(1LL, Ymax);
        D = C;
    }

    // Output the test case
    println(A, B, C, D);
    return 0;
}
