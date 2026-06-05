#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int bounded(int x) {
    return max(0, min(1000000, x));
}

void addNeighborhood(set<int>& values, int center, int radius) {
    for (int d = -radius; d <= radius; ++d) {
        values.insert(bounded(center + d));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<int> values;
    values.insert(0);

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        int count = rnd.next(1, 20);
        for (int i = 0; i < count; ++i) {
            values.insert(rnd.next(0, 60));
        }
    } else if (mode == 1) {
        vector<int> anchors = {1, 2, 3, 4, 9, 10, 16, 25, 100, 1000, 10000};
        shuffle(anchors.begin(), anchors.end());
        int anchorCount = rnd.next(2, 6);
        for (int i = 0; i < anchorCount; ++i) {
            addNeighborhood(values, anchors[i], rnd.next(1, 4));
        }
    } else if (mode == 2) {
        int count = rnd.next(8, 35);
        for (int i = 0; i < count; ++i) {
            int bucket = rnd.next(0, 2);
            if (bucket == 0) {
                values.insert(rnd.wnext(1000001, -3));
            } else if (bucket == 1) {
                values.insert(rnd.next(0, 1000000));
            } else {
                values.insert(1000000 - rnd.wnext(1000001, -4));
            }
        }
    } else {
        int base = rnd.next(0, 1000000);
        int radius = rnd.next(3, 30);
        addNeighborhood(values, base, radius);
    }

    values.insert(1);
    if (rnd.next(0, 1)) {
        values.insert(999999);
        values.insert(1000000);
    }

    vector<int> queries(values.begin(), values.end());
    shuffle(queries.begin(), queries.end());

    int limit = rnd.next(1, min<int>(queries.size(), 60));
    for (int i = 0; i < limit; ++i) {
        println(queries[i]);
    }
    println(-1);

    return 0;
}
