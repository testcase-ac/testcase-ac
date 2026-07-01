#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

const int MIN_COORD = -1000000;
const int MAX_COORD = 1000000;
const int MAX_H = 1000000;

struct Lizard {
    int x;
    int y;
    int h;
};

int maxSteps(int tx, int ty, int dx, int dy) {
    int result = MAX_COORD - MIN_COORD;
    if (dx > 0) result = min(result, (MAX_COORD - tx) / dx);
    if (dx < 0) result = min(result, (tx - MIN_COORD) / -dx);
    if (dy > 0) result = min(result, (MAX_COORD - ty) / dy);
    if (dy < 0) result = min(result, (ty - MIN_COORD) / -dy);
    return result;
}

pair<int, int> randomDirection() {
    while (true) {
        int dx = rnd.next(-8, 8);
        int dy = rnd.next(-8, 8);
        if (dx == 0 && dy == 0) continue;
        int g = gcd(abs(dx), abs(dy));
        dx /= g;
        dy /= g;
        return {dx, dy};
    }
}

void addOnRay(vector<Lizard>& lizards, set<pair<int, int>>& used, int tx, int ty,
              int dx, int dy, int step, int h) {
    int x = tx + dx * step;
    int y = ty + dy * step;
    if (x < MIN_COORD || x > MAX_COORD || y < MIN_COORD || y > MAX_COORD) return;
    if (!used.insert({x, y}).second) return;
    lizards.push_back({x, y, h});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int tx = rnd.next(-20, 20);
    int ty = rnd.next(-20, 20);
    if (mode == 3) {
        vector<pair<int, int>> corners = {
            {MIN_COORD, MIN_COORD},
            {MIN_COORD, MAX_COORD},
            {MAX_COORD, MIN_COORD},
            {MAX_COORD, MAX_COORD},
            {MIN_COORD, 0},
            {0, MAX_COORD},
        };
        tie(tx, ty) = rnd.any(corners);
    }

    vector<Lizard> lizards;
    set<pair<int, int>> used;
    used.insert({tx, ty});

    int targetN = rnd.next(4, 18);
    if (mode == 0) {
        auto [dx, dy] = randomDirection();
        int maxStep = maxSteps(tx, ty, dx, dy);
        if (maxStep == 0) {
            dx = -dx;
            dy = -dy;
            maxStep = maxSteps(tx, ty, dx, dy);
        }
        int count = min(targetN, maxStep);
        vector<int> steps;
        for (int step = 1; step <= maxStep; ++step) steps.push_back(step);
        shuffle(steps.begin(), steps.end());
        steps.resize(count);
        sort(steps.begin(), steps.end());
        for (int i = 0; i < count; ++i) {
            int h = (i % 3 == 0) ? rnd.next(1, 5) : rnd.next(1, 20);
            addOnRay(lizards, used, tx, ty, dx, dy, steps[i], h);
        }
    } else if (mode == 1) {
        auto [dx, dy] = randomDirection();
        for (int sign : {-1, 1}) {
            int sx = dx * sign;
            int sy = dy * sign;
            int maxStep = maxSteps(tx, ty, sx, sy);
            int count = min(rnd.next(2, 8), maxStep);
            for (int step = 1; step <= count; ++step) {
                int h = (sign < 0) ? count - step + 1 : step;
                addOnRay(lizards, used, tx, ty, sx, sy, step, h);
            }
        }
    } else {
        while ((int)lizards.size() < targetN) {
            auto [dx, dy] = randomDirection();
            int maxStep = maxSteps(tx, ty, dx, dy);
            if (maxStep == 0) continue;
            int step = rnd.next(1, min(maxStep, 30));
            int h = rnd.next(1, mode == 3 ? MAX_H : 30);
            addOnRay(lizards, used, tx, ty, dx, dy, step, h);
        }
    }

    while (lizards.empty()) {
        auto [dx, dy] = randomDirection();
        int maxStep = maxSteps(tx, ty, dx, dy);
        if (maxStep > 0) addOnRay(lizards, used, tx, ty, dx, dy, 1, rnd.next(1, 10));
    }

    shuffle(lizards.begin(), lizards.end());

    println(tx, ty);
    println((int)lizards.size());
    for (const Lizard& lizard : lizards) {
        println(lizard.x, lizard.y, lizard.h);
    }

    return 0;
}
