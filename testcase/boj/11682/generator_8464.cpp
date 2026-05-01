#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, M;
    int sizeType = rnd.next(0, 5); // 0..5

    if (sizeType == 0) {
        // tiny (1..3) x (1..3)
        N = rnd.next(1, 3);
        M = rnd.next(1, 3);
    } else if (sizeType == 1) {
        // line (1 x K or K x 1)
        if (rnd.next(0, 1) == 0) {
            N = 1;
            M = rnd.next(2, 10);
        } else {
            N = rnd.next(2, 10);
            M = 1;
        }
    } else if (sizeType == 2) {
        // small rectangle
        N = rnd.next(2, 5);
        M = rnd.next(2, 5);
    } else if (sizeType == 3) {
        // medium square-ish
        N = rnd.next(4, 10);
        M = rnd.next(4, 10);
    } else if (sizeType == 4) {
        // medium wide
        N = rnd.next(2, 6);
        M = rnd.next(7, 12);
    } else {
        // medium tall
        N = rnd.next(7, 12);
        M = rnd.next(2, 6);
    }

    // Costs A and B
    long long A, B;
    int costType = rnd.next(0, 5); // 0..5
    if (costType == 0) {
        // A < B, B much larger
        A = rnd.next(1, 100);
        B = A * rnd.next(2, 20);
    } else if (costType == 1) {
        // A > B, A much larger
        B = rnd.next(1, 100);
        A = B * rnd.next(2, 20);
    } else if (costType == 2) {
        // A == B
        A = B = rnd.next(1, 100000);
    } else if (costType == 3) {
        // moderate random
        A = rnd.next(1, 1000);
        B = rnd.next(1, 1000);
    } else if (costType == 4) {
        // wide random
        A = rnd.next(1, 100000);
        B = rnd.next(1, 100000);
    } else {
        // extreme ratio fixed
        if (rnd.next(0, 1) == 0) {
            A = 1;
            B = 100000;
        } else {
            A = 100000;
            B = 1;
        }
    }

    vector<string> g(N, string(M, '.'));

    int patternType = rnd.next(0, 8); // 0..8

    if (patternType == 0) {
        // all '.': already done
    } else if (patternType == 1) {
        // all '#'
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                g[i][j] = '#';
    } else if (patternType == 2) {
        // checkerboard
        int offset = rnd.next(0, 1);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (((i + j + offset) & 1) == 0) g[i][j] = '#';
                else g[i][j] = '.';
            }
        }
    } else if (patternType == 3) {
        // row-based stripes
        int mode = rnd.next(0, 1);
        if (mode == 0) {
            // alternating rows
            for (int i = 0; i < N; i++) {
                char c = (i % 2 == 0 ? '#' : '.');
                for (int j = 0; j < M; j++) g[i][j] = c;
            }
        } else {
            // top half vs bottom half
            int cut = (N > 1 ? rnd.next(1, N - 1) : 0);
            char top = rnd.next(0, 1) == 0 ? '#' : '.';
            char bottom = (top == '#') ? '.' : '#';
            for (int i = 0; i < N; i++) {
                char c = (i < cut ? top : bottom);
                for (int j = 0; j < M; j++) g[i][j] = c;
            }
        }
    } else if (patternType == 4) {
        // column-based stripes
        int mode = rnd.next(0, 1);
        if (mode == 0) {
            // alternating columns
            for (int j = 0; j < M; j++) {
                char c = (j % 2 == 0 ? '#' : '.');
                for (int i = 0; i < N; i++) g[i][j] = c;
            }
        } else {
            // left vs right half
            int cut = (M > 1 ? rnd.next(1, M - 1) : 0);
            char left = rnd.next(0, 1) == 0 ? '#' : '.';
            char right = (left == '#') ? '.' : '#';
            for (int j = 0; j < M; j++) {
                char c = (j < cut ? left : right);
                for (int i = 0; i < N; i++) g[i][j] = c;
            }
        }
    } else if (patternType == 5) {
        // random noise with bias
        double probs[3] = {0.2, 0.5, 0.8};
        double p = probs[rnd.next(0, 2)];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (rnd.next() < p) g[i][j] = '#';
                else g[i][j] = '.';
            }
        }
    } else if (patternType == 6) {
        // single rectangular island of '#'
        // base all '.'
        int h = rnd.next(1, N);
        int w = rnd.next(1, M);
        int r1 = rnd.next(0, N - h);
        int c1 = rnd.next(0, M - w);
        for (int i = r1; i < r1 + h; i++)
            for (int j = c1; j < c1 + w; j++)
                g[i][j] = '#';
    } else if (patternType == 7) {
        // plus-shaped cross of '#'
        int ci = N / 2;
        int cj = M / 2;
        for (int i = 0; i < N; i++) g[i][cj] = '#';
        for (int j = 0; j < M; j++) g[ci][j] = '#';
    } else {
        // big step/hill: vertical or horizontal cut, different sides
        bool vertical = (M > 1 && (N == 1 || rnd.next(0, 1) == 0));
        if (vertical) {
            int cut = (M > 1 ? rnd.next(1, M - 1) : 0);
            bool leftHigh = rnd.next(0, 1);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    bool high = (j < cut) == leftHigh;
                    g[i][j] = high ? '#' : '.';
                }
            }
        } else {
            int cut = (N > 1 ? rnd.next(1, N - 1) : 0);
            bool topHigh = rnd.next(0, 1);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    bool high = (i < cut) == topHigh;
                    g[i][j] = high ? '#' : '.';
                }
            }
        }
    }

    println(N, M, A, B);
    for (int i = 0; i < N; i++) {
        println(g[i]);
    }

    return 0;
}
