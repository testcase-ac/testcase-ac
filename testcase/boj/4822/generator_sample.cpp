#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Match {
    int a;
    int b;
    int x;
    int y;
};

string teamName(int index) {
    static const vector<string> names = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
        "Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Zeta",
        "Orion", "Nova", "Comet", "Meteor"
    };
    return names[index];
}

pair<int, int> playedScore(int mode) {
    if (mode == 0) {
        int base = rnd.next(0, 4);
        return {base, base};
    }
    if (mode == 1) {
        return {rnd.next(0, 6), rnd.next(0, 6)};
    }
    if (mode == 2) {
        return {rnd.next(0, 1000000), rnd.next(0, 1000000)};
    }
    int winner = rnd.next(0, 1);
    int low = rnd.next(0, 3);
    int high = rnd.next(low + 1, low + 7);
    return winner == 0 ? make_pair(high, low) : make_pair(low, high);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(1, 4);
    for (int tc = 0; tc < caseCount; ++tc) {
        int mode = rnd.next(0, 5);
        int n = 2;
        if (mode == 0) {
            n = 2;
        } else if (mode == 5) {
            n = rnd.next(12, 20);
        } else {
            n = rnd.next(3, 8);
        }

        vector<pair<int, int>> pairs;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                pairs.push_back({i, j});
            }
        }
        shuffle(pairs.begin(), pairs.end());

        int maxCompact = min<int>(pairs.size(), mode == 5 ? 30 : 14);
        int m = rnd.next(1, maxCompact);
        vector<Match> matches;
        for (int i = 0; i < m; ++i) {
            auto p = pairs[i % pairs.size()];
            if (mode == 3 && rnd.next(0, 3) == 0) {
                p = pairs[rnd.next(0, (int)pairs.size() - 1)];
            }
            if (rnd.next(0, 1)) {
                swap(p.first, p.second);
            }

            auto score = playedScore(mode % 4);
            matches.push_back({p.first, p.second, score.first, score.second});
        }

        int unplayedLimit = min(12, m);
        int unplayed = 0;
        if (mode == 0) {
            unplayed = rnd.next(0, unplayedLimit);
        } else if (mode == 4) {
            unplayed = unplayedLimit;
        } else {
            unplayed = rnd.next(0, min(unplayedLimit, max(1, m / 2)));
        }

        vector<int> order(m);
        for (int i = 0; i < m; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());
        for (int i = 0; i < unplayed; ++i) {
            matches[order[i]].x = -1;
            matches[order[i]].y = -1;
        }

        println(n, m);
        for (int i = 0; i < n; ++i) {
            println(teamName(i));
        }
        for (const Match& match : matches) {
            printf("%s vs %s: %d %d\n",
                   teamName(match.a).c_str(),
                   teamName(match.b).c_str(),
                   match.x,
                   match.y);
        }
    }

    println(0, 0);
    return 0;
}
