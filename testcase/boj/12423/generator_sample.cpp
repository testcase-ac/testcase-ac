#include "testlib.h"

#include <vector>
using namespace std;

vector<int> splitInto3(int total) {
    int first = rnd.next(0, total);
    int second = rnd.next(0, total - first);
    vector<int> parts = {first, second, total - first - second};
    shuffle(parts.begin(), parts.end());
    return parts;
}

int payoffValue(int mode, int row, int col) {
    if (mode == 0) return rnd.next(-5, 5);
    if (mode == 1) return rnd.any(vector<int>{-100000, -1, 0, 1, 100000});
    if (mode == 2) return row == col ? rnd.next(20, 100) : rnd.next(-100, 10);
    if (mode == 3) return row + col == 2 ? rnd.next(20, 100) : rnd.next(-100, 10);
    if (mode == 4) return rnd.next(-100000, 100000);
    return rnd.next(-20, 20);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int sizeMode = rnd.next(0, 4);
        int n;
        if (sizeMode == 0) {
            n = 1;
        } else if (sizeMode == 1) {
            n = rnd.next(2, 6);
        } else if (sizeMode == 2) {
            n = rnd.next(7, 20);
        } else {
            n = rnd.any(vector<int>{50, 75, 100});
        }

        vector<int> left = splitInto3(n);
        vector<int> right = splitInto3(n);

        println(n, left[0], left[1], left[2], right[0], right[1], right[2]);

        int matrixMode = rnd.next(0, 5);
        for (int row = 0; row < 3; ++row) {
            vector<int> values;
            for (int col = 0; col < 3; ++col) {
                values.push_back(payoffValue(matrixMode, row, col));
            }
            println(values);
        }
    }

    return 0;
}
