#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

void validateHeights(const vector<int>& heights, const char* name) {
    for (int i = 0; i < static_cast<int>(heights.size()); ++i) {
        int height = heights[i];
        ensuref(1500 <= abs(height) && abs(height) <= 2500,
                "%s[%d] has invalid signed height: %d", name, i + 1, height);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<int> men = inf.readInts(n, -2500, 2500, "men");
    inf.readEoln();
    validateHeights(men, "men");

    vector<int> women = inf.readInts(n, -2500, 2500, "women");
    inf.readEoln();
    validateHeights(women, "women");

    inf.readEof();
}
