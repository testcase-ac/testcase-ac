#include "testlib.h"
#include <array>
#include <vector>
using namespace std;

const long long LIM = 1000000000LL;

long long clampValue(long long x) {
    if (x < -LIM) return -LIM;
    if (x > LIM) return LIM;
    return x;
}

long long randomSmall() {
    return rnd.next(-30, 30);
}

long long randomWide() {
    return rnd.next(-LIM, LIM);
}

array<array<long long, 3>, 3> randomGrid(long long lo, long long hi) {
    array<array<long long, 3>, 3> g{};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            g[i][j] = rnd.next(lo, hi);
    return g;
}

array<array<long long, 3>, 3> arithmeticGrid() {
    long long base = rnd.next(-100, 100);
    long long rowStep = rnd.next(-20, 20);
    long long colStep = rnd.next(-20, 20);

    array<array<long long, 3>, 3> g{};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            g[i][j] = base + i * rowStep + j * colStep;
    return g;
}

array<array<long long, 3>, 3> centerVoteGrid() {
    long long center = rnd.next(-1000, 1000);
    array<array<long long, 3>, 3> g = randomGrid(-50, 50);

    vector<int> lines = {0, 1, 2, 3};
    shuffle(lines.begin(), lines.end());
    int agreeing = rnd.next(1, 4);

    for (int idx = 0; idx < agreeing; ++idx) {
        int line = lines[idx];
        long long delta = rnd.next(-200, 200);
        if (line == 0) {
            g[1][0] = clampValue(center - delta);
            g[1][2] = clampValue(center + delta);
        } else if (line == 1) {
            g[0][1] = clampValue(center - delta);
            g[2][1] = clampValue(center + delta);
        } else if (line == 2) {
            g[0][0] = clampValue(center - delta);
            g[2][2] = clampValue(center + delta);
        } else {
            g[0][2] = clampValue(center - delta);
            g[2][0] = clampValue(center + delta);
        }
    }

    return g;
}

array<array<long long, 3>, 3> outerLineGrid() {
    array<array<long long, 3>, 3> g = randomGrid(-100, 100);

    long long start = rnd.next(-200, 200);
    long long step = rnd.next(-40, 40);
    g[0][0] = start;
    g[0][1] = start + step;
    g[0][2] = start + 2 * step;

    start = rnd.next(-200, 200);
    step = rnd.next(-40, 40);
    g[2][0] = start;
    g[2][1] = start + step;
    g[2][2] = start + 2 * step;

    if (rnd.next(0, 1)) {
        start = rnd.next(-200, 200);
        step = rnd.next(-40, 40);
        g[0][0] = start;
        g[1][0] = start + step;
        g[2][0] = start + 2 * step;
    }

    if (rnd.next(0, 1)) {
        start = rnd.next(-200, 200);
        step = rnd.next(-40, 40);
        g[0][2] = start;
        g[1][2] = start + step;
        g[2][2] = start + 2 * step;
    }

    return g;
}

array<array<long long, 3>, 3> boundaryGrid() {
    vector<long long> values = {-LIM, -LIM + 1, -1, 0, 1, LIM - 1, LIM};
    array<array<long long, 3>, 3> g{};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            g[i][j] = rnd.any(values);
    return g;
}

void printCase(const array<array<long long, 3>, 3>& g) {
    println(g[0][0], g[0][1], g[0][2]);
    println(g[1][0], g[1][2]);
    println(g[2][0], g[2][1], g[2][2]);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        array<array<long long, 3>, 3> g{};

        if (mode == 0) {
            long long x = randomSmall();
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    g[i][j] = x;
        } else if (mode == 1) {
            g = arithmeticGrid();
        } else if (mode == 2) {
            g = centerVoteGrid();
        } else if (mode == 3) {
            g = outerLineGrid();
        } else if (mode == 4) {
            g = boundaryGrid();
        } else {
            g = randomGrid(-1000, 1000);
            if (rnd.next(0, 4) == 0)
                g[rnd.next(0, 2)][rnd.next(0, 2)] = randomWide();
        }

        printCase(g);
    }

    return 0;
}
