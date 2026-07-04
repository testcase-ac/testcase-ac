#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct Monster {
    bool present;
    string required;
    string learned;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> names = {
        "bfs", "dfs", "dp", "sort", "greedy",
        "graph", "dijkstra", "math", "tree", "flow"
    };

    int n = rnd.next(1, 4);
    int mode = rnd.next(0, 4);

    vector<string> pieces(n, string(n, 'A'));
    const string tileKinds = "ABCD";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mode == 0) {
                pieces[i][j] = tileKinds[(i + j) % 4];
            } else if (mode == 1) {
                pieces[i][j] = tileKinds[(i * 2 + j) % 4];
            } else {
                pieces[i][j] = tileKinds[rnd.next(0, 3)];
            }
        }
    }

    vector<vector<int>> level(n, vector<int>(n));
    int base = rnd.next(1, 4);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mode == 2) {
                level[i][j] = rnd.next(1, 16);
            } else if (mode == 3) {
                level[i][j] = min(16, base + i + j + rnd.next(0, 2));
            } else {
                level[i][j] = rnd.next(1, 6);
            }
        }
    }

    vector<vector<Monster>> monsters(n, vector<Monster>(n, {false, "0", "0"}));
    int algorithmLimit = rnd.next(1, 10);
    int monsterPercent = rnd.next(25, 80);
    int highestUsed = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (rnd.next(1, 100) > monsterPercent) {
                continue;
            }

            Monster m;
            m.present = true;
            if (highestUsed >= 0 && rnd.next(0, 99) < 70) {
                m.required = names[rnd.next(0, highestUsed)];
            } else {
                m.required = "0";
            }

            if (highestUsed + 1 < algorithmLimit && rnd.next(0, 99) < 65) {
                ++highestUsed;
                m.learned = names[highestUsed];
            } else if (highestUsed >= 0 && rnd.next(0, 99) < 30) {
                m.learned = names[rnd.next(0, highestUsed)];
            } else {
                m.learned = "0";
            }

            monsters[i][j] = m;
        }
    }

    int knownUpper = min(4, max(0, highestUsed + 1));
    int a = rnd.next(0, knownUpper);
    vector<string> initial;
    vector<int> order;
    for (int i = 0; i <= highestUsed; ++i) {
        order.push_back(i);
    }
    shuffle(order.begin(), order.end());
    for (int i = 0; i < a; ++i) {
        initial.push_back(names[order[i]]);
    }
    sort(initial.begin(), initial.end());

    println(n);
    for (const string& row : pieces) {
        println(row);
    }
    for (int i = 0; i < n; ++i) {
        println(level[i]);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                cout << ' ';
            }
            const Monster& m = monsters[i][j];
            cout << (m.present ? 1 : 0) << ' ' << m.required << ' ' << m.learned;
        }
        cout << '\n';
    }
    println(a);
    if (initial.empty()) {
        println("");
    } else {
        println(initial);
    }

    return 0;
}
