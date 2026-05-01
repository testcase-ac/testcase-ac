#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: small, tiny, medium, large
    int nm = rnd.next(0, 3);
    int N;
    if (nm == 0) {
        N = 1;
    } else if (nm == 1) {
        N = rnd.next(2, 3);
    } else if (nm == 2) {
        N = rnd.next(5, 20);
    } else {
        N = rnd.next(90, 100);
    }

    // Decide if max-T and min-B come from same submission
    bool same;
    if (N == 1) {
        same = true;
    } else {
        // ~30% same, ~70% distinct
        same = rnd.next(0, 9) < 3;
    }

    // Pick indices
    int i_max = rnd.next(0, N - 1);
    int i_min = i_max;
    if (!same) {
        do {
            i_min = rnd.next(0, N - 1);
        } while (i_min == i_max);
    }

    // Choose T_max with edge and random cases
    int tcase = rnd.next(0, 3);
    int T_max;
    if (tcase == 0) {
        T_max = 1;
    } else if (tcase == 1) {
        T_max = 1500;
    } else if (tcase == 2) {
        int k = rnd.next(1, 214); // 7*k up to 1498
        T_max = 7 * k;
    } else {
        T_max = rnd.next(1, 1500);
    }

    // Choose B_min with edge and random cases
    int bcase = rnd.next(0, 3);
    int B_min;
    if (bcase == 0) {
        B_min = 50;
    } else if (bcase == 1) {
        B_min = 5000;
    } else if (bcase == 2) {
        int k = rnd.next(8, 714); // 7*k from 56..4998
        B_min = 7 * k;
    } else {
        B_min = rnd.next(50, 5000);
    }

    // Fix for distinct constraints
    if (!same) {
        if (T_max <= 1) T_max = 2;
        if (B_min >= 5000) B_min = 4999;
    }

    // Prepare submissions
    vector<pair<int,int>> v(N, {0,0});
    // Fill special ones
    if (same) {
        v[i_max] = {T_max, B_min};
    } else {
        // max-T submission
        int B_for_max = rnd.next(max(B_min + 1, 50), 5000);
        v[i_max] = {T_max, B_for_max};
        // min-B submission
        int T_for_min = rnd.next(1, T_max - 1);
        v[i_min] = {T_for_min, B_min};
    }
    // Fill the rest
    for (int i = 0; i < N; i++) {
        if (i == i_max && same) continue;
        if (i == i_max && !same) continue;
        if (i == i_min && !same) continue;
        // T < T_max
        int tval = (T_max > 1 ? rnd.next(1, T_max - 1) : 1);
        // B > B_min
        int bval = (B_min < 5000 ? rnd.next(B_min + 1, 5000) : 5000);
        v[i] = {tval, bval};
    }

    // Output
    println(N);
    for (auto &p : v) {
        println(p.first, p.second);
    }
    return 0;
}
