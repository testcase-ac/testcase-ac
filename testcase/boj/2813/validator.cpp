#include "testlib.h"

#include <unordered_set>

using namespace std;

namespace {

void readHeights(int n, const char* name) {
    unordered_set<int> seen;
    seen.reserve(static_cast<size_t>(n) * 2);

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }

        int height = inf.readInt(1, 999999999, name);
        ensuref(seen.insert(height).second,
                "%s contains duplicate height %d at position %d", name,
                height, i + 1);
    }
    inf.readEoln();
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "n");
    inf.readEoln();

    readHeights(n, "donggyu_height");
    readHeights(n, "sanggeun_height");

    inf.readEof();
}
