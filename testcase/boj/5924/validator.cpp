#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Segment {
    long long x1;
    long long y1;
    long long x2;
    long long y2;
};

bool overlaps(long long a1, long long a2, long long b1, long long b2) {
    if (a1 > a2) swap(a1, a2);
    if (b1 > b2) swap(b1, b2);
    return max(a1, b1) <= min(a2, b2);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250, "N");
    inf.readEoln();

    vector<Segment> horizontal;
    vector<Segment> vertical;
    for (int i = 1; i <= n; ++i) {
        long long x1 = inf.readLong(1LL, 1000000000LL, "X1_i");
        inf.readSpace();
        long long y1 = inf.readLong(1LL, 1000000000LL, "Y1_i");
        inf.readSpace();
        long long x2 = inf.readLong(1LL, 1000000000LL, "X2_i");
        inf.readSpace();
        long long y2 = inf.readLong(1LL, 1000000000LL, "Y2_i");
        inf.readEoln();

        ensuref(x1 != x2 || y1 != y2,
                "segment %d must have distinct endpoints", i);
        ensuref(x1 == x2 || y1 == y2,
                "segment %d must be horizontal or vertical", i);

        Segment current{x1, y1, x2, y2};
        if (y1 == y2) {
            for (int j = 0; j < (int)horizontal.size(); ++j) {
                const Segment& other = horizontal[j];
                ensuref(y1 != other.y1 || !overlaps(x1, x2, other.x1, other.x2),
                        "horizontal segments %d and %d intersect",
                        j + 1, i);
            }
            horizontal.push_back(current);
        } else {
            for (int j = 0; j < (int)vertical.size(); ++j) {
                const Segment& other = vertical[j];
                ensuref(x1 != other.x1 || !overlaps(y1, y2, other.y1, other.y2),
                        "vertical segments %d and %d intersect",
                        j + 1, i);
            }
            vertical.push_back(current);
        }
    }

    inf.readEof();
}
