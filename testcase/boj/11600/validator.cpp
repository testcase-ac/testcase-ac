#include "testlib.h"
#include <unordered_set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and S
    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    long long S = inf.readLong(1LL, 1000000000LL, "S");
    ensuref(S % 2 == 1, "S must be odd, but S = %lld", S);
    inf.readEoln();

    // To check uniqueness of coordinates and identifiers
    unordered_set<long long> coords;
    coords.reserve(n * 2);
    unordered_set<string> ids;
    ids.reserve(n * 2);

    for (int i = 0; i < n; i++) {
        // Read x_i, y_i
        long long x = inf.readLong(0LL, S, "x_i");
        inf.readSpace();
        long long y = inf.readLong(0LL, S, "y_i");
        inf.readSpace();

        // Read identifier: 1 to 46 alphanumeric characters
        string id = inf.readToken("[A-Za-z0-9]{1,46}", "id");
        inf.readEoln();

        // Check uniqueness of coordinate
        // Encode (x,y) into one 64-bit key
        long long key = (x << 32) | y;
        ensuref(coords.find(key) == coords.end(),
                "Duplicate location at index %d: (%lld, %lld)", i, x, y);
        coords.insert(key);

        // Check uniqueness of identifier
        ensuref(ids.find(id) == ids.end(),
                "Duplicate identifier at index %d: %s", i, id.c_str());
        ids.insert(id);
    }

    inf.readEof();
    return 0;
}
