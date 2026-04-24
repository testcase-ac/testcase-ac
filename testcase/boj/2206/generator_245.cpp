#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    double density = rnd.next(0.1, 0.9);
    int R = rnd.next(1, 6), C = rnd.next(1, 6);
    vector<vector<int>> grids(R, vector<int>(C));
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(i == 0 && j == 0) continue;
            if(i == R-1 && j == C-1) continue;
            if(rnd.next() < density) {
                grids[i][j] = 1;
            } else {
                grids[i][j] = 0;
            }
        }
    }
    println(R, C);
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            printf("%d", grids[i][j]);
        }
        printf("\n");
    }
}
