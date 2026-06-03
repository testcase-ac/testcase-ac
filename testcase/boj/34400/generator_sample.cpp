#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int tCount = rnd.next(1, 40);
    if (mode == 4) tCount = rnd.next(100, 1000);

    vector<int> values;
    values.reserve(tCount);

    while ((int)values.size() < tCount) {
        int value;

        if (mode == 0) {
            value = rnd.next(0, 1000);
        } else if (mode == 1) {
            int cycle = rnd.next(0, 40);
            int offset = rnd.any(vector<int>{0, 1, 15, 16, 17, 18, 23, 24});
            value = min(1000, cycle * 25 + offset);
        } else if (mode == 2) {
            int base = rnd.any(vector<int>{0, 16, 17, 18, 24, 25, 26, 999, 1000});
            value = max(0, min(1000, base + rnd.next(-2, 2)));
        } else if (mode == 3) {
            int cycle = rnd.next(0, 40);
            int offset = rnd.next(0, 24);
            value = min(1000, cycle * 25 + offset);
        } else {
            value = rnd.wnext(1001, rnd.next(-3, 3));
        }

        values.push_back(value);
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    for (int value : values) println(value);

    return 0;
}
