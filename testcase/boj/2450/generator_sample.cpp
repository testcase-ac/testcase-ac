#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

vector<int> makeGrouped(const array<int, 3>& counts, vector<int> order) {
    vector<int> shapes;
    for (int shape : order) {
        shapes.insert(shapes.end(), counts[shape - 1], shape);
    }
    return shapes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 45);
    array<int, 3> counts = {1, 1, 1};
    for (int i = 3; i < n; ++i) {
        ++counts[rnd.next(0, 2)];
    }

    vector<int> shapes;
    if (mode == 0) {
        for (int shape = 1; shape <= 3; ++shape) {
            shapes.insert(shapes.end(), counts[shape - 1], shape);
        }
        shuffle(shapes.begin(), shapes.end());
    } else if (mode == 1) {
        vector<int> order = {1, 2, 3};
        shuffle(order.begin(), order.end());
        shapes = makeGrouped(counts, order);
    } else if (mode == 2) {
        int offset = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            shapes.push_back((i + offset) % 3 + 1);
        }
    } else if (mode == 3) {
        vector<int> order = {1, 2, 3};
        shuffle(order.begin(), order.end());
        shapes = makeGrouped(counts, order);
        reverse(shapes.begin(), shapes.end());
    } else if (mode == 4) {
        vector<int> order = {1, 2, 3};
        shuffle(order.begin(), order.end());
        shapes = makeGrouped(counts, order);
        int swaps = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < swaps; ++i) {
            swap(shapes[rnd.next(0, n - 1)], shapes[rnd.next(0, n - 1)]);
        }
    } else {
        int dominant = rnd.next(1, 3);
        shapes = {1, 2, 3};
        while ((int)shapes.size() < n) {
            if (rnd.next(0, 99) < 65) {
                shapes.push_back(dominant);
            } else {
                shapes.push_back(rnd.next(1, 3));
            }
        }
        shuffle(shapes.begin(), shapes.end());
    }

    println((int)shapes.size());
    println(shapes);
    return 0;
}
