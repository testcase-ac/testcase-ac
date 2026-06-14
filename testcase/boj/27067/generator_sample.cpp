#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> movedForward(vector<int> values, int moved, int targetPos) {
    int from = (int)(find(values.begin(), values.end(), moved) - values.begin());
    values.erase(values.begin() + from);
    values.insert(values.begin() + targetPos, moved);
    return values;
}

int chooseEarlierPosition(int from, int mode) {
    if (mode == 0) return from - 1;
    if (mode == 1) return 0;
    return rnd.next(0, from - 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 4;
    } else if (mode == 1) {
        n = rnd.next(5, 10);
    } else if (mode == 2) {
        n = rnd.next(11, 40);
    } else if (mode == 3) {
        n = rnd.next(41, 120);
    } else if (mode == 4) {
        n = rnd.next(121, 500);
    } else {
        n = rnd.next(2500, 3000);
    }

    vector<int> original(n);
    iota(original.begin(), original.end(), 1);

    int orderMode = rnd.next(0, 3);
    if (orderMode == 0) {
        shuffle(original.begin(), original.end());
    } else if (orderMode == 1) {
        reverse(original.begin(), original.end());
    } else if (orderMode == 2) {
        int rotations = rnd.next(0, n - 1);
        rotate(original.begin(), original.begin() + rotations, original.end());
    }

    vector<int> movable;
    for (int i = 1; i < n; ++i) movable.push_back(original[i]);
    shuffle(movable.begin(), movable.end());

    vector<int> moved = {movable[0], movable[1], movable[2]};
    vector<vector<int>> transformed;
    transformed.reserve(3);

    for (int i = 0; i < 3; ++i) {
        int from = (int)(find(original.begin(), original.end(), moved[i]) - original.begin());
        int moveMode = rnd.next(0, 2);
        int targetPos = chooseEarlierPosition(from, moveMode);
        transformed.push_back(movedForward(original, moved[i], targetPos));
    }

    println(n);
    println(transformed[0]);
    println(transformed[1]);
    println(transformed[2]);

    return 0;
}
