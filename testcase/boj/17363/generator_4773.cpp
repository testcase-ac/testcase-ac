#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    // Initialize grid
    vector<string> grid(N, string(M, '.'));
    // Hyper-parameter: scenario for distribution
    int scenario = rnd.next(0, 2);
    vector<char> base = {'.','O','-','|','/','\\','^','<','v','>'};
    vector<int> w(10);
    if (scenario == 0) {
        // vertical-heavy
        w = {5,1,1,5,1,1,2,1,2,1};
    } else if (scenario == 1) {
        // horizontal-heavy
        w = {5,1,5,1,2,2,1,2,1,1};
    } else {
        // uniform
        for (int i = 0; i < 10; i++) w[i] = 1;
    }
    vector<char> pool;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < w[i]; j++)
            pool.push_back(base[i]);
    }
    // Fill grid randomly
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            grid[i][j] = rnd.any(pool);
        }
    }
    // Guarantee at least one horizontal segment of '-'
    int hr = rnd.next(0, N-1);
    int ha = rnd.next(0, M-1);
    int hb = rnd.next(ha, M-1);
    for (int j = ha; j <= hb; j++)
        grid[hr][j] = '-';
    // Guarantee at least one vertical segment of '|'
    int vc = rnd.next(0, M-1);
    int va = rnd.next(0, N-1);
    int vb = rnd.next(va, N-1);
    for (int i = va; i <= vb; i++)
        grid[i][vc] = '|';
    // Guarantee at least one 'O'
    int oi = rnd.next(0, N-1);
    int oj = rnd.next(0, M-1);
    grid[oi][oj] = 'O';
    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        printf("%s\n", grid[i].c_str());
    }
    return 0;
}
