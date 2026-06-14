#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Case {
    int b;
    int x;
    int y;
};

int boundedValue(int b, int digits) {
    long long value = 0;
    long long place = 1;
    for (int i = 0; i < digits && place <= 2000000; ++i) {
        value += 1LL * rnd.next(0, b - 1) * place;
        if (value > 2000000) value = rnd.next(0, 2000000);
        if (place > 2000000 / b) break;
        place *= b;
    }
    return int(min<long long>(value, 2000000));
}

Case makeCase(int mode) {
    if (mode == 0) {
        return {rnd.next(2, 20), 0, rnd.next(0, 200)};
    }
    if (mode == 1) {
        int b = rnd.next(2, 30);
        return {b, rnd.next(0, b - 1), rnd.next(0, b - 1)};
    }
    if (mode == 2) {
        int b = rnd.any(vector<int>{2, 3, 4, 5, 7, 10, 16});
        int digits = rnd.next(2, 10);
        return {b, boundedValue(b, digits), boundedValue(b, digits)};
    }
    if (mode == 3) {
        int b = rnd.next(1000000, 2000000);
        return {b, rnd.next(0, 2000000), rnd.next(0, 2000000)};
    }
    if (mode == 4) {
        int b = rnd.any(vector<int>{2, 10, 100, 1000, 2000000});
        int x = rnd.any(vector<int>{0, 1, b - 1, min(2000000, b), 2000000});
        int y = rnd.any(vector<int>{0, 1, b - 1, min(2000000, b), 2000000});
        return {b, x, y};
    }
    int b = rnd.next(2, 2000000);
    return {b, rnd.next(0, 2000000), rnd.next(0, 2000000)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 40);
    vector<Case> cases;
    cases.reserve(t);

    for (int mode = 0; mode < 6 && int(cases.size()) < t; ++mode) {
        cases.push_back(makeCase(mode));
    }
    while (int(cases.size()) < t) {
        cases.push_back(makeCase(rnd.next(0, 5)));
    }
    shuffle(cases.begin(), cases.end());

    println(int(cases.size()));
    for (const Case& c : cases) {
        println(c.b, c.x, c.y);
    }

    return 0;
}
