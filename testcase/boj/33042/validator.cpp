#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    set<string> tiles;
    for (char suit : {'m', 'p', 's'}) {
        for (char rank = '1'; rank <= '9'; ++rank) {
            tiles.insert(string() + rank + suit);
        }
    }
    for (char rank = '1'; rank <= '7'; ++rank) {
        tiles.insert(string() + rank + 'z');
    }

    int n = inf.readInt(1, 136, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string tile = inf.readToken("[1-9][mps]|[1-7]z", "tile");
        ensuref(tiles.count(tile) == 1, "invalid tile at position %d: %s", i + 1, tile.c_str());
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
