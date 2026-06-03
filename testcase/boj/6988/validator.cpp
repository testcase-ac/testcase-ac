#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 3000, "n");
    inf.readEoln();

    vector<int> tiles = inf.readInts(n, 1, 1000000, "tile");
    inf.readEoln();

    for (int i = 1; i < n; ++i) {
        ensuref(tiles[i - 1] < tiles[i],
                "tiles must be strictly increasing: tile[%d]=%d, tile[%d]=%d",
                i,
                tiles[i - 1],
                i + 1,
                tiles[i]);
    }

    inf.readEof();
}
