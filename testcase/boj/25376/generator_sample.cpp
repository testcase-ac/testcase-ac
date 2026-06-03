#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> shuffledOthers(int n, int self) {
    vector<int> nodes;
    for (int x = 1; x <= n; ++x) {
        if (x != self) {
            nodes.push_back(x);
        }
    }
    shuffle(nodes.begin(), nodes.end());
    return nodes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 5) {
        n = rnd.next(15, 20);
    } else if (mode == 6) {
        n = rnd.next(3, 20);
    } else {
        n = rnd.next(3, 12);
    }

    vector<int> state(n + 1);
    int stateMode = rnd.next(0, 4);
    for (int i = 1; i <= n; ++i) {
        if (stateMode == 0) {
            state[i] = 0;
        } else if (stateMode == 1) {
            state[i] = 1;
        } else if (stateMode == 2) {
            state[i] = i % 2;
        } else if (stateMode == 3) {
            state[i] = (i == 1 || i == n);
        } else {
            state[i] = rnd.next(0, 1);
        }
    }

    vector<vector<int>> affects(n + 1);
    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 3) == 0) {
                affects[i].push_back(rnd.any(shuffledOthers(n, i)));
            }
        }
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            affects[i].push_back(i + 1);
            if (i + 2 <= n && rnd.next(0, 2) == 0) {
                affects[i].push_back(i + 2);
            }
        }
        if (rnd.next(0, 1)) {
            affects[n].push_back(1);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            affects[i].push_back(i == n ? 1 : i + 1);
            if (rnd.next(0, 1)) {
                affects[i].push_back(i == 1 ? n : i - 1);
            }
        }
    } else if (mode == 3) {
        int hub = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i == hub) {
                affects[i] = shuffledOthers(n, i);
                affects[i].resize(rnd.next(max(1, n / 2), n - 1));
            } else if (rnd.next(0, 1)) {
                affects[i].push_back(hub);
            }
        }
    } else if (mode == 4) {
        int left = rnd.next(1, n - 1);
        for (int i = 1; i <= n; ++i) {
            vector<int> candidates;
            for (int j = 1; j <= n; ++j) {
                if (i != j && ((i <= left) != (j <= left))) {
                    candidates.push_back(j);
                }
            }
            shuffle(candidates.begin(), candidates.end());
            int take = candidates.empty() ? 0 : rnd.next(0, (int)candidates.size());
            affects[i].assign(candidates.begin(), candidates.begin() + take);
        }
    } else if (mode == 5) {
        for (int i = 1; i <= n; ++i) {
            affects[i] = shuffledOthers(n, i);
            affects[i].resize(rnd.next(max(0, n - 4), n - 1));
        }
    } else {
        int density = rnd.next(0, 100);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i != j && rnd.next(0, 99) < density) {
                    affects[i].push_back(j);
                }
            }
            shuffle(affects[i].begin(), affects[i].end());
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << state[i];
    }
    cout << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << affects[i].size();
        for (int x : affects[i]) {
            cout << ' ' << x;
        }
        cout << '\n';
    }

    return 0;
}
