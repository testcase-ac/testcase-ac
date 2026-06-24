#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int n;
vector<vector<int>> likes;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "selected count");
    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        return {true};
    }

    if (first == 0) {
        stream.quitf(_wa, "selected count must be positive");
    }

    stream.readEoln();

    vector<bool> usedMen(n + 1, false);
    vector<bool> usedWomen(n + 1, false);
    int women = 0;

    for (int i = 0; i < first; ++i) {
        int man = stream.readInt(1, n, format("selected man[%d]", i + 1).c_str());
        if (usedMen[man]) {
            stream.quitf(_wa, "man %d is selected more than once", man);
        }
        usedMen[man] = true;

        for (int woman : likes[man]) {
            if (!usedWomen[woman]) {
                usedWomen[woman] = true;
                ++women;
            }
        }
    }

    stream.readEoln();
    stream.readEof();

    if (first <= women) {
        stream.quitf(_wa,
                     "selected subset is smooth: selected men=%d interested women=%d",
                     first,
                     women);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 500, "N");
    int m = inf.readInt(0, n * n, "M");
    likes.assign(n + 1, {});

    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int man = inf.readInt(1, n, format("u[%d]", i + 1).c_str());
        int woman = inf.readInt(1, n, format("v[%d]", i + 1).c_str());
        if (!edges.insert({man, woman}).second) {
            quitf(_fail, "input contains duplicate relation (%d, %d)", man, woman);
        }
        likes[man].push_back(woman);
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant found a valid subset while jury says impossible");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "jury provides a valid subset but participant says impossible");
    }

    quitf(_ok, "valid output");
}
