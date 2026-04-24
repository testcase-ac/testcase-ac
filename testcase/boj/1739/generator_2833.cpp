#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    println(T);
    for (int ti = 0; ti < T; ++ti) {
        int N = rnd.next(2, 10);
        int M = rnd.next(2, 10);
        int maxK = min(N * M, 15);
        int K = rnd.next(1, maxK);
        println(N, M, K);

        // Hyper-parameter for zero-length trips
        double zeroProb = rnd.next(0.0, 1.0);

        for (int i = 0; i < K; ++i) {
            int A, B, C, D;
            if (rnd.next() < zeroProb) {
                // zero-length: same start and end
                A = rnd.next(1, N);
                B = rnd.next(1, M);
                C = A;
                D = B;
            } else {
                int type = rnd.next(0, 2);
                if (type == 0) {
                    // horizontal move only
                    A = rnd.next(1, N);
                    C = A;
                    int t = rnd.next(-1, 1);
                    int d = rnd.wnext(M - 1, t) + 1;  // 1..M-1
                    int b1 = rnd.next(1, M - d);
                    int b2 = b1 + d;
                    if (rnd.next(0, 1) == 0) {
                        B = b1; D = b2;
                    } else {
                        B = b2; D = b1;
                    }
                } else if (type == 1) {
                    // vertical move only
                    B = rnd.next(1, M);
                    D = B;
                    int t = rnd.next(-1, 1);
                    int d = rnd.wnext(N - 1, t) + 1;  // 1..N-1
                    int a1 = rnd.next(1, N - d);
                    int a2 = a1 + d;
                    if (rnd.next(0, 1) == 0) {
                        A = a1; C = a2;
                    } else {
                        A = a2; C = a1;
                    }
                } else {
                    // both horizontal and vertical differ
                    int t1 = rnd.next(-1, 1);
                    int d1 = rnd.wnext(N - 1, t1) + 1;
                    int a1 = rnd.next(1, N - d1);
                    int a2 = a1 + d1;
                    if (rnd.next(0, 1) == 0) {
                        A = a1; C = a2;
                    } else {
                        A = a2; C = a1;
                    }
                    int t2 = rnd.next(-1, 1);
                    int d2 = rnd.wnext(M - 1, t2) + 1;
                    int b1 = rnd.next(1, M - d2);
                    int b2 = b1 + d2;
                    if (rnd.next(0, 1) == 0) {
                        B = b1; D = b2;
                    } else {
                        B = b2; D = b1;
                    }
                }
            }
            println(A, B, C, D);
        }
    }
    return 0;
}
