#include "testlib.h"

#include <array>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kDimensions = 11;
    constexpr int kTriedVertices = 2047;
    constexpr int kMinCoordinate = -1000000;
    constexpr int kMaxCoordinate = 1000000;

    set<array<int, kDimensions>> tried;
    array<set<int>, kDimensions> valuesByDimension;

    for (int i = 0; i < kTriedVertices; ++i) {
        array<int, kDimensions> vertex{};
        for (int j = 0; j < kDimensions; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            vertex[j] = inf.readInt(kMinCoordinate, kMaxCoordinate, "x_i_j");
            valuesByDimension[j].insert(vertex[j]);
        }
        inf.readEoln();

        ensuref(tried.insert(vertex).second, "duplicate vertex at line %d", i + 1);
    }

    for (int j = 0; j < kDimensions; ++j) {
        ensuref(valuesByDimension[j].size() == 2,
                "dimension %d must have exactly two endpoint values, found %d",
                j + 1,
                static_cast<int>(valuesByDimension[j].size()));
    }

    inf.readEof();
}
