#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 13, "M");
    inf.readEoln();

    // Read the grid and count houses and chicken stores
    int house_cnt = 0;
    int chicken_cnt = 0;
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(N, 0, 2, "cell");
        inf.readEoln();
        for (int v : row) {
            if (v == 1) {
                house_cnt++;
            } else if (v == 2) {
                chicken_cnt++;
            }
        }
    }

    // Validate global constraints
    ensuref(house_cnt >= 1,
            "There must be at least one house, found %d", house_cnt);
    ensuref(house_cnt <= 2 * N,
            "Number of houses (%d) exceeds 2*N (%d)", house_cnt, 2 * N);
    ensuref(chicken_cnt >= M,
            "Number of chicken stores (%d) is less than M (%d)", chicken_cnt, M);
    ensuref(chicken_cnt <= 13,
            "Number of chicken stores (%d) exceeds 13", chicken_cnt);

    inf.readEof();
    return 0;
}
