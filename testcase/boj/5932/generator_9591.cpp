#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    vector<int> p;

    // 10% of time: fixed sample from statement
    if (rnd.next(0, 9) == 0) {
        N = 5;
        p = {3, 5, 4, 2, 1};
    } else {
        // Choose size category
        int sizeCategory = rnd.next(0, 4);
        if (sizeCategory == 0) {
            N = 1;
        } else if (sizeCategory == 1) {
            N = 2;
        } else if (sizeCategory == 2) {
            N = rnd.next(3, 10);
        } else if (sizeCategory == 3) {
            N = rnd.next(10, 25);
        } else {
            N = rnd.next(25, 80);
        }

        p.resize(N);
        for (int i = 0; i < N; i++)
            p[i] = i + 1;

        int pattern = rnd.next(0, 5);

        switch (pattern) {
            case 0: {
                // Completely random permutation
                shuffle(p.begin(), p.end());
                break;
            }
            case 1: {
                // A rotation of 1..N (already "acceptable" order)
                if (N > 1) {
                    int k = rnd.next(0, N - 1);
                    rotate(p.begin(), p.begin() + k, p.end());
                }
                break;
            }
            case 2: {
                // Reversed order
                reverse(p.begin(), p.end());
                break;
            }
            case 3: {
                // Rotation with a few adjacent swaps (nearly acceptable)
                if (N > 1) {
                    int k = rnd.next(0, N - 1);
                    rotate(p.begin(), p.begin() + k, p.end());
                    int maxSwaps = max(1, N / 3);
                    int swaps = rnd.next(1, maxSwaps);
                    for (int s = 0; s < swaps; s++) {
                        int i = rnd.next(0, N - 2);
                        swap(p[i], p[i + 1]);
                    }
                }
                break;
            }
            case 4: {
                // Local block shuffles, then optional rotation
                int i = 0;
                while (i < N) {
                    int rem = N - i;
                    int len = rnd.next(1, min(4, rem));
                    shuffle(p.begin() + i, p.begin() + i + len);
                    i += len;
                }
                if (N > 1 && rnd.next(0, 1) == 1) {
                    int k = rnd.next(0, N - 1);
                    rotate(p.begin(), p.begin() + k, p.end());
                }
                break;
            }
            case 5: {
                // Cut a random segment and insert it elsewhere (block move)
                if (N <= 3) {
                    shuffle(p.begin(), p.end());
                } else {
                    int l = rnd.next(0, N - 2);
                    int r = rnd.next(l + 1, N - 1);
                    vector<int> seg(p.begin() + l, p.begin() + r + 1);
                    p.erase(p.begin() + l, p.begin() + r + 1);
                    int pos = rnd.next(0, (int)p.size());
                    p.insert(p.begin() + pos, seg.begin(), seg.end());
                    if (rnd.next(0, 1) == 1)
                        reverse(p.begin(), p.end());
                }
                break;
            }
        }
    }

    println(N);
    for (int i = 0; i < N; i++)
        println(p[i]);

    return 0;
}
