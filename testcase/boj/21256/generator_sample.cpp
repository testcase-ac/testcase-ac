#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct TestCase {
    long long mx;
    long long my;
    string s;
};

string makeString(int up, int down, int left, int right) {
    string s;
    s.append(up, 'U');
    s.append(down, 'D');
    s.append(left, 'L');
    s.append(right, 'R');
    if (s.empty()) {
        s += rnd.any(string("UDLR"));
    }
    shuffle(s.begin(), s.end());
    return s;
}

TestCase randomCompactCase() {
    int len = rnd.next(1, 24);
    int up = 0, down = 0, left = 0, right = 0;
    const string dirs = "UDLR";
    for (int i = 0; i < len; ++i) {
        char c = rnd.any(dirs);
        if (c == 'U') ++up;
        if (c == 'D') ++down;
        if (c == 'L') ++left;
        if (c == 'R') ++right;
    }

    long long xReach = right - left;
    long long yReach = up - down;
    int mode = rnd.next(0, 7);
    long long mx = 0;
    long long my = 0;
    if (mode == 0) {
        mx = 0;
        my = 0;
    } else if (mode == 1) {
        mx = rnd.next(-left, right);
        my = 0;
    } else if (mode == 2) {
        mx = 0;
        my = rnd.next(-down, up);
    } else if (mode == 3) {
        mx = xReach;
        my = yReach;
    } else if (mode == 4) {
        mx = xReach + rnd.next(-2, 2);
        my = yReach + rnd.next(-2, 2);
    } else if (mode == 5) {
        mx = rnd.next(-5, 5);
        my = rnd.next(-5, 5);
    } else if (mode == 6) {
        mx = rnd.any(vector<long long>{-1000000000LL, 1000000000LL});
        my = rnd.next(-3, 3);
    } else {
        mx = rnd.next(-3, 3);
        my = rnd.any(vector<long long>{-1000000000LL, 1000000000LL});
    }

    return {mx, my, makeString(up, down, left, right)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<TestCase> cases;
    cases.push_back({0, 0, makeString(rnd.next(1, 6), 0, 0, 0)});
    cases.push_back({0, rnd.next(1, 8), makeString(rnd.next(1, 8), 0, 0, 0)});
    cases.push_back({rnd.next(1, 8), 0, makeString(0, 0, 0, rnd.next(1, 8))});
    cases.push_back({-rnd.next(1, 8), 0, makeString(0, 0, rnd.next(1, 8), 0)});
    cases.push_back({0, -rnd.next(1, 8), makeString(0, rnd.next(1, 8), 0, 0)});
    cases.push_back({rnd.next(-3, 3), rnd.next(-3, 3),
                     makeString(rnd.next(0, 5), rnd.next(0, 5),
                                rnd.next(0, 5), rnd.next(0, 5))});
    cases.push_back({1000000000LL, -1000000000LL, makeString(0, 0, 0, 1)});
    cases.push_back({-1000000000LL, 1000000000LL, makeString(0, 0, 1, 0)});

    int extra = rnd.next(6, 14);
    for (int i = 0; i < extra; ++i) {
        cases.push_back(randomCompactCase());
    }

    shuffle(cases.begin(), cases.end());
    println(static_cast<int>(cases.size()));
    for (const TestCase& tc : cases) {
        println(tc.mx, tc.my);
        println(tc.s);
    }

    return 0;
}
