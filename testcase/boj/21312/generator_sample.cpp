#include "testlib.h"
#include <vector>
using namespace std;

int pickDistinctWithParity(int parity, const vector<int>& used, bool boundaryBias) {
    vector<int> values;
    if (boundaryBias) {
        for (int x : {1, 2, 3, 4, 97, 98, 99, 100}) {
            if (x % 2 == parity) values.push_back(x);
        }
    } else {
        for (int x = (parity == 0 ? 2 : 1); x <= 100; x += 2) values.push_back(x);
    }

    shuffle(values.begin(), values.end());
    for (int x : values) {
        bool seen = false;
        for (int y : used) {
            if (x == y) seen = true;
        }
        if (!seen) return x;
    }

    for (int x = (parity == 0 ? 2 : 1); x <= 100; x += 2) {
        bool seen = false;
        for (int y : used) {
            if (x == y) seen = true;
        }
        if (!seen) return x;
    }

    quitf(_fail, "could not find a distinct value with requested parity");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    bool boundaryBias = rnd.next(0, 99) < 35;

    vector<int> parities;
    if (mode == 0) {
        parities = {1, 1, 1};
    } else if (mode == 1) {
        parities = {0, 0, 0};
    } else if (mode == 2) {
        parities = {1, 0, 0};
    } else if (mode == 3) {
        parities = {1, 1, 0};
    } else {
        parities = {rnd.next(0, 1), rnd.next(0, 1), rnd.next(0, 1)};
    }

    shuffle(parities.begin(), parities.end());

    vector<int> values;
    for (int parity : parities) {
        values.push_back(pickDistinctWithParity(parity, values, boundaryBias));
    }

    shuffle(values.begin(), values.end());
    println(values);

    return 0;
}
