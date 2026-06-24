#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<vector<int>> manPref;
vector<vector<int>> womanRank;

struct Matching {
    vector<int> womanOfMan;
    vector<int> manOfWoman;
};

Matching readMatching(InStream& stream) {
    Matching matching;
    matching.womanOfMan.assign(n + 1, 0);
    matching.manOfWoman.assign(n + 1, 0);

    for (int man = 1; man <= n; ++man) {
        int woman = stream.readInt(1, n, format("match[%d]", man).c_str());
        if (matching.manOfWoman[woman] != 0) {
            stream.quitf(_wa,
                         "woman %d is matched to both man %d and man %d",
                         woman,
                         matching.manOfWoman[woman],
                         man);
        }
        matching.womanOfMan[man] = woman;
        matching.manOfWoman[woman] = man;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after matching");
    }
    return matching;
}

void ensureStable(InStream& stream, const Matching& matching) {
    for (int man = 1; man <= n; ++man) {
        int currentWoman = matching.womanOfMan[man];
        for (int preferredWoman : manPref[man]) {
            if (preferredWoman == currentWoman) {
                break;
            }

            int currentMan = matching.manOfWoman[preferredWoman];
            if (womanRank[preferredWoman][man] < womanRank[preferredWoman][currentMan]) {
                stream.quitf(_wa,
                             "blocking pair: man %d and woman %d prefer each other over %d and %d",
                             man,
                             preferredWoman,
                             currentWoman,
                             currentMan);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    manPref.assign(n + 1, vector<int>(n));
    womanRank.assign(n + 1, vector<int>(n + 1));

    for (int man = 1; man <= n; ++man) {
        for (int i = 0; i < n; ++i) {
            manPref[man][i] = inf.readInt();
        }
    }
    for (int woman = 1; woman <= n; ++woman) {
        for (int rank = 0; rank < n; ++rank) {
            int man = inf.readInt();
            womanRank[woman][man] = rank;
        }
    }

    Matching jury = readMatching(ans);
    ensureStable(ans, jury);

    Matching participant = readMatching(ouf);
    ensureStable(ouf, participant);

    quitf(_ok, "stable matching");
}
