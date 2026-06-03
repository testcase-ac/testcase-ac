#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        1, 2, 99, 100, 101, 170, 171, 172, 296, 297, 298,
        370, 371, 372, 596, 597, 598, 736, 737, 738,
        978, 979, 980, 1136, 1137, 1138, 1312, 1313, 1314,
        9999990, 9999999, 10000000
    };

    int T = rnd.next(12, 40);
    vector<int> values;
    values.reserve(T);

    shuffle(anchors.begin(), anchors.end());
    int anchored = min(T, rnd.next(4, 10));
    for (int i = 0; i < anchored; ++i) values.push_back(anchors[i]);

    while ((int)values.size() < T) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 0) {
            n = rnd.next(1, 150);
        } else if (mode == 1) {
            n = rnd.next(151, 1500);
        } else if (mode == 2) {
            int base = rnd.any(anchors);
            n = max(1, min(10000000, base + rnd.next(-25, 25)));
        } else if (mode == 3) {
            n = rnd.next(1501, 100000);
        } else if (mode == 4) {
            n = rnd.next(100001, 2000000);
        } else {
            n = rnd.next(2000001, 10000000);
        }
        values.push_back(n);
    }

    shuffle(values.begin(), values.end());
    println(T);
    for (int n : values) println(n);

    return 0;
}
