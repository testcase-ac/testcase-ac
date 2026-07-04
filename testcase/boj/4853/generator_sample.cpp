#include "testlib.h"
#include <vector>

using namespace std;

int randomEven(int lo, int hi) {
    int halfLo = (lo + 1) / 2;
    int halfHi = hi / 2;
    return 2 * rnd.next(halfLo, halfHi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int lineCount = rnd.next(1, 12);
    vector<int> values;

    if (mode == 0) {
        values.push_back(2);
        values.push_back(randomEven(2, 12));
    } else if (mode == 1) {
        values.push_back(randomEven(14, 50));
    } else if (mode == 2) {
        values.push_back(randomEven(52, 100));
    } else {
        values.push_back(100);
        values.push_back(randomEven(2, 100));
    }

    while ((int)values.size() < lineCount) {
        int bucket = rnd.next(0, 4);
        if (bucket == 0) {
            values.push_back(2);
        } else if (bucket == 1) {
            values.push_back(randomEven(4, 20));
        } else if (bucket == 2) {
            values.push_back(randomEven(22, 60));
        } else if (bucket == 3) {
            values.push_back(randomEven(62, 98));
        } else {
            values.push_back(100);
        }
    }

    shuffle(values.begin(), values.end());
    for (int value : values) {
        println(value);
    }

    return 0;
}
