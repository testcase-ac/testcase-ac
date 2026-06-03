#include "testlib.h"
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);
    int w = rnd.next(1, 20);
    int h = rnd.next(1, 20);

    if (mode == 1) {
        w = rnd.next(1, 5);
        h = rnd.next(1, 5);
        n = rnd.next(8, 20);
    } else if (mode == 2) {
        w = rnd.next(80, 100);
        h = rnd.next(80, 100);
        n = rnd.next(6, 15);
    } else if (mode == 3) {
        w = rnd.next(1, 100);
        h = rnd.next(1, 100);
        n = rnd.next(1, 50);
    } else if (mode == 4) {
        if (rnd.next(0, 1) == 0) {
            w = rnd.next(1, 8);
            h = rnd.next(70, 100);
        } else {
            w = rnd.next(70, 100);
            h = rnd.next(1, 8);
        }
        n = rnd.next(5, 18);
    }

    int diagonalFloor = static_cast<int>(sqrt(w * w + h * h));
    while ((diagonalFloor + 1) * (diagonalFloor + 1) <= w * w + h * h) {
        ++diagonalFloor;
    }
    while (diagonalFloor * diagonalFloor > w * w + h * h) {
        --diagonalFloor;
    }

    vector<int> candidates;
    candidates.push_back(1);
    candidates.push_back(w);
    candidates.push_back(h);
    candidates.push_back(diagonalFloor);
    candidates.push_back(diagonalFloor + 1);
    candidates.push_back(max(1, diagonalFloor - 1));
    candidates.push_back(rnd.next(1, min(1000, max(1, diagonalFloor))));
    candidates.push_back(rnd.next(min(1000, diagonalFloor + 1), 1000));

    vector<int> lengths;
    for (int i = 0; i < n; ++i) {
        int length;
        if (rnd.next(0, 99) < 70) {
            length = rnd.any(candidates);
        } else if (rnd.next(0, 1) == 0) {
            length = rnd.next(1, min(1000, max(1, diagonalFloor + 3)));
        } else {
            length = rnd.next(max(1, diagonalFloor - 3), 1000);
        }
        lengths.push_back(min(1000, max(1, length)));
    }
    shuffle(lengths.begin(), lengths.end());

    println(n, w, h);
    for (int length : lengths) {
        println(length);
    }

    return 0;
}
