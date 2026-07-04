#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Command {
    string op;
    long long a;
    long long b;
};

long long chooseId(int dataset, int index) {
    if (rnd.next(100) < 15) {
        return rnd.next(0LL, 1000000000LL);
    }
    return dataset * 1000LL + index;
}

long long chooseSize() {
    int mode = rnd.next(100);
    if (mode < 60) return rnd.next(1LL, 8LL);
    if (mode < 90) return rnd.next(9LL, 40LL);
    return rnd.next(999999950LL, 1000000000LL);
}

long long choosePosition(const vector<long long>& interesting) {
    int mode = rnd.next(100);
    if (!interesting.empty() && mode < 55) {
        long long base = rnd.any(interesting);
        long long delta = rnd.next(-2LL, 2LL);
        return max(0LL, min(1000000000LL, base + delta));
    }
    if (mode < 85) return rnd.next(0LL, 80LL);
    return rnd.next(999999940LL, 1000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(1, 4);
    int remainingCommands = 10000;

    for (int tc = 1; tc <= datasets; ++tc) {
        int n = rnd.next(6, min(45, remainingCommands - (datasets - tc) * 6));
        remainingCommands -= n;

        println(n);

        vector<Command> commands;
        vector<long long> liveIds;
        vector<long long> usedIds;
        vector<long long> interestingPositions = {0, 1, 2, 3, 1000000000LL};
        set<long long> writtenIds;

        auto addWrite = [&]() {
            long long id;
            do {
                id = chooseId(tc, int(usedIds.size()) + 1);
            } while (writtenIds.count(id));

            long long size = chooseSize();
            commands.push_back({"W", id, size});
            writtenIds.insert(id);
            liveIds.push_back(id);
            usedIds.push_back(id);
            if (size <= 100) {
                interestingPositions.push_back(size - 1);
                interestingPositions.push_back(size);
                interestingPositions.push_back(size + 1);
            }
        };

        auto addDelete = [&]() {
            long long id;
            if (!liveIds.empty() && rnd.next(100) < 75) {
                int index = rnd.next(int(liveIds.size()));
                id = liveIds[index];
                liveIds.erase(liveIds.begin() + index);
            } else if (!usedIds.empty() && rnd.next(100) < 70) {
                id = rnd.any(usedIds);
            } else {
                id = rnd.next(0LL, 1000000000LL);
            }
            commands.push_back({"D", id, 0});
        };

        auto addRead = [&]() {
            commands.push_back({"R", choosePosition(interestingPositions), 0});
        };

        addWrite();
        addRead();
        addWrite();
        addDelete();
        addWrite();
        addRead();

        while (int(commands.size()) < n) {
            int mode = rnd.next(100);
            if (mode < 40) {
                addWrite();
            } else if (mode < 65) {
                addDelete();
            } else {
                addRead();
            }
        }

        shuffle(commands.begin() + 6, commands.end());

        for (const Command& command : commands) {
            if (command.op == "W") {
                println(command.op, command.a, command.b);
            } else {
                println(command.op, command.a);
            }
        }
    }

    println(0);
    return 0;
}
