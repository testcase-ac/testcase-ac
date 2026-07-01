#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

bool isAncestor(int ancestor, int vertex) {
    if (ancestor == 0) {
        return true;
    }

    int width = 0;
    int x = ancestor;
    while (x > 0) {
        ++width;
        x >>= 1;
    }

    int mask = (1 << width) - 1;
    return (vertex & mask) == ancestor;
}

bool canRemove(const vector<int>& removed, int vertex) {
    for (int ancestor : removed) {
        if (isAncestor(ancestor, vertex)) {
            return false;
        }
    }
    return true;
}

int randomVertex(int a, int mode) {
    if (a == 0) {
        return 0;
    }

    if (a < 30) {
        int limit = 1 << a;
        if (mode == 1) {
            return rnd.next(max(0, limit - 12), limit - 1);
        }
        return rnd.next(0, limit - 1);
    }

    if (mode == 2) {
        return rnd.next(900000000, 1000000000);
    }
    return rnd.next(0, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a;
    if (mode == 0) {
        a = rnd.next(0, 6);
    } else if (mode == 1) {
        a = rnd.next(7, 15);
    } else if (mode == 2) {
        a = rnd.next(26, 29);
    } else if (mode == 3) {
        a = rnd.next(30, 60);
    } else {
        a = rnd.next(61, 1000000);
    }

    int targetM = (a == 0 ? 1 : rnd.next(1, 25));
    if (a > 0 && rnd.next(0, 4) == 0) {
        ++targetM;
    }

    vector<int> removed;
    removed.reserve(targetM);

    if (a >= 2 && rnd.next(0, 3) == 0) {
        int depth = min(a, rnd.next(2, min(a, 20)));
        int suffix = rnd.next(1, (1 << depth) - 1);
        for (int width = depth; width >= 1 && (int)removed.size() < targetM; --width) {
            int vertex = suffix & ((1 << width) - 1);
            if (canRemove(removed, vertex)) {
                removed.push_back(vertex);
            }
        }
    }

    int attempts = 0;
    while ((int)removed.size() < targetM && attempts < 5000) {
        ++attempts;
        int vertex = randomVertex(a, mode);
        if (canRemove(removed, vertex)) {
            removed.push_back(vertex);
        }
    }

    if (removed.empty()) {
        removed.push_back(0);
    }

    if (a > 0 && (int)removed.size() < targetM && canRemove(removed, 0)) {
        removed.push_back(0);
    }

    println(a, (int)removed.size());
    for (int vertex : removed) {
        println(vertex);
    }

    return 0;
}
