#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size
    int N = rnd.next(2, 11);
    // Initialize grid with placeholders
    vector<string> grid(N, string(N, '?'));

    // Hyper-parameter: add some 2x2 F clusters
    int max_c = min(3, (N - 1) * (N - 1));
    int cluster_count = rnd.next(0, max_c);
    for (int t = 0; t < cluster_count; t++) {
        int i = rnd.next(0, N - 2);
        int j = rnd.next(0, N - 2);
        for (int di = 0; di < 2; di++)
            for (int dj = 0; dj < 2; dj++)
                grid[i + di][j + dj] = 'F';
    }

    // Hyper-parameter: random distribution thresholds for A, B, C, F
    vector<double> cuts(3);
    for (int i = 0; i < 3; i++) cuts[i] = rnd.next();
    sort(cuts.begin(), cuts.end());

    // Fill remaining cells according to the random distribution
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == '?') {
                double x = rnd.next();
                char c;
                if (x < cuts[0]) c = 'A';
                else if (x < cuts[1]) c = 'B';
                else if (x < cuts[2]) c = 'C';
                else c = 'F';
                grid[i][j] = c;
            }
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i].c_str());
    }

    return 0;
}
