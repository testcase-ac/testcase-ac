#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxCube = 30000;
    int mode = rnd.next(0, 4);
    int cubeCount = rnd.next(5, 18);
    int targetOps = rnd.next(12, 45);

    vector<int> cubes;
    if (mode == 4) {
        cubes = {1, 2, 3, 4, 5, maxCube - 2, maxCube - 1, maxCube};
        cubeCount = (int)cubes.size();
    } else {
        vector<int> pool;
        for (int i = 1; i <= maxCube; ++i) {
            pool.push_back(i);
        }
        shuffle(pool.begin(), pool.end());
        cubes.assign(pool.begin(), pool.begin() + cubeCount);
        if (rnd.next(0, 2) == 0) {
            cubes[rnd.next(0, cubeCount - 1)] = maxCube;
        }
        sort(cubes.begin(), cubes.end());
        cubes.erase(unique(cubes.begin(), cubes.end()), cubes.end());
        cubeCount = (int)cubes.size();
    }

    vector<int> parent(maxCube + 1), stackSize(maxCube + 1, 1);
    iota(parent.begin(), parent.end(), 0);

    auto findRoot = [&](int x) {
        while (parent[x] != x) {
            x = parent[x];
        }
        return x;
    };

    vector<string> ops;
    auto addCount = [&](int x) {
        ops.push_back("C " + to_string(x));
    };
    auto addMove = [&](int x, int y) {
        int rootX = findRoot(x);
        int rootY = findRoot(y);
        if (rootX == rootY) {
            return false;
        }
        parent[rootX] = rootY;
        stackSize[rootY] += stackSize[rootX];
        ops.push_back("M " + to_string(x) + " " + to_string(y));
        return true;
    };

    vector<int> order = cubes;
    shuffle(order.begin(), order.end());

    if (mode == 0) {
        for (int i = 1; i < cubeCount && (int)ops.size() < targetOps; ++i) {
            addMove(order[i - 1], order[i]);
            addCount(order[rnd.next(0, i)]);
        }
    } else if (mode == 1) {
        int hub = order[0];
        for (int i = 1; i < cubeCount && (int)ops.size() < targetOps; ++i) {
            addCount(order[i]);
            addMove(order[i], hub);
            addCount(hub);
        }
    } else if (mode == 2) {
        for (int step = 1; step < cubeCount && (int)ops.size() < targetOps; ++step) {
            int x = order[step];
            int y = order[rnd.next(0, step - 1)];
            addMove(x, y);
            if (rnd.next(0, 1) == 0) {
                addCount(x);
            } else {
                addCount(y);
            }
        }
    } else {
        for (int i = 0; i + 1 < cubeCount && (int)ops.size() < targetOps; i += 2) {
            addMove(order[i], order[i + 1]);
            addCount(order[i]);
        }
        for (int i = 2; i < cubeCount && (int)ops.size() < targetOps; i += 2) {
            addMove(order[i - 1], order[i]);
            addCount(order[rnd.next(0, i)]);
        }
    }

    while ((int)ops.size() < targetOps) {
        if (rnd.next(0, 99) < 65) {
            addCount(rnd.any(cubes));
            continue;
        }

        vector<pair<int, int>> candidates;
        for (int x : cubes) {
            for (int y : cubes) {
                if (findRoot(x) != findRoot(y)) {
                    candidates.push_back({x, y});
                }
            }
        }
        if (candidates.empty()) {
            addCount(rnd.any(cubes));
        } else {
            auto move = rnd.any(candidates);
            addMove(move.first, move.second);
        }
    }

    println((int)ops.size());
    for (const string& op : ops) {
        println(op);
    }

    return 0;
}
