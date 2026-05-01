#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N between small and medium for manual verification
    int N = rnd.next(2, 20);
    vector<int> a1(N), a2(N);

    // Pick a pattern type to induce different behaviors
    int typ = rnd.next(0, 3);
    if (typ == 0) {
        // Fully random small values
        for (int i = 0; i < N; i++) {
            a1[i] = rnd.next(-5, 5);
            a2[i] = rnd.next(-5, 5);
        }
    } else if (typ == 1) {
        // Clustered positive segments amid negatives
        for (int i = 0; i < N; i++) {
            a1[i] = rnd.next(-10, 10);
            a2[i] = rnd.next(-10, 10);
        }
        int clusters = rnd.next(1, 3);
        for (int c = 0; c < clusters; c++) {
            int row = rnd.next(0, 1);
            int len = rnd.next(1, max(1, N/3));
            int st = rnd.next(0, N - len);
            for (int i = st; i < st + len; i++) {
                int v = rnd.next(5, 20);
                if (row == 0) a1[i] = v;
                else          a2[i] = v;
            }
        }
    } else if (typ == 2) {
        // One row all positive, other mostly negative
        int posRow = rnd.next(0, 1);
        for (int i = 0; i < N; i++) {
            if (posRow == 0) {
                a1[i] = rnd.next(1, 15);
                a2[i] = rnd.next(-15, 0);
            } else {
                a1[i] = rnd.next(-15, 0);
                a2[i] = rnd.next(1, 15);
            }
        }
    } else {
        // Alternating peaks to force up/down moves
        for (int i = 0; i < N; i++) {
            if (i % 3 == 0) {
                a1[i] = rnd.next(1, 15);
                a2[i] = rnd.next(-5, 5);
            } else if (i % 3 == 1) {
                a1[i] = rnd.next(-5, 5);
                a2[i] = rnd.next(1, 15);
            } else {
                a1[i] = rnd.next(-5, 5);
                a2[i] = rnd.next(-5, 5);
            }
        }
    }

    // Output the generated test case
    println(N);
    println(a1);
    println(a2);
    return 0;
}
