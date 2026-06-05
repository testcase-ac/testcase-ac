#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

struct Triple {
    int position;
    char direction;
    int distance;
};

int nextDistinct(int current, const set<int>& used, int minStep, int maxStep) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        int distance = rnd.next(minStep, maxStep);
        int direction = rnd.next(0, 1) == 0 ? -1 : 1;
        int candidate = current + direction * distance;
        if (candidate >= -1000000 && candidate <= 1000000 && !used.count(candidate)) {
            return candidate;
        }
    }

    for (int candidate = -1000000; candidate <= 1000000; ++candidate) {
        if (candidate != current && !used.count(candidate)) {
            return candidate;
        }
    }

    return current + 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = mode == 1 ? rnd.next(8, 35) : rnd.next(1, 18);

    vector<int> path;
    set<int> used;

    int start;
    if (mode == 2) {
        start = rnd.any(vector<int>{-1000000, -999999, 999999, 1000000});
    } else {
        start = rnd.next(-30, 30);
    }
    path.push_back(start);
    used.insert(start);

    if (mode == 0) {
        int current = start;
        for (int i = 0; i < n; ++i) {
            current = nextDistinct(current, used, 1, 25);
            path.push_back(current);
            if (i + 1 < n) used.insert(current);
        }
    } else if (mode == 1) {
        int step = rnd.next(1, 9);
        int direction = rnd.next(0, 1) == 0 ? -1 : 1;
        int base = rnd.next(-100, 100);
        path[0] = base;
        used.clear();
        used.insert(base);
        for (int i = 1; i <= n; ++i) {
            int current = base + direction * step * i;
            path.push_back(current);
            if (i < n) used.insert(current);
        }
    } else if (mode == 2) {
        int current = start;
        for (int i = 0; i < n; ++i) {
            int direction = current > 0 ? -1 : 1;
            int distance = rnd.next(1, 2000000);
            int candidate = current + direction * distance;
            if (i + 1 < n) {
                for (int attempt = 0;
                     attempt < 1000 && (candidate < -1000000 || candidate > 1000000 || used.count(candidate));
                     ++attempt) {
                    distance = rnd.next(1, 2000000);
                    candidate = current + direction * distance;
                }
                if (candidate < -1000000 || candidate > 1000000 || used.count(candidate)) {
                    candidate = nextDistinct(current, used, 1, 2000000);
                }
                used.insert(candidate);
            }
            path.push_back(candidate);
            current = candidate;
        }
    } else if (mode == 3) {
        int current = rnd.next(-200, 200);
        path[0] = current;
        used.clear();
        used.insert(current);
        for (int i = 0; i < n; ++i) {
            int span = rnd.next(1, 40);
            int direction = i % 2 == 0 ? 1 : -1;
            int candidate = current + direction * span;
            if (candidate < -1000000 || candidate > 1000000 || used.count(candidate)) {
                candidate = nextDistinct(current, used, 1, 40);
            }
            path.push_back(candidate);
            current = candidate;
            if (i + 1 < n) used.insert(current);
        }
    } else {
        n = 1;
        path[0] = rnd.next(-1000000, 1000000);
        int direction = rnd.next(0, 1) == 0 ? -1 : 1;
        int distance = rnd.next(1, 2000000);
        path.push_back(path[0] + direction * distance);
    }

    vector<Triple> triples;
    for (int i = 0; i < n; ++i) {
        int delta = path[i + 1] - path[i];
        triples.push_back({path[i], delta < 0 ? 'L' : 'R', abs(delta)});
    }
    shuffle(triples.begin(), triples.end());

    println(n);
    for (const Triple& triple : triples) {
        println(triple.position, string(1, triple.direction), triple.distance);
    }
    println(path[0]);

    return 0;
}
