#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases (1 to 5)
    int T = rnd.next(1, 5);
    println(T);

    // Ranges for N to ensure small to medium sizes
    vector<pair<int,int>> ranges = {
        {1, 1},
        {2, 3},
        {4, 7},
        {8, 15},
        {16, 20}
    };

    for (int tc = 0; tc < T; ++tc) {
        // Pick a random range and then N within it
        auto rg = rnd.any(ranges);
        int N = rnd.next(rg.first, rg.second);
        println(N);

        // Initialize an N x N matrix with '-'
        vector<string> s(N, string(N, '-'));

        // Fill tournament results randomly
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                bool iBeatsJ = rnd.next(0, 1) == 0;
                s[i][j] = iBeatsJ ? 'W' : 'L';
                s[j][i] = iBeatsJ ? 'L' : 'W';
            }
        }

        // Output the matrix
        for (int i = 0; i < N; ++i) {
            println(s[i]);
        }
    }
    return 0;
}
