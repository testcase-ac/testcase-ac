#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr int kDimensions = 11;
    constexpr int kVertexCount = 1 << kDimensions;
    constexpr int kMinCoordinate = -1000000;
    constexpr int kMaxCoordinate = 1000000;

    array<array<int, 2>, kDimensions> endpoint{};
    int mode = rnd.next(0, 4);
    for (int j = 0; j < kDimensions; ++j) {
        int lo = 0;
        int hi = 0;

        if (mode == 0) {
            lo = -1;
            hi = 1;
        } else if (mode == 1) {
            lo = 0;
            hi = 1;
        } else if (mode == 2) {
            lo = kMinCoordinate + j;
            hi = kMaxCoordinate - j;
        } else if (mode == 3) {
            lo = rnd.next(-20, 20);
            hi = lo + rnd.next(1, 50);
        } else {
            lo = rnd.next(kMinCoordinate, kMaxCoordinate - 1);
            hi = rnd.next(lo + 1, kMaxCoordinate);
        }

        if (rnd.next(0, 1) == 1) {
            swap(lo, hi);
        }
        endpoint[j] = {lo, hi};
    }

    int missing = rnd.next(0, kVertexCount - 1);
    vector<int> vertices;
    vertices.reserve(kVertexCount - 1);
    for (int mask = 0; mask < kVertexCount; ++mask) {
        if (mask != missing) {
            vertices.push_back(mask);
        }
    }
    shuffle(vertices.begin(), vertices.end());

    for (int mask : vertices) {
        vector<int> row;
        row.reserve(kDimensions);
        for (int j = 0; j < kDimensions; ++j) {
            row.push_back(endpoint[j][(mask >> j) & 1]);
        }
        println(row);
    }

    return 0;
}
