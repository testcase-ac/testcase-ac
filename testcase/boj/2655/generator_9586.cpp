#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Brick {
    int area;
    int height;
    int weight;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 2); // 0: small crafted, 1: medium random, 2: edge
    int N;
    vector<Brick> bricks;

    if (type == 2) {
        // Edge cases
        int sub = rnd.next(0, 1);
        if (sub == 0) {
            // Single brick
            N = 1;
            bricks.resize(N);
            bricks[0].area = rnd.next(1, 50);
            bricks[0].weight = rnd.next(51, 100); // just to separate ranges a bit
            bricks[0].height = rnd.next(1, 20);
        } else {
            // 2 or 3 bricks with some (non)stackable patterns
            N = rnd.next(2, 3);
            bricks.resize(N);
            if (N == 2) {
                int pattern = rnd.next(0, 1);
                if (pattern == 0) {
                    // Stackable: brick 0 can be bottom, brick 1 top
                    int a1 = rnd.next(1, 50);
                    int a0 = rnd.next(51, 100);
                    int w1 = rnd.next(1, 50);
                    int w0 = rnd.next(51, 100);
                    bricks[0] = {a0, rnd.next(1, 20), w0};
                    bricks[1] = {a1, rnd.next(1, 20), w1};
                } else {
                    // Not stackable either way
                    int a1 = rnd.next(1, 50);
                    int a0 = rnd.next(51, 100);
                    int w0 = rnd.next(1, 50);
                    int w1 = rnd.next(51, 100);
                    bricks[0] = {a0, rnd.next(1, 20), w0};
                    bricks[1] = {a1, rnd.next(1, 20), w1};
                }
            } else { // N == 3
                // Make one clear 2-brick stack and one disturbing brick
                int a2 = rnd.next(1, 30);
                int a1 = rnd.next(31, 60);
                int a0 = rnd.next(61, 90);
                int w2 = rnd.next(1, 30);
                int w1 = rnd.next(31, 60);
                int w0 = rnd.next(61, 90);
                bricks[0] = {a0, rnd.next(1, 20), w0}; // good bottom
                bricks[1] = {a1, rnd.next(1, 20), w1}; // good middle/top
                // Disturbing brick: conflicts in area/weight with others
                int aD = rnd.next(10, 80);
                int wD = rnd.next(10, 80);
                // ensure uniqueness
                while (aD == a0 || aD == a1 || aD == a2) aD = rnd.next(10, 80);
                while (wD == w0 || wD == w1 || wD == w2) wD = rnd.next(10, 80);
                bricks[2] = {aD, rnd.next(5, 25), wD};
            }
        }
    } else if (type == 0) {
        // Small handcrafted with a clear chain
        N = rnd.next(3, 7);
        bricks.resize(N);

        int L = rnd.next(2, N); // length of guaranteed chain
        int areaStart = 200 + 5 * L;
        int weightStart = 400 + 7 * L;

        // Create a strictly decreasing chain in area and weight (0: bottom, L-1: top)
        set<int> usedA, usedW;
        for (int k = 0; k < L; ++k) {
            int a = areaStart - k;   // strictly decreasing
            int w = weightStart - 2 * k; // strictly decreasing
            usedA.insert(a);
            usedW.insert(w);
            bricks[k].area = a;
            bricks[k].weight = w;
            // Heights with some variety
            if (rnd.next(0, 3) == 0) // occasionally tall
                bricks[k].height = rnd.next(10, 30);
            else
                bricks[k].height = rnd.next(1, 15);
        }

        // Additional random bricks that may or may not fit into the chain
        for (int i = L; i < N; ++i) {
            int a, w;
            do {
                a = rnd.next(50, 260);
            } while (usedA.count(a));
            usedA.insert(a);
            do {
                w = rnd.next(50, 260);
            } while (usedW.count(w));
            usedW.insert(w);
            bricks[i].area = a;
            bricks[i].weight = w;
            bricks[i].height = rnd.next(1, 25);
        }
    } else {
        // Medium random test with unique areas and weights
        N = rnd.next(8, 20);
        bricks.resize(N);

        int M = max(50, 3 * N + 10);
        if (M > 10000) M = 10000;

        vector<int> poolA, poolW;
        for (int i = 1; i <= M; ++i) poolA.push_back(i);
        for (int i = 1; i <= M; ++i) poolW.push_back(i);
        shuffle(poolA.begin(), poolA.end());
        shuffle(poolW.begin(), poolW.end());

        for (int i = 0; i < N; ++i) {
            int a = poolA[i];
            int w = poolW[i];
            int h;
            if (rnd.next(0, 4) == 0)  // about 20% very tall
                h = rnd.next(30, 100);
            else
                h = rnd.next(1, 30);
            bricks[i] = {a, h, w};
        }
    }

    // Decide input order pattern
    int orderType = rnd.next(0, 3); // 0: random, 1: area asc, 2: area desc, 3: weight asc
    vector<int> idx(N);
    iota(idx.begin(), idx.end(), 0);

    if (orderType == 0) {
        shuffle(idx.begin(), idx.end());
    } else if (orderType == 1) {
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return bricks[i].area < bricks[j].area;
        });
    } else if (orderType == 2) {
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return bricks[i].area > bricks[j].area;
        });
    } else { // weight asc
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return bricks[i].weight < bricks[j].weight;
        });
    }

    // Output
    println(N);
    for (int pos = 0; pos < N; ++pos) {
        Brick &b = bricks[idx[pos]];
        println(b.area, b.height, b.weight);
    }

    return 0;
}
