#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

vector<int> makeHeights(int n, int mode) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    if (mode == 0) {
        return a;
    }
    if (mode == 1) {
        reverse(a.begin(), a.end());
        return a;
    }
    if (mode == 2) {
        for (int i = 0; i + 1 < n; i += 2) {
            swap(a[i], a[i + 1]);
        }
        return a;
    }
    if (mode == 3) {
        vector<int> odds, evens;
        for (int x = 1; x <= n; ++x) {
            (x % 2 ? odds : evens).push_back(x);
        }
        a.clear();
        a.insert(a.end(), odds.begin(), odds.end());
        a.insert(a.end(), evens.begin(), evens.end());
        return a;
    }

    shuffle(a.begin(), a.end());
    return a;
}

string makeDirections(int n, int mode) {
    string d(n, 'L');

    if (mode == 0) {
        fill(d.begin() + n / 2, d.end(), 'R');
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            d[i] = (i % 2 == 0 ? 'L' : 'R');
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            d[i] = (i % 3 == 0 ? 'R' : 'L');
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            d[i] = (i % 3 == 1 ? 'L' : 'R');
        }
    } else {
        double rightProbability = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            d[i] = (rnd.next() < rightProbability ? 'R' : 'L');
        }
    }

    return d;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 9);
    int n;
    if (sizeMode < 4) {
        n = rnd.next(3, 8);
    } else if (sizeMode < 8) {
        n = rnd.next(9, 25);
    } else {
        n = rnd.next(26, 60);
    }

    int heightMode = rnd.next(0, 4);
    int directionMode = rnd.next(0, 4);

    vector<int> heights = makeHeights(n, heightMode);
    string directions = makeDirections(n, directionMode);

    if (rnd.next(0, 3) == 0) {
        int rotations = rnd.next(0, n - 1);
        rotate(heights.begin(), heights.begin() + rotations, heights.end());
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(heights[i], directions[i]);
    }

    return 0;
}
