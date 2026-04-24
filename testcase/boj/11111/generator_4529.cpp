#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    // Prepare letter set
    vector<char> all = {'A','B','C','D','F'};
    shuffle(all.begin(), all.end());
    int k = rnd.next(2, 5);
    vector<char> letters(all.begin(), all.begin() + k);
    // Choose distribution type
    int distType = rnd.next(0, 3);
    // Initialize grid
    vector<string> grid(N, string(M, 'A'));
    if (distType == 0) {
        // Uniform random fill
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = rnd.any(letters);
    } else if (distType == 1) {
        // Horizontal stripes
        int stripes = rnd.next(1, N);
        vector<int> b;
        b.push_back(0);
        for (int i = 0; i < stripes - 1; i++)
            b.push_back(rnd.next(1, N - 1));
        b.push_back(N);
        sort(b.begin(), b.end());
        for (int s = 0; s < stripes; s++) {
            char c = letters[s % k];
            for (int i = b[s]; i < b[s + 1]; i++)
                for (int j = 0; j < M; j++)
                    grid[i][j] = c;
        }
    } else if (distType == 2) {
        // Vertical stripes
        int stripes = rnd.next(1, M);
        vector<int> b;
        b.push_back(0);
        for (int i = 0; i < stripes - 1; i++)
            b.push_back(rnd.next(1, M - 1));
        b.push_back(M);
        sort(b.begin(), b.end());
        for (int s = 0; s < stripes; s++) {
            char c = letters[s % k];
            for (int j = b[s]; j < b[s + 1]; j++)
                for (int i = 0; i < N; i++)
                    grid[i][j] = c;
        }
    } else {
        // Checkerboard
        char c1 = rnd.any(letters), c2;
        do { c2 = rnd.any(letters); } while (c2 == c1);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                grid[i][j] = ((i + j) % 2 == 0 ? c1 : c2);
    }
    // Output
    println(N, M);
    for (int i = 0; i < N; i++)
        printf("%s\n", grid[i].c_str());
    return 0;
}
