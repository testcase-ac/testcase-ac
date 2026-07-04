#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_N = 1;
const int MAX_N = 10000000;

int clampN(int n) {
    return max(MIN_N, min(MAX_N, n));
}

int nearAnchor(const vector<int>& anchors, int deltaLimit) {
    int value = rnd.any(anchors) + rnd.next(-deltaLimit, deltaLimit);
    return clampN(value);
}

int randomN() {
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        return rnd.next(1, 30);
    }
    if (mode == 1) {
        vector<int> anchors = {1, 2, 3, 4, 5, 19, 100, 1000, 45678, 45679};
        return nearAnchor(anchors, 3);
    }
    if (mode == 2) {
        vector<int> anchors = {45678, 45679, 91356, 100000, 999999, 1000000};
        return nearAnchor(anchors, 25);
    }
    if (mode == 3) {
        return rnd.next(1, 1000000);
    }
    if (mode == 4) {
        return rnd.next(9000000, MAX_N);
    }
    return nearAnchor(vector<int>{MAX_N - 100, MAX_N - 1, MAX_N}, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    println(randomN());

    return 0;
}
