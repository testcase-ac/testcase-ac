#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int LIM = 1000000000;

struct Case {
    int k;
    int n;
    int x1;
    int y1;
    int x2;
    int y2;
};

int coordAny() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return rnd.any(vector<int>{-LIM, -LIM + 1, -1, 0, 1, LIM - 1, LIM});
    if (mode == 1) return rnd.next(-1000, 1000);
    return rnd.next(-LIM, LIM);
}

pair<int, int> boundedStart(long long dx, long long dy) {
    int loX = static_cast<int>(max(-1000000000LL, -1000000000LL - dx));
    int hiX = static_cast<int>(min(1000000000LL, 1000000000LL - dx));
    int loY = static_cast<int>(max(-1000000000LL, -1000000000LL - dy));
    int hiY = static_cast<int>(min(1000000000LL, 1000000000LL - dy));
    return {rnd.next(loX, hiX), rnd.next(loY, hiY)};
}

int moveValue() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(1, 5);
    if (mode == 2) return rnd.next(6, 100);
    if (mode == 3) return rnd.any(vector<int>{999999937, 999999999, 1000000000});
    return rnd.next(1, LIM);
}

Case randomCase() {
    int k = moveValue();
    int n = moveValue();
    if (k == 0 && n == 0) {
        if (rnd.next(0, 1)) k = rnd.next(1, 10);
        else n = rnd.next(1, 10);
    }

    return {k, n, coordAny(), coordAny(), coordAny(), coordAny()};
}

Case oneMoveCase() {
    int k = moveValue();
    int n = moveValue();
    if (k == 0 && n == 0) k = rnd.next(1, 10);

    vector<pair<long long, long long>> deltas = {
        {k, n}, {k, -n}, {-k, n}, {-k, -n},
        {n, k}, {n, -k}, {-n, k}, {-n, -k},
    };
    auto [dx, dy] = rnd.any(deltas);
    auto [x1, y1] = boundedStart(dx, dy);
    return {k, n, x1, y1, static_cast<int>(x1 + dx), static_cast<int>(y1 + dy)};
}

Case zeroAxisCase() {
    int step = rnd.any(vector<int>{1, 2, 3, 5, 10, 1000000000});
    bool zeroK = rnd.next(0, 1);
    int k = zeroK ? 0 : step;
    int n = zeroK ? step : 0;
    int mx = rnd.next(-8, 8);
    int my = rnd.next(-8, 8);
    if (mx == 0 && my == 0) mx = 1;
    if (step > 1000000) {
        mx = rnd.next(-1, 1);
        my = rnd.next(-1, 1);
        if (mx == 0 && my == 0) mx = 1;
    }
    long long dx = 1LL * mx * step;
    long long dy = 1LL * my * step;
    auto [x1, y1] = boundedStart(dx, dy);
    return {k, n, x1, y1, static_cast<int>(x1 + dx), static_cast<int>(y1 + dy)};
}

Case equalStepCase() {
    int step = rnd.any(vector<int>{1, 2, 3, 7, 99991, 1000000000});
    int scaleX = rnd.next(-6, 6);
    int scaleY = rnd.next(-6, 6);
    if (step > 1000000) {
        scaleX = rnd.next(-1, 1);
        scaleY = rnd.next(-1, 1);
    }
    long long dx = 1LL * scaleX * step;
    long long dy = 1LL * scaleY * step;
    auto [sx, sy] = boundedStart(dx, dy);
    return {step, step, sx, sy, static_cast<int>(sx + dx), static_cast<int>(sy + dy)};
}

Case boundaryCase() {
    int k = rnd.any(vector<int>{1, 2, 999999937, 1000000000});
    int n = rnd.any(vector<int>{0, 1, 2, 999999999, 1000000000});
    if (k == 0 && n == 0) k = 1;
    vector<int> edge = {-LIM, -LIM + 1, -999999999, -1, 0, 1, 999999999, LIM - 1, LIM};
    return {k, n, rnd.any(edge), rnd.any(edge), rnd.any(edge), rnd.any(edge)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    vector<Case> cases;
    cases.reserve(t);

    cases.push_back({2, 1, 0, 0, 3, 3});
    cases.push_back(zeroAxisCase());
    cases.push_back(equalStepCase());
    cases.push_back(boundaryCase());

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 4);
        if (mode == 0) cases.push_back(oneMoveCase());
        else if (mode == 1) cases.push_back(zeroAxisCase());
        else if (mode == 2) cases.push_back(equalStepCase());
        else if (mode == 3) cases.push_back(boundaryCase());
        else cases.push_back(randomCase());
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const Case& c : cases) {
        println(c.k, c.n, c.x1, c.y1, c.x2, c.y2);
    }

    return 0;
}
