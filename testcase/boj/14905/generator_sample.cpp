#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int lineCount = rnd.next(1, 25);
    vector<int> values;
    values.reserve(lineCount);

    while ((int)values.size() < lineCount) {
        int mode = rnd.next(0, 5);
        int n;

        if (mode == 0) {
            n = rnd.next(1, 7);
        } else if (mode == 1) {
            n = rnd.next(8, 20);
        } else if (mode == 2) {
            n = rnd.next(21, 200);
        } else if (mode == 3) {
            n = rnd.next(201, 10000);
        } else if (mode == 4) {
            n = 100000000 - rnd.next(0, 200);
        } else {
            n = rnd.next(1, 100000000);
        }

        values.push_back(n);
    }

    if (lineCount >= 3) {
        values[0] = rnd.next(1, 7);
        values[1] = rnd.next(8, 11);
        values[2] = 100000000 - rnd.next(0, 3);
    }

    shuffle(values.begin(), values.end());
    for (int n : values) {
        println(n);
    }

    return 0;
}
