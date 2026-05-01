#include "testlib.h"
using namespace std;

vector<int> genRandomIncreasing(int N, int Q) {
    vector<int> v(N);
    for (int i = 0; i < N; i++) v[i] = i + 1;
    shuffle(v.begin(), v.end());
    v.resize(Q);
    sort(v.begin(), v.end());
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 6);

    int N = 0, K = 0, Q = 0;
    vector<int> A;
    vector<int> X;

    switch (type) {
        // Tiny random
        case 0: {
            N = rnd.next(1, 10);
            K = rnd.next(1, 3);
            A.resize(N);
            for (int i = 0; i < N; i++)
                A[i] = rnd.next(1, 3);

            int style = (N == 1 ? 0 : rnd.next(0, 2)); // 0: Q=1, 1: random Q, 2: Q=N
            if (style == 0) {
                Q = 1;
                X.push_back(rnd.next(1, N));
            } else if (style == 2) {
                Q = N;
                X.resize(N);
                for (int i = 0; i < N; i++) X[i] = i + 1;
            } else {
                Q = rnd.next(1, N);
                X = genRandomIncreasing(N, Q);
            }
            break;
        }

        // All students are in the same grade as Eunho (all A_i = K)
        case 1: {
            N = rnd.next(1, 20);
            K = rnd.next(1, 3);
            A.assign(N, K);

            int style = rnd.next(0, 2); // 0: Q=1, 1: random Q, 2: Q=N
            if (style == 0) {
                Q = 1;
                X.push_back(rnd.next(1, N));
            } else if (style == 2) {
                Q = N;
                X.resize(N);
                for (int i = 0; i < N; i++) X[i] = i + 1;
            } else {
                Q = rnd.next(1, N);
                X = genRandomIncreasing(N, Q);
            }
            break;
        }

        // No student is in grade K (no A_i = K)
        case 2: {
            N = rnd.next(1, 20);
            K = rnd.next(1, 3);
            vector<int> others;
            for (int g = 1; g <= 3; g++)
                if (g != K) others.push_back(g);

            A.resize(N);
            for (int i = 0; i < N; i++)
                A[i] = rnd.any(others);

            int style = rnd.next(0, 2); // 0: Q=1, 1: random Q, 2: Q=N
            if (style == 0) {
                Q = 1;
                X.push_back(rnd.next(1, N));
            } else if (style == 2) {
                Q = N;
                X.resize(N);
                for (int i = 0; i < N; i++) X[i] = i + 1;
            } else {
                Q = rnd.next(1, N);
                X = genRandomIncreasing(N, Q);
            }
            break;
        }

        // Alternating pattern with many K's
        case 3: {
            N = rnd.next(2, 30);
            K = rnd.next(1, 3);
            vector<int> others;
            for (int g = 1; g <= 3; g++)
                if (g != K) others.push_back(g);

            A.resize(N);
            for (int i = 0; i < N; i++) {
                if (i % 2 == 0) {
                    A[i] = K;
                } else {
                    // alternate between the two other grades
                    A[i] = others[(i / 2) % 2];
                }
            }

            int style = rnd.next(0, 1); // 0: Q=N, 1: random Q
            if (style == 0) {
                Q = N;
                X.resize(N);
                for (int i = 0; i < N; i++) X[i] = i + 1;
            } else {
                Q = rnd.next(1, N);
                X = genRandomIncreasing(N, Q);
            }
            break;
        }

        // Random blocks of same grade to create segments with/without K
        case 4: {
            N = rnd.next(10, 40);
            K = rnd.next(1, 3);
            A.resize(N);

            int pos = 0;
            while (pos < N) {
                int maxLen = min(7, N - pos);
                int len = rnd.next(1, maxLen);
                int val;
                if (rnd.next(0, 1) == 0) {
                    val = K;
                } else {
                    do {
                        val = rnd.next(1, 3);
                    } while (val == K);
                }
                for (int i = 0; i < len && pos + i < N; i++)
                    A[pos + i] = val;
                pos += len;
            }

            Q = rnd.next(1, N);
            X = genRandomIncreasing(N, Q);
            break;
        }

        // Subtask-style: single query X1 = N
        case 5: {
            N = rnd.next(1, 40);
            K = rnd.next(1, 3);
            A.resize(N);
            for (int i = 0; i < N; i++)
                A[i] = rnd.next(1, 3);

            Q = 1;
            X.push_back(N);
            break;
        }

        // Maximal number of queries: Q = N, Xi = i
        case 6: {
            N = rnd.next(1, 50);
            K = rnd.next(1, 3);
            A.resize(N);
            for (int i = 0; i < N; i++)
                A[i] = rnd.next(1, 3);

            Q = N;
            X.resize(N);
            for (int i = 0; i < N; i++) X[i] = i + 1;
            break;
        }
    }

    println(N, K, Q);
    println(A);
    println(X);

    return 0;
}
