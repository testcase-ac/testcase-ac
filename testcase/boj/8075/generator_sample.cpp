#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {

string randomSide(int k, int minLen, int maxLen, int digitWeight) {
    int len = rnd.next(minLen, maxLen);
    string side;
    side.reserve(len);

    for (int i = 0; i < len; ++i) {
        bool useDigit = k == 0 || rnd.next(1, 100) <= digitWeight;
        if (useDigit) {
            side.push_back(rnd.next(0, 1) == 0 ? '0' : '1');
        } else {
            side.push_back(static_cast<char>('a' + rnd.next(0, k - 1)));
        }
    }

    return side;
}

string repeatedSide(int k, int blocks) {
    string side;
    for (int i = 0; i < blocks; ++i) {
        int mode = rnd.next(0, 2);
        if (mode == 0 || k == 0) {
            side.push_back(rnd.next(0, 1) == 0 ? '0' : '1');
        } else if (mode == 1) {
            side.push_back(static_cast<char>('a' + rnd.next(0, k - 1)));
        } else {
            char ch = static_cast<char>('a' + rnd.next(0, k - 1));
            side.push_back(ch);
            side.push_back(ch);
        }
    }
    return side;
}

void printEquation() {
    int mode = rnd.next(0, 4);
    int k = 0;
    if (mode == 0) {
        k = 0;
    } else if (mode == 1) {
        k = 1;
    } else if (mode == 2) {
        k = rnd.next(2, 4);
    } else if (mode == 3) {
        k = rnd.next(4, 8);
    } else {
        k = rnd.next(1, 6);
    }

    println(k);

    vector<int> lengths(k);
    for (int i = 0; i < k; ++i) {
        int upper = mode == 3 ? 12 : 7;
        lengths[i] = rnd.next(1, upper);
    }
    println(lengths);

    string left;
    string right;
    if (mode == 0) {
        left = randomSide(0, 1, 18, 100);
        right = randomSide(0, 1, 18, 100);
    } else if (mode == 1) {
        left = repeatedSide(k, rnd.next(2, 8));
        right = repeatedSide(k, rnd.next(2, 8));
    } else if (mode == 2) {
        left = randomSide(k, 3, 14, rnd.next(20, 60));
        right = randomSide(k, 3, 14, rnd.next(20, 60));
    } else if (mode == 3) {
        left = randomSide(k, 8, 24, rnd.next(5, 35));
        right = randomSide(k, 8, 24, rnd.next(5, 35));
    } else {
        string shared = randomSide(k, 1, 6, rnd.next(15, 70));
        left = shared + randomSide(k, 1, 8, rnd.next(20, 80));
        right = randomSide(k, 1, 8, rnd.next(20, 80)) + shared;
    }

    println(static_cast<int>(left.size()));
    println(left);
    println(static_cast<int>(right.size()));
    println(right);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int equations = rnd.next(1, 5);
    println(equations);
    for (int i = 0; i < equations; ++i) {
        printEquation();
    }

    return 0;
}
