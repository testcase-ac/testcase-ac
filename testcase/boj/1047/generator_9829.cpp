#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

vector<int> makeLinearCoords(int N, int minStart, int maxStart, int maxStep) {
    int start = rnd.next(minStart, maxStart);
    int step = rnd.next(1, maxStep);
    vector<int> a(N);
    for (int i = 0; i < N; i++)
        a[i] = start + step * i;
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4);
    int N;
    vector<int> xsSorted, ysSorted, p, x, y, L;

    if (scenario == 0) {
        // very small, simple
        N = rnd.next(2, 4);
        xsSorted = makeLinearCoords(N, 1, 20, 3);
        ysSorted = makeLinearCoords(N, 1, 20, 3);

        p.resize(N);
        for (int i = 0; i < N; i++) p[i] = i;
        shuffle(p.begin(), p.end());

        L.resize(N);
        for (int i = 0; i < N; i++)
            L[i] = rnd.next(1, 10);
    } else if (scenario == 1) {
        // medium random, mixed lengths
        N = rnd.next(5, 9);
        xsSorted = makeLinearCoords(N, 1, 50, 5);
        ysSorted = makeLinearCoords(N, 1, 50, 5);

        p.resize(N);
        for (int i = 0; i < N; i++) p[i] = i;
        shuffle(p.begin(), p.end());

        L.resize(N);
        for (int i = 0; i < N; i++) {
            int t = rnd.next(0, 2);
            if (t == 0)      L[i] = rnd.next(1, 10);   // small
            else if (t == 1) L[i] = rnd.next(5, 30);   // medium
            else             L[i] = rnd.next(20, 70);  // large
        }
    } else if (scenario == 2) {
        // diagonal extremes: (minX,minY) and (maxX,maxY) in single trees, extremes have small L
        N = rnd.next(6, 10);
        xsSorted = makeLinearCoords(N, 1, 80, 10);
        ysSorted = makeLinearCoords(N, 1, 80, 10);

        p.assign(N, -1);
        // y indices 0..N-1 (sorted); assign extremes to x extremes
        p[0] = 0;           // minX with minY
        p[N-1] = N-1;       // maxX with maxY
        vector<int> remainingYs;
        for (int i = 1; i <= N-2; i++) remainingYs.push_back(i);
        shuffle(remainingYs.begin(), remainingYs.end());
        for (int i = 1; i <= N-2; i++)
            p[i] = remainingYs[i-1];

        L.resize(N);
        for (int i = 0; i < N; i++) {
            if (i == 0 || i == N-1)
                L[i] = rnd.next(1, 12);      // extremes not very rewarding
            else
                L[i] = rnd.next(8, 60);      // interior give more fence
        }
    } else if (scenario == 3) {
        // cross extremes: (minX,maxY) and (maxX,minY) in single trees, extremes have big L
        N = rnd.next(6, 10);
        xsSorted = makeLinearCoords(N, 1, 80, 10);
        ysSorted = makeLinearCoords(N, 1, 80, 10);

        p.assign(N, -1);
        p[0] = N-1;         // minX with maxY
        p[N-1] = 0;         // maxX with minY
        vector<int> remainingYs;
        for (int i = 1; i <= N-2; i++) remainingYs.push_back(i);
        shuffle(remainingYs.begin(), remainingYs.end());
        for (int i = 1; i <= N-2; i++)
            p[i] = remainingYs[i-1];

        L.resize(N);
        for (int i = 0; i < N; i++) {
            if (i == 0 || i == N-1)
                L[i] = rnd.next(30, 90);     // extremes very valuable to cut
            else
                L[i] = rnd.next(1, 25);      // others relatively small
        }
    } else { // scenario == 4
        // anti-diagonal mapping: x increasing, y decreasing, many points near different extremes
        N = rnd.next(8, 12);
        xsSorted = makeLinearCoords(N, 1, 80, 8);
        ysSorted = makeLinearCoords(N, 1, 80, 8);

        p.resize(N);
        for (int i = 0; i < N; i++)
            p[i] = N - 1 - i;   // anti-diagonal relationship between x and y

        L.resize(N);
        for (int i = 0; i < N; i++) {
            if (i == 0 || i == N-1)
                L[i] = rnd.next(10, 40);
            else if (i == 1 || i == N-2)
                L[i] = rnd.next(20, 60);
            else
                L[i] = rnd.next(5, 50);
        }
    }

    // Compute perimeter of bounding box of all trees
    int width  = xsSorted.back() - xsSorted.front();
    int height = ysSorted.back() - ysSorted.front();
    long long P_all = 2LL * (width + height);

    // Ensure total available fence length is enough for full bounding box
    long long sumL = accumulate(L.begin(), L.end(), 0LL);
    if (sumL < P_all) {
        int id = rnd.next(0, (int)L.size() - 1);
        L[id] += (int)(P_all - sumL);
        if (L[id] > 1000000) L[id] = 1000000; // just in case, still within constraints
    }

    // Build final coordinates per tree
    x.resize(N);
    y.resize(N);
    for (int i = 0; i < N; i++) {
        x[i] = xsSorted[i];
        y[i] = ysSorted[p[i]];
    }

    // Randomize output order
    vector<int> order(N);
    for (int i = 0; i < N; i++) order[i] = i;
    shuffle(order.begin(), order.end());

    println(N);
    for (int idx : order) {
        println(x[idx], y[idx], L[idx]);
    }

    return 0;
}
