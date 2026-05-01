#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A, B, C;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        // All minimum
        A = 1;
        B = 1;
        C = 1;
    } else if (mode == 1) {
        // Small A, large B (ratio large)
        A = rnd.next(1, 10);
        int maxK = 1000 / A;
        int loK = max(1, maxK - 3);
        int k = rnd.next(loK, maxK);
        B = A * k;
        // C: sometimes extreme values
        int t = rnd.next(0, 2);
        if (t == 0) C = 1;
        else if (t == 1) C = 1000;
        else C = rnd.next(2, 999);
    } else if (mode == 2) {
        // Large A, B = A (ratio 1)
        A = rnd.next(500, 1000);
        B = A;
        int t = rnd.next(0, 2);
        if (t == 0) C = 1;
        else if (t == 1) C = 1000;
        else C = rnd.next(2, 999);
    } else if (mode == 3) {
        // General random, with weighted C
        A = rnd.next(1, 1000);
        {
            int maxK = 1000 / A;
            int k = rnd.next(1, maxK);
            B = A * k;
        }
        int weight = rnd.next(-3, 3); // bias C small or large
        int x = rnd.wnext(1000, weight); // 0..999
        C = x + 1; // 1..1000
    } else {
        // Mode 4: near-maximum possible performance
        int divisorsOf1000[] = {1, 2, 4, 5, 8, 10, 20, 25, 40, 50, 100, 125, 200, 250, 500, 1000};
        int idx = rnd.next(0, 15);
        A = divisorsOf1000[idx];
        B = 1000; // multiple of any chosen A
        int t = rnd.next(0, 2);
        if (t == 0) C = 1000;        // up to 1,000,000 performance
        else if (t == 1) C = 999;
        else C = rnd.next(900, 1000);
    }

    println(A, B, C);
    return 0;
}
