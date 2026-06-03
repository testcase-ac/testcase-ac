#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Circle {
    int x;
    int r;
};

static void shuffleAndPrint(vector<Circle> circles) {
    shuffle(circles.begin(), circles.end());
    println((int)circles.size());
    for (const Circle& c : circles) {
        println(c.x, c.r);
    }
}

static vector<Circle> separatedCircles(int n) {
    vector<Circle> circles;
    int x = rnd.next(-1000, 1000);
    for (int i = 0; i < n; ++i) {
        int r = rnd.next(1, 20);
        x += r + rnd.next(1, 15);
        circles.push_back({x, r});
        x += r + rnd.next(1, 15);
    }
    return circles;
}

static vector<Circle> nestedChain(int n) {
    vector<Circle> circles;
    int center = rnd.next(-100, 100);
    int r = n * 12 + rnd.next(20, 40);
    for (int i = 0; i < n; ++i) {
        circles.push_back({center, r});
        r -= rnd.next(3, 8);
        if (r < 1) r = 1;
    }
    return circles;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 20);
    vector<Circle> circles;

    if (mode == 0) {
        circles = separatedCircles(n);
    } else if (mode == 1) {
        circles = nestedChain(n);
    } else if (mode == 2) {
        int leftCount = rnd.next(1, n - 1);
        circles = separatedCircles(leftCount);
        vector<Circle> nested = nestedChain(n - leftCount);
        int offset = rnd.next(200, 500);
        for (Circle c : nested) {
            circles.push_back({c.x + offset, c.r});
        }
    } else if (mode == 3) {
        circles = separatedCircles(n);
        circles[0] = {0, rnd.next(3, 30)};
        circles[1] = {rnd.next(1, circles[0].r - 1), rnd.next(3, 30)};
    } else if (mode == 4) {
        circles = separatedCircles(n);
        int r1 = rnd.next(1, 30);
        int r2 = rnd.next(1, 30);
        circles[0] = {0, r1};
        circles[1] = {r1 + r2, r2};
    } else {
        for (int i = 0; i < n; ++i) {
            circles.push_back({rnd.next(-120, 120), rnd.next(1, 40)});
        }
    }

    shuffleAndPrint(circles);
    return 0;
}
