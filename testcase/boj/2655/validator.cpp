#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of bricks: 1 <= n <= 100
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    set<int> areas, weights;
    for (int i = 1; i <= n; i++) {
        // Each brick: base area, height, weight in [1,10000]
        int area = inf.readInt(1, 10000, "area_i");
        inf.readSpace();
        int height = inf.readInt(1, 10000, "height_i");
        inf.readSpace();
        int weight = inf.readInt(1, 10000, "weight_i");
        inf.readEoln();

        // Base areas must be unique
        ensuref(!areas.count(area),
                "Duplicate base area at brick %d: %d", i, area);
        // Weights must be unique
        ensuref(!weights.count(weight),
                "Duplicate weight at brick %d: %d", i, weight);

        areas.insert(area);
        weights.insert(weight);
    }

    inf.readEof();
    return 0;
}
