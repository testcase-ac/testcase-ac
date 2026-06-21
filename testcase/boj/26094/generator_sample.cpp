#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 25);
    int targetQ = rnd.next(1, 60);

    vector<int> ids(n);
    for (int i = 0; i < n; ++i) ids[i] = i + 1;
    shuffle(ids.begin(), ids.end());

    vector<vector<int>> commands;
    int nextId = 0;
    int schedulerSize = 0;

    auto addInsert = [&]() {
        commands.push_back({0, ids[nextId++]});
        ++schedulerSize;
    };

    auto addPop = [&]() {
        commands.push_back({3});
        --schedulerSize;
    };

    while ((int)commands.size() < targetQ) {
        int remaining = targetQ - (int)commands.size();
        bool canInsert = nextId < n;
        bool canPop = schedulerSize > 0;

        if (!canPop && canInsert) {
            addInsert();
            continue;
        }
        if (!canInsert && !canPop) break;

        int mode = rnd.next(0, 99);
        if (canInsert && (mode < 42 || remaining == 1)) {
            addInsert();
        } else if (canPop && mode < 68) {
            addPop();
        } else if (remaining >= 2 && canInsert && rnd.next(0, 1) == 0) {
            int burst = rnd.next(1, min({4, n - nextId, remaining}));
            for (int i = 0; i < burst; ++i) addInsert();
        } else {
            commands.push_back({rnd.next(1, 2)});
        }
    }

    if (commands.empty()) {
        addInsert();
    }

    println(n, (int)commands.size());
    for (const vector<int>& command : commands) {
        if (command[0] == 0) {
            println(command[0], command[1]);
        } else {
            println(command[0]);
        }
    }

    return 0;
}
