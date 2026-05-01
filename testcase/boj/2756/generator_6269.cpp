#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Precompute diagonal boundary distances
    double d9  = 9.0 / sqrt(2.0);
    double d15 = 15.0 / sqrt(2.0);
    // List of points exactly on ring boundaries
    vector<pair<double,double>> bnd = {
        {3,0}, {0,3}, {-3,0}, {0,-3},
        {6,0}, {0,6}, {-6,0}, {0,-6},
        {d9, d9}, {-d9, d9}, {d9, -d9}, {-d9, -d9},
        {12,0}, {0,12}, {-12,0}, {0,-12},
        {d15, d15}, {-d15, d15}, {d15, -d15}, {-d15, -d15}
    };
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        // Number of darts landing exactly on boundaries
        int k = rnd.next(0, 6);
        shuffle(bnd.begin(), bnd.end());
        vector<pair<double,double>> darts;
        // Add k boundary darts
        for (int i = 0; i < k; i++) {
            darts.push_back(bnd[i]);
        }
        // Add remaining random darts
        for (int i = k; i < 6; i++) {
            double x = rnd.next(-2000, 2000) / 100.0;
            double y = rnd.next(-2000, 2000) / 100.0;
            darts.emplace_back(x, y);
        }
        // Shuffle the order of 6 darts
        shuffle(darts.begin(), darts.end());
        // Print 6 darts (12 numbers) with two decimal places
        for (auto &p : darts) {
            printf("%.2f %.2f ", p.first, p.second);
        }
        printf("\n");
    }
    return 0;
}
