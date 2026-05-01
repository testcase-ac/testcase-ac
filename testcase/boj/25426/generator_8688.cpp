#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 9);

    vector<long long> A, B;
    int N = 0;

    switch (scenario) {
        // Very small / edge
        case 0: {
            N = 1;
            int type = rnd.next(0, 2);
            long long a0, b0;
            if (type == 0) {
                a0 = 0;
                b0 = rnd.next(0, 10);
            } else if (type == 1) {
                a0 = 1;
                b0 = rnd.next(0, 10);
            } else {
                a0 = rnd.next(0, 1000000000);
                b0 = rnd.next(0, 1000000000);
            }
            A.push_back(a0);
            B.push_back(b0);
            break;
        }

        // All a equal
        case 1: {
            N = rnd.next(2, 15);
            long long aVal;
            if (rnd.next(0, 1) == 0) aVal = 0;
            else aVal = rnd.next(1, 1000000000);
            for (int i = 0; i < N; ++i) {
                A.push_back(aVal);
                if (rnd.next(0, 1) == 0)
                    B.push_back(rnd.next(0, 20));
                else
                    B.push_back(rnd.next(0, 1000000000));
            }
            break;
        }

        // Strictly increasing a
        case 2: {
            N = rnd.next(3, 15);
            long long start = rnd.next(0, 10);
            long long step = rnd.next(1, 5);
            for (int i = 0; i < N; ++i) {
                A.push_back(start + step * i);
                B.push_back(rnd.next(0, 50));
            }
            break;
        }

        // Strictly decreasing a
        case 3: {
            N = rnd.next(3, 15);
            long long step = rnd.next(1, 5);
            long long start = rnd.next(0, 10) + step * (N - 1);
            for (int i = 0; i < N; ++i) {
                A.push_back(start - step * i);
                B.push_back(rnd.next(0, 50));
            }
            break;
        }

        // Random small coefficients
        case 4: {
            N = rnd.next(5, 15);
            for (int i = 0; i < N; ++i) {
                A.push_back(rnd.next(0, 20));
                B.push_back(rnd.next(0, 20));
            }
            break;
        }

        // Random large coefficients (overflow trap for int)
        case 5: {
            N = rnd.next(5, 15);
            for (int i = 0; i < N; ++i) {
                long long aVal;
                if (rnd.next(0, 1) == 0)
                    aVal = rnd.next(0, 1000000000);
                else
                    aVal = rnd.next(1000000000 - 20, 1000000000);
                A.push_back(aVal);

                long long bVal;
                if (rnd.next(0, 1) == 0)
                    bVal = rnd.next(0, 100);
                else
                    bVal = rnd.next(1000000000 - 50, 1000000000);
                B.push_back(bVal);
            }
            break;
        }

        // Many zeros in a
        case 6: {
            N = rnd.next(2, 15);
            int zeros = N / 2;
            for (int i = 0; i < N; ++i) {
                if (i < zeros)
                    A.push_back(0);
                else {
                    if (rnd.next(0, 1) == 0)
                        A.push_back(rnd.next(1, 20));
                    else
                        A.push_back(rnd.next(1, 1000000000));
                }
                B.push_back(rnd.next(0, 30));
            }
            break;
        }

        // Adversarial for wrong sorting by (a+b) instead of a
        case 7: {
            N = rnd.next(4, 10);

            // Special pair 1: low a, huge b
            A.push_back(1);
            B.push_back(100);

            // Special pair 2: higher a, small b
            A.push_back(5);
            B.push_back(0);

            // Optionally another tricky pair
            if (N >= 5) {
                A.push_back(2);
                B.push_back(50); // 2+50=52 still > 5
            }

            while ((int)A.size() < N) {
                long long aVal = rnd.next(0, 10);
                long long bVal = rnd.next(0, 20);
                A.push_back(aVal);
                B.push_back(bVal);
            }
            break;
        }

        // Multiple equal groups of a
        case 8: {
            N = rnd.next(6, 15);
            int groups = rnd.next(2, min(4, N));
            int remaining = N;
            for (int g = 0; g < groups; ++g) {
                int leftGroups = groups - g;
                int sz = (g == groups - 1) ? remaining : rnd.next(1, remaining - (leftGroups - 1));
                remaining -= sz;
                long long aVal = g * 5 + rnd.next(0, 2); // distinct-ish, small
                for (int i = 0; i < sz; ++i) {
                    A.push_back(aVal);
                    B.push_back(rnd.next(0, 40));
                }
            }
            break;
        }

        // All zeros (trivial sum)
        case 9: {
            N = rnd.next(1, 15);
            for (int i = 0; i < N; ++i) {
                A.push_back(0);
                B.push_back(0);
            }
            break;
        }
    }

    // Optional shuffle of the functions to vary order
    if (rnd.next(0, 1) == 1) {
        int n = (int)A.size();
        vector<int> idx(n);
        for (int i = 0; i < n; ++i) idx[i] = i;
        shuffle(idx.begin(), idx.end());
        vector<long long> AA, BB;
        AA.reserve(n);
        BB.reserve(n);
        for (int i = 0; i < n; ++i) {
            AA.push_back(A[idx[i]]);
            BB.push_back(B[idx[i]]);
        }
        A.swap(AA);
        B.swap(BB);
    }

    println((int)A.size());
    for (int i = 0; i < (int)A.size(); ++i)
        println(A[i], B[i]);

    return 0;
}
