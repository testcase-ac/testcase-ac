#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int caseCount = rnd.next(3, 20);
    vector<int> values;

    auto addValue = [&](int value) {
        values.push_back(max(1, min(1000, value)));
    };

    if (mode == 0) {
        caseCount = rnd.next(3, 10);
        for (int i = 0; i < caseCount; ++i) addValue(rnd.next(1, 12));
    } else if (mode == 1) {
        caseCount = rnd.next(6, 18);
        int start = rnd.next(1, 80);
        int step = rnd.next(1, 17);
        for (int i = 0; i < caseCount; ++i) addValue(start + i * step);
    } else if (mode == 2) {
        caseCount = rnd.next(5, 16);
        for (int i = 0; i < caseCount; ++i) addValue(rnd.next(850, 1000));
    } else if (mode == 3) {
        caseCount = rnd.next(6, 18);
        for (int i = 0; i < caseCount; ++i) {
            int center = rnd.any(vector<int>{1, 2, 3, 4, 5, 10, 20, 50, 100, 200, 500, 1000});
            addValue(center + rnd.next(-3, 3));
        }
    } else if (mode == 4) {
        caseCount = rnd.next(8, 20);
        for (int i = 0; i < caseCount; ++i) addValue(rnd.wnext(1000, 3) + 1);
    } else {
        caseCount = rnd.next(8, 20);
        for (int i = 0; i < caseCount; ++i) addValue(rnd.wnext(1000, -3) + 1);
    }

    if (rnd.next(2)) addValue(1);
    if (rnd.next(2)) addValue(1000);
    shuffle(values.begin(), values.end());

    for (int value : values) println(value);
    return 0;
}
