#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 1500000000;
    vector<int> values;

    int mode = rnd.next(0, 4);
    int randomCount = rnd.next(4, 8);

    if (mode == 0) {
        values = {1, 2, 3, 4, 5, 6};
    } else if (mode == 1) {
        values = {MAX_N, MAX_N - 1, MAX_N - 2, MAX_N - 3, MAX_N - 4, MAX_N - 5};
    } else if (mode == 2) {
        int base = rnd.next(1, 250000000) * 6;
        values = {base - 5, base - 4, base - 3, base - 2, base - 1, base};
    } else {
        int base = rnd.next(1, 1000) * 6;
        values = {base + 1, base + 5, rnd.next(1, MAX_N), rnd.next(1, MAX_N)};
    }

    for (int i = 0; i < randomCount; ++i) {
        int residue = rnd.next(0, 5);
        int quotient = rnd.next(0, MAX_N / 6);
        int value = quotient * 6 + residue;
        if (value == 0) value = residue + 1;
        if (value > MAX_N) value -= 6;
        values.push_back(value);
    }

    shuffle(values.begin(), values.end());
    for (int value : values) {
        println(value);
    }
    println(0);

    return 0;
}
