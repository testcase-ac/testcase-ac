#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N (1..15), biased to have some very small and some medium cases
    int modeN = rnd.next(0, 4);
    int N;
    if (modeN == 0) N = rnd.next(1, 4);        // very small
    else if (modeN <= 2) N = rnd.next(5, 10);  // small
    else N = rnd.next(10, 15);                 // medium but still readable

    // Choose K (1..N) with different patterns
    int K;
    if (N == 1) {
        K = 1;
    } else {
        int modeK = rnd.next(0, 4);
        if (modeK == 0) {
            K = 1;                  // single train
        } else if (modeK == 1) {
            K = N;                  // everyone alone
        } else if (modeK == 2) {
            K = rnd.next(2, min(N, 5)); // small K
        } else if (modeK == 3) {
            int lo = max(2, N / 3);
            K = rnd.next(lo, N);    // relatively large K
        } else {
            K = rnd.next(1, N);     // completely random
        }
    }

    // Special-case N == 1 to avoid invalid random ranges and keep it simple
    if (N == 1) {
        println(N, K);
        println(0); // only u_11 = 0
        return 0;
    }

    // Prepare matrix u
    vector<vector<int>> u(N, vector<int>(N, 0));

    // Choose a pattern for u to get diverse structures
    int type = rnd.next(0, 5); // 0..5 => 6 patterns

    if (type == 0) {
        // All zeros
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                u[i][j] = (i == j ? 0 : 0);
    } else if (type == 1) {
        // All ones off-diagonal
        for (int i = 0; i < N; ++i) {
            u[i][i] = 0;
            for (int j = i + 1; j < N; ++j) {
                u[i][j] = u[j][i] = 1;
            }
        }
    } else if (type == 2) {
        // Fully random symmetric matrix (0..9)
        for (int i = 0; i < N; ++i) {
            u[i][i] = 0;
            for (int j = i + 1; j < N; ++j) {
                int v = rnd.next(0, 9);
                u[i][j] = u[j][i] = v;
            }
        }
    } else if (type == 3) {
        // Block structure: low inside blocks, high between blocks
        int B = rnd.next(2, min(4, N)); // number of blocks (N >= 2 here)

        // Choose B-1 cut positions between 1..N-1
        vector<int> positions;
        for (int i = 1; i <= N - 1; ++i) positions.push_back(i);
        shuffle(positions.begin(), positions.end());
        positions.resize(B - 1);
        sort(positions.begin(), positions.end());

        vector<int> blockId(N);
        int curBlock = 0;
        int posIndex = 0;
        for (int i = 0; i < N; ++i) {
            blockId[i] = curBlock;
            if (posIndex < (int)positions.size() && i + 1 == positions[posIndex]) {
                ++curBlock;
                ++posIndex;
            }
        }

        for (int i = 0; i < N; ++i) {
            u[i][i] = 0;
            for (int j = i + 1; j < N; ++j) {
                int v;
                if (blockId[i] == blockId[j]) {
                    // Inside block: often small
                    v = rnd.next(0, 3);
                } else {
                    // Between blocks: larger
                    v = rnd.next(5, 9);
                }
                u[i][j] = u[j][i] = v;
            }
        }
    } else if (type == 4) {
        // Distance-based: cost grows with |i-j|
        for (int i = 0; i < N; ++i) {
            u[i][i] = 0;
            for (int j = i + 1; j < N; ++j) {
                int d = j - i;
                int v = min(9, d); // simple monotone pattern
                u[i][j] = u[j][i] = v;
            }
        }
    } else if (type == 5) {
        // Sparse awkwardness: many zeros, some random positives
        for (int i = 0; i < N; ++i) {
            u[i][i] = 0;
            for (int j = i + 1; j < N; ++j) {
                int v;
                if (rnd.next(0, 9) < 7) {
                    v = 0; // 70% zeros
                } else {
                    v = rnd.next(1, 9);
                }
                u[i][j] = u[j][i] = v;
            }
        }
    }

    // Output
    println(N, K);
    for (int i = 0; i < N; ++i) {
        println(u[i]);
    }

    return 0;
}
