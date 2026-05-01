#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Image size
    int R = rnd.next(3, 10);
    int C = rnd.next(3, 10);
    vector<vector<int>> mat(R, vector<int>(C));

    // Pattern hyper-parameter: 0=uniform noise, 1=horizontal gradient, 2=vertical gradient
    int pattern = rnd.next(0, 2);
    if (pattern == 0) {
        // Uniform noise
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                mat[i][j] = rnd.next(0, 255);
    } else if (pattern == 1) {
        // Horizontal gradient: constant per column
        vector<int> col(C);
        for (int j = 0; j < C; j++)
            col[j] = rnd.next(0, 255);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                mat[i][j] = col[j];
    } else {
        // Vertical gradient: constant per row
        vector<int> row(R);
        for (int i = 0; i < R; i++)
            row[i] = rnd.next(0, 255);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                mat[i][j] = row[i];
    }

    // Threshold hyper-parameter: clustered ranges
    int T;
    int tmode = rnd.next(0, 2);
    if (tmode == 0) {
        T = rnd.next(0, 50);
    } else if (tmode == 1) {
        T = rnd.next(51, 200);
    } else {
        T = rnd.next(201, 255);
    }

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        println(mat[i]);
    }
    println(T);
    return 0;
}
