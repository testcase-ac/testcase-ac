#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 10, "N");
    inf.readSpace();
    int M = inf.readInt(2, 20, "M");
    inf.readEoln();

    vector<vector<int>> a(N, vector<int>(N));
    bool hasZero = false;

    for (int i = 0; i < N; ++i) {
        a[i][0] = inf.readInt(0, 20, "cell");
        for (int j = 1; j < N; ++j) {
            inf.readSpace();
            a[i][j] = inf.readInt(0, 20, "cell");
        }
        inf.readEoln();
    }

    // Start and end cells must be normal land (1)
    ensuref(a[0][0] == 1, "Start cell (0,0) must be 1 (land), got %d", a[0][0]);
    ensuref(a[N-1][N-1] == 1, "End cell (N-1,N-1) must be 1 (land), got %d", a[N-1][N-1]);

    // Check that all >1 cells are bridges (periodic)
    // and mark presence of at least one zero (cliff).
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (a[i][j] == 0) hasZero = true;
        }
    }

    // “또한, 주어지는 지형 정보에서 오작교를 반드시 하나 이상 놓을 수 있다.”
    // => there must exist at least one zero-cell where:
    //   - it's not already a bridge (value must be 0), and
    //   - it's not at an intersection of a horizontal and vertical zero-cliff.
    // Intersection condition from statement: a zero cell where there exists
    // zero to left and right in row, and zero up and down in column.
    bool canPlaceNewBridge = false;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (a[i][j] != 0) continue; // must be a pure cliff, not existing bridge

            bool hasLeftZero = false, hasRightZero = false;
            bool hasUpZero = false, hasDownZero = false;

            // check left
            for (int y = j - 1; y >= 0; --y) {
                if (a[i][y] == 0) { hasLeftZero = true; break; }
                if (a[i][y] != 0) break;
            }
            // check right
            for (int y = j + 1; y < N; ++y) {
                if (a[i][y] == 0) { hasRightZero = true; break; }
                if (a[i][y] != 0) break;
            }
            // check up
            for (int x = i - 1; x >= 0; --x) {
                if (a[x][j] == 0) { hasUpZero = true; break; }
                if (a[x][j] != 0) break;
            }
            // check down
            for (int x = i + 1; x < N; ++x) {
                if (a[x][j] == 0) { hasDownZero = true; break; }
                if (a[x][j] != 0) break;
            }

            bool isIntersection = hasLeftZero && hasRightZero && hasUpZero && hasDownZero;
            if (!isIntersection) {
                canPlaceNewBridge = true;
                break;
            }
        }
        if (canPlaceNewBridge) break;
    }

    ensuref(hasZero, "There must be at least one cliff cell (0) to potentially place a new bridge.");
    ensuref(canPlaceNewBridge,
            "Terrain must allow placing at least one new bridge of period M on some cliff cell.");

    inf.readEof();
}
