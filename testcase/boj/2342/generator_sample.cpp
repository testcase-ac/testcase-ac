#include "testlib.h"
#include <vector>
using namespace std;

int opposite(int x) {
    return x == 1 ? 3 : x == 3 ? 1 : x == 2 ? 4 : 2;
}

int adjacent(int x) {
    vector<int> candidates;
    for (int y = 1; y <= 4; ++y) {
        if (y != x && y != opposite(x)) {
            candidates.push_back(y);
        }
    }
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> steps;
    int mode = rnd.next(0, 5);
    int n = rnd.next(0, 80);

    if (mode == 0) {
        n = rnd.next(0, 8);
        int x = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            steps.push_back(x);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 60);
        int a = rnd.next(1, 4);
        int b = rnd.next(0, 1) ? opposite(a) : adjacent(a);
        for (int i = 0; i < n; ++i) {
            steps.push_back(i % 2 == 0 ? a : b);
        }
    } else if (mode == 2) {
        n = rnd.next(6, 80);
        while ((int)steps.size() < n) {
            int value = rnd.next(1, 4);
            int len = rnd.next(1, 8);
            while (len-- > 0 && (int)steps.size() < n) {
                steps.push_back(value);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(8, 80);
        int cur = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            steps.push_back(cur);
            int choice = rnd.next(0, 2);
            if (choice == 0) {
                cur = adjacent(cur);
            } else if (choice == 1) {
                cur = opposite(cur);
            }
        }
    } else if (mode == 4) {
        vector<int> cycle = {1, 2, 3, 4};
        if (rnd.next(0, 1)) {
            cycle = {1, 4, 3, 2};
        }
        n = rnd.next(4, 80);
        int offset = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            steps.push_back(cycle[(i + offset) % 4]);
        }
    } else {
        n = rnd.next(1, 80);
        for (int i = 0; i < n; ++i) {
            steps.push_back(rnd.next(1, 4));
        }
    }

    steps.push_back(0);
    println(steps);
    return 0;
}
