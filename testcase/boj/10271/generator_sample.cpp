#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> sortedUniqueGoals(int n, int count) {
    vector<int> goals(n);
    iota(goals.begin(), goals.end(), 1);
    shuffle(goals.begin(), goals.end());
    goals.resize(count);
    sort(goals.begin(), goals.end());
    return goals;
}

static void printList(const vector<int>& goals) {
    println(static_cast<int>(goals.size()));
    if (goals.empty()) {
        println("");
        return;
    }
    println(goals);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    vector<vector<int>> graph(n + 1);

    if (mode == 0) {
        for (int room = 1; room < n; ++room) {
            graph[room].push_back(room + 1);
        }
    } else if (mode == 1) {
        for (int room = 1; room < n; ++room) {
            if (room + 1 < n && rnd.next(0, 1)) {
                graph[room].push_back(room + 1);
            } else {
                graph[room].push_back(n);
            }
        }
        if (n == 2) {
            graph[1].clear();
        } else {
            int dead = rnd.next(2, n - 1);
            graph[dead].clear();
        }
    } else if (mode == 2) {
        if (n == 2) {
            graph[1].push_back(2);
        } else {
            graph[1] = {2, n};
            graph[2] = {1, n};
            for (int room = 3; room < n; ++room) {
                graph[room].push_back(n);
            }
        }
    } else if (mode == 3) {
        if (n == 2) {
            graph[1].push_back(1);
        } else {
            graph[1] = {2, n};
            graph[2] = {2};
            for (int room = 3; room < n; ++room) {
                graph[room].push_back(n);
            }
        }
    } else if (mode == 4) {
        double edgeProbability = rnd.next(0.15, 0.55);
        for (int room = 1; room < n; ++room) {
            for (int goal = 1; goal <= n; ++goal) {
                if (rnd.next() < edgeProbability) {
                    graph[room].push_back(goal);
                }
            }
            if (graph[room].empty() && rnd.next(0, 2) != 0) {
                graph[room].push_back(rnd.next(1, n));
            }
            sort(graph[room].begin(), graph[room].end());
        }
    } else {
        for (int room = 1; room < n; ++room) {
            int maxCount = min(n, rnd.next(0, 6));
            graph[room] = sortedUniqueGoals(n, rnd.next(0, maxCount));
        }
    }

    println(n);
    for (int room = 1; room < n; ++room) {
        printList(graph[room]);
    }

    return 0;
}
