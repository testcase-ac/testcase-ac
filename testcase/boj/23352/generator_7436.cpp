#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = rnd.next(0, 5);
    int N, M;
    vector<vector<int>> A;
    if (type == 0) {
        // fully open grid
        N = rnd.next(1, 12);
        M = rnd.next(1, 12);
        A.assign(N, vector<int>(M));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                A[i][j] = rnd.next(1, 9);
    } else if (type == 1) {
        // random blocks
        N = rnd.next(2, 12);
        M = rnd.next(2, 12);
        double p = rnd.next() * 0.7; // block probability
        A.assign(N, vector<int>(M));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (rnd.next() < p) A[i][j] = 0;
                else A[i][j] = rnd.next(1, 9);
    } else if (type == 2) {
        // single cell
        N = 1; M = 1;
        A.assign(1, vector<int>(1));
        A[0][0] = rnd.next(0, 9);
    } else if (type == 3) {
        // single row
        N = 1;
        M = rnd.next(2, 12);
        A.assign(1, vector<int>(M));
        for (int j = 0; j < M; j++)
            A[0][j] = rnd.next(0, 9);
    } else if (type == 4) {
        // single column
        N = rnd.next(2, 12);
        M = 1;
        A.assign(N, vector<int>(1));
        for (int i = 0; i < N; i++)
            A[i][0] = rnd.next(0, 9);
    } else {
        // snake path
        N = rnd.next(2, 6);
        M = rnd.next(2, 6);
        A.assign(N, vector<int>(M, 0));
        vector<pair<int,int>> path;
        int i = 0, j = 0, dir = 1;
        int total = N * M;
        for (int cnt = 0; cnt < total; cnt++) {
            path.emplace_back(i, j);
            if (dir == 1) {
                if (j + 1 < M) j++;
                else { i++; dir = -1; }
            } else {
                if (j - 1 >= 0) j--;
                else { i++; dir = 1; }
            }
        }
        int L = rnd.next(2, (int)path.size());
        for (int k = 0; k < L; k++) {
            auto [x, y] = path[k];
            A[x][y] = rnd.next(1, 9);
        }
    }
    // output
    println(N, M);
    for (int i = 0; i < N; i++)
        println(A[i]);
    return 0;
}
