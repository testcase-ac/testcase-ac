#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

struct Mushroom {
    int pos;
    int dir;
    int id;
};

int n, fieldLength;
vector<Mushroom> initialMushrooms;

int simulate(const set<int>& commands) {
    vector<Mushroom> active = initialMushrooms;
    if (commands.count(0)) {
        for (auto& mushroom : active) {
            mushroom.dir = -mushroom.dir;
        }
    }

    int leftExits = 0;
    while (!active.empty()) {
        vector<vector<int>> byPosition(fieldLength + 1);
        for (int i = 0; i < (int)active.size(); ++i) {
            active[i].pos += active[i].dir;
            if (0 <= active[i].pos && active[i].pos <= fieldLength) {
                byPosition[active[i].pos].push_back(i);
            } else {
                quitf(_fail, "internal simulation moved mushroom %d outside the field", active[i].id);
            }
        }

        for (int pos = 0; pos <= fieldLength; ++pos) {
            if (byPosition[pos].size() >= 2) {
                for (int idx : byPosition[pos]) {
                    active[idx].dir = -active[idx].dir;
                }
            }
        }

        vector<int> exitedIds;
        vector<Mushroom> nextActive;
        for (const auto& mushroom : active) {
            if (mushroom.pos == 0 || mushroom.pos == fieldLength) {
                exitedIds.push_back(mushroom.id);
                if (mushroom.pos == 0) {
                    ++leftExits;
                }
            } else {
                nextActive.push_back(mushroom);
            }
        }

        active.swap(nextActive);
        bool reverseAll = false;
        for (int id : exitedIds) {
            if (commands.count(id)) {
                reverseAll = !reverseAll;
            }
        }
        if (reverseAll) {
            for (auto& mushroom : active) {
                mushroom.dir = -mushroom.dir;
            }
        }
    }

    return leftExits;
}

struct Answer {
    int claimed;
    int achieved;
    set<int> commands;
};

Answer readAnswer(InStream& stream) {
    int claimed = stream.readInt(0, n, "maximum left exits");
    int k = stream.readInt(0, n + 1, "number of commands");

    set<int> commands;
    for (int i = 0; i < k; ++i) {
        int command = stream.readInt(0, n, format("command[%d]", i + 1).c_str());
        if (!commands.insert(command).second) {
            stream.quitf(_wa, "command %d is repeated", command);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after command list");
    }

    int achieved = simulate(commands);
    if (achieved != claimed) {
        stream.quitf(_wa, "claimed %d left exits, but commands achieve %d", claimed, achieved);
    }

    return {claimed, achieved, commands};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    int l = inf.readInt();
    fieldLength = 4 * l;
    for (int i = 1; i <= n; ++i) {
        int p = inf.readInt();
        string c = inf.readToken("[LR]", format("direction[%d]", i).c_str());
        initialMushrooms.push_back({4 * p + 1, c == "L" ? -1 : 1, i});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.achieved < jury.achieved) {
        quitf(_wa, "jury achieves %d left exits, participant achieves %d", jury.achieved, participant.achieved);
    }
    if (participant.achieved > jury.achieved) {
        quitf(_fail, "participant found better answer: jury=%d participant=%d", jury.achieved, participant.achieved);
    }
    quitf(_ok, "answer=%d", participant.achieved);
}
