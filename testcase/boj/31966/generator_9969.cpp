#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6); // 0..5: random patterns, 6: use sample from statement
    int N;
    vector<int> A, B;

    if (mode == 6) {
        // Use one of the samples from the statement for easy manual checking
        if (rnd.next(0, 1) == 0) {
            // Sample 1
            N = 5;
            A.assign(N + 1, 0);
            B.assign(N + 1, 0);
            A[1] = 0; B[1] = 0;
            A[2] = 1; B[2] = 0;
            A[3] = 1; B[3] = 2;
            A[4] = 3; B[4] = 1;
            A[5] = 4; B[5] = 4;
        } else {
            // Sample 2 (Ai = Bi = i-1)
            N = 7;
            A.assign(N + 1, 0);
            B.assign(N + 1, 0);
            for (int i = 1; i <= N; i++) {
                A[i] = i - 1;
                B[i] = i - 1;
            }
        }
    } else {
        // Choose N with bias towards small but sometimes medium
        int sizeType = rnd.next(0, 5);
        if (sizeType == 0) N = rnd.next(1, 3);
        else if (sizeType == 1) N = rnd.next(4, 7);
        else if (sizeType == 2) N = rnd.next(8, 12);
        else if (sizeType == 3) N = rnd.next(13, 18);
        else if (sizeType == 4) N = rnd.next(19, 25);
        else N = rnd.next(26, 40);

        A.assign(N + 1, 0);
        B.assign(N + 1, 0);

        int pattern = mode; // 0..5

        if (pattern == 0) {
            // Subtask 1/2 style: Ai = Bi = i-1 (rapidly growing duplicated tree)
            for (int i = 1; i <= N; i++) {
                A[i] = i - 1;
                B[i] = i - 1;
            }
        } else if (pattern == 1) {
            // Subtask 3 style: Ai = i-1, Bi = 0 (very skewed with many T0)
            for (int i = 1; i <= N; i++) {
                A[i] = i - 1;
                B[i] = 0;
            }
        } else if (pattern == 2) {
            // Both children are the same random previous index (many identical subtrees)
            for (int i = 1; i <= N; i++) {
                int x = rnd.next(0, i - 1);
                A[i] = x;
                B[i] = x;
            }
        } else if (pattern == 3) {
            // "Balanced-ish" splits: left prefers smaller index, right prefers larger
            for (int i = 1; i <= N; i++) {
                if (i == 1) {
                    A[i] = 0;
                    B[i] = 0;
                    continue;
                }
                int cut = rnd.next(0, i - 1);
                A[i] = rnd.next(0, cut);
                B[i] = rnd.next(cut, i - 1);
            }
        } else if (pattern == 4) {
            // Strong bias to 0 and i-1 but with some randomness
            auto chooseChild = [&](int i) -> int {
                int t = rnd.next(0, 9);
                if (t < 4) return 0;          // 40%: T0
                else if (t < 7) return i - 1; // 30%: latest tree
                else return rnd.next(0, i - 1); // 30%: arbitrary previous
            };
            for (int i = 1; i <= N; i++) {
                A[i] = chooseChild(i);
                B[i] = chooseChild(i);
            }
        } else { // pattern == 5
            // Prefer reusing only a small prefix of previous indices (small total tree size)
            for (int i = 1; i <= N; i++) {
                int maxIdx = min(i - 1, 5);                 // restrict to small indices
                int limit = rnd.next(0, maxIdx);            // upper bound within [0, maxIdx]
                A[i] = rnd.next(0, limit);
                B[i] = rnd.next(0, limit);
            }
        }
    }

    println(N);
    for (int i = 1; i <= N; i++) {
        println(A[i], B[i]);
    }

    return 0;
}
