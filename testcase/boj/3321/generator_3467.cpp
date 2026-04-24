#include "testlib.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // small sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    vector<string> mat(N, string(M, '0'));

    // choose a generation mode for diversity
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // fully random with a random density
        double density = rnd.next(0.0, 1.0);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (rnd.next() < density)
                    mat[i][j] = '1';
    } else if (mode == 1) {
        // some columns are dense, others sparse
        vector<int> cols(M);
        iota(cols.begin(), cols.end(), 0);
        shuffle(cols.begin(), cols.end());
        int k = rnd.next(1, M);
        vector<bool> denseCol(M, false);
        for (int t = 0; t < k; t++)
            denseCol[cols[t]] = true;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                double p = denseCol[j] ? 0.8 : 0.2;
                if (rnd.next() < p)
                    mat[i][j] = '1';
            }
        }
    } else if (mode == 2) {
        // some rows full of 1s, others sparse
        vector<int> rows(N);
        iota(rows.begin(), rows.end(), 0);
        shuffle(rows.begin(), rows.end());
        int k = rnd.next(1, N);
        vector<bool> denseRow(N, false);
        for (int t = 0; t < k; t++)
            denseRow[rows[t]] = true;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (denseRow[i])
                    mat[i][j] = '1';
                else if (rnd.next() < 0.3)
                    mat[i][j] = '1';
            }
        }
    } else {
        // small random base density plus one guaranteed all-1 block
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (rnd.next() < 0.2)
                    mat[i][j] = '1';
        int h = rnd.next(1, N);
        int w = rnd.next(1, M);
        int i0 = rnd.next(0, N - h);
        int j0 = rnd.next(0, M - w);
        for (int i = i0; i < i0 + h; i++)
            for (int j = j0; j < j0 + w; j++)
                mat[i][j] = '1';
    }

    // output
    println(N, M);
    for (int i = 0; i < N; i++)
        printf("%s\n", mat[i].c_str());

    return 0;
}
