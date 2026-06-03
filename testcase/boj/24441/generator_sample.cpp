#include "testlib.h"
#include <vector>

using namespace std;

int bounded(int x) {
    if (x < 1) return 1;
    if (x > 1000000) return 1000000;
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    int mode = rnd.next(0, 5);
    int target = rnd.next(20, 80);

    if (mode == 0) {
        int start = rnd.next(1, 40);
        for (int i = 0; i < target; ++i) values.push_back(bounded(start + i));
    } else if (mode == 1) {
        int base = rnd.next(1, 200);
        for (int i = 0; i < target; ++i) {
            int delta = rnd.next(0, 7000);
            values.push_back(bounded(base + 2 * delta));
        }
    } else if (mode == 2) {
        int base = rnd.next(1, 200);
        for (int i = 0; i < target; ++i) {
            int delta = rnd.next(0, 7000);
            values.push_back(bounded(base + 2 * delta + 1));
        }
    } else if (mode == 3) {
        vector<int> anchors = {1, 2, 3, 4, 5, 7, 9, 29, 43, 1247, 8481,
                               73731, 393939, 999999, 1000000};
        while ((int)values.size() < target) {
            int anchor = rnd.any(anchors);
            int radius = rnd.next(0, 15);
            values.push_back(bounded(anchor + rnd.next(-radius, radius)));
        }
    } else if (mode == 4) {
        while ((int)values.size() < target) {
            int span = rnd.next(0, 1000);
            values.push_back(1000000 - span);
        }
    } else {
        while ((int)values.size() < target) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) values.push_back(rnd.next(1, 100));
            if (bucket == 1) values.push_back(rnd.next(101, 10000));
            if (bucket == 2) values.push_back(rnd.next(10001, 200000));
            if (bucket == 3) values.push_back(rnd.next(200001, 1000000));
        }
    }

    if (rnd.next(0, 1)) shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int value : values) println(value);

    return 0;
}
