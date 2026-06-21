#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int count = rnd.next(1, 20);
    vector<int> values;

    vector<int> anchors = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        31, 32, 33, 99, 100, 101,
        999999937, 999999999, 1000000000
    };
    shuffle(anchors.begin(), anchors.end());

    int anchorCount = rnd.next(0, min(count, 5));
    for (int i = 0; i < anchorCount; ++i) {
        values.push_back(anchors[i]);
    }

    while ((int)values.size() < count) {
        int mode = rnd.next(0, 4);
        int m;
        if (mode == 0) {
            m = rnd.next(1, 30);
        } else if (mode == 1) {
            int base = rnd.next(1, 1000);
            m = base * base;
        } else if (mode == 2) {
            m = 1000000000 - rnd.next(0, 1000);
        } else if (mode == 3) {
            m = rnd.next(1, 1000000);
        } else {
            m = rnd.next(1, 1000000000);
        }
        values.push_back(m);
    }

    shuffle(values.begin(), values.end());
    for (int m : values) {
        println(m);
    }
    println(0);

    return 0;
}
