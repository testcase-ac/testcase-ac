#include "testlib.h"
using namespace std;

struct TestCase {
    int N, M;
    vector<string> grid;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 5);
    println(T);

    int remainingCells = rnd.next(80, 130);

    vector<TestCase> tests;
    tests.reserve(T);
    bool anyQuestion = false;

    for (int tc = 0; tc < T; ++tc) {
        int maxAreaForThis = remainingCells - (T - 1 - tc);
        if (maxAreaForThis < 1) maxAreaForThis = 1;

        int minN = 1, minM = 1;
        // Ensure at least one 2D case with N,M >= 2
        if (tc == 0 && maxAreaForThis >= 4) {
            minN = 2;
            minM = 2;
        }

        int N, M;
        // Choose N, M such that 1 <= N,M <= 8 and N*M <= maxAreaForThis
        while (true) {
            int maxN = min(8, maxAreaForThis);
            if (maxN < minN) {
                // Fallback if constraints too tight
                minN = 1;
            }
            N = rnd.next(minN, maxN);
            int maxM = maxAreaForThis / N;
            maxM = min(maxM, 8);
            if (maxM < minM) continue;
            M = rnd.next(minM, maxM);
            break;
        }

        remainingCells -= N * M;

        int type;
        if (tc == 0) type = 0;
        else type = rnd.next(0, 3); // 0..3

        vector<string> g(N, string(M, '.'));

        if (type == 0) {
            int subtype = rnd.next(0, 3);
            if (subtype == 0) {
                // All '?'
                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < M; ++j)
                        g[i][j] = '?';
            } else if (subtype == 1) {
                // All '#'
                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < M; ++j)
                        g[i][j] = '#';
            } else if (subtype == 2) {
                // All '.'
                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < M; ++j)
                        g[i][j] = '.';
            } else {
                // Chessboard of '?' and '.' with some random '#'
                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < M; ++j)
                        g[i][j] = ((i + j) % 2 == 0) ? '?' : '.';
                int extraBlues = rnd.next(0, N * M / 4 + 1);
                for (int k = 0; k < extraBlues; ++k) {
                    int ri = rnd.next(0, N - 1);
                    int rj = rnd.next(0, M - 1);
                    g[ri][rj] = '#';
                }
            }
        } else if (type == 1) {
            // Random mix with varying densities
            int pattern = rnd.next(0, 2);
            int pBlue, pQ;
            if (pattern == 0) {
                pBlue = 20; pQ = 30;
            } else if (pattern == 1) {
                pBlue = 35; pQ = 25;
            } else {
                pBlue = 10; pQ = 50;
            }
            int pWhite = 100 - pBlue - pQ;

            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    int x = rnd.next(0, 99);
                    if (x < pBlue) g[i][j] = '#';
                    else if (x < pBlue + pWhite) g[i][j] = '.';
                    else g[i][j] = '?';
                }
            }
        } else if (type == 2) {
            // Stripes with embedded '?'
            if (rnd.next(0, 1) == 0) {
                // Horizontal stripes
                for (int i = 0; i < N; ++i) {
                    char base = (i % 2 == 0 ? '#' : '.');
                    for (int j = 0; j < M; ++j) {
                        g[i][j] = base;
                    }
                }
                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < M; ++j)
                        if ((i + j + rnd.next(0, 1)) % 3 == 0)
                            g[i][j] = '?';
            } else {
                // Vertical stripes
                for (int j = 0; j < M; ++j) {
                    char base = (j % 2 == 0 ? '#' : '.');
                    for (int i = 0; i < N; ++i) {
                        g[i][j] = base;
                    }
                }
                for (int i = 0; i < N; ++i)
                    for (int j = 0; j < M; ++j)
                        if (((i * 2) + j + rnd.next(0, 1)) % 4 == 0)
                            g[i][j] = '?';
            }
        } else if (type == 3) {
            // Cross pattern plus some random blues
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    g[i][j] = '.';

            if (N >= 3 && M >= 3) {
                int midR = N / 2;
                int midC = M / 2;
                for (int j = 0; j < M; ++j) g[midR][j] = '?';
                for (int i = 0; i < N; ++i) g[i][midC] = '?';
                if (rnd.next(0, 1) == 0) g[midR][midC] = '#';
            } else {
                // Fallback small pattern
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < M; ++j) {
                        int r = rnd.next(0, 2);
                        if (r == 0) g[i][j] = '?';
                        else if (r == 1) g[i][j] = '#';
                        else g[i][j] = '.';
                    }
                }
            }
            int extra = rnd.next(0, (N * M) / 5 + 1);
            for (int k = 0; k < extra; ++k) {
                int ri = rnd.next(0, N - 1);
                int rj = rnd.next(0, M - 1);
                g[ri][rj] = '#';
            }
        }

        // Track whether any '?' exists overall
        bool hasQHere = false;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (g[i][j] == '?')
                    hasQHere = true;

        if (hasQHere) anyQuestion = true;

        tests.push_back({N, M, g});
    }

    // Ensure at least one '?' in entire input to exercise decision logic
    if (!anyQuestion) {
        TestCase &last = tests.back();
        int N = last.N, M = last.M;
        int ri = rnd.next(0, N - 1);
        int rj = rnd.next(0, M - 1);
        last.grid[ri][rj] = '?';
    }

    // Output all test cases
    for (int tc = 0; tc < T; ++tc) {
        println(tests[tc].N, tests[tc].M);
        for (int i = 0; i < tests[tc].N; ++i) {
            println(tests[tc].grid[i]);
        }
    }

    return 0;
}
