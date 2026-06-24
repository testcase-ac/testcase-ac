#include "testlib.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace {

int n;
vector<string> men;
vector<string> women;
map<string, int> manIndex;
map<string, int> womanIndex;
vector<vector<int>> manRank;
vector<vector<int>> womanRank;

string readName(InStream& stream, const string& fieldName) {
    return stream.readToken("[a-z0-9]{4,10}", fieldName);
}

vector<string> readNameList(int count, const string& fieldPrefix) {
    vector<string> names(count);
    for (int i = 0; i < count; ++i) {
        names[i] = readName(inf, format("%s_%d", fieldPrefix.c_str(), i + 1));
    }
    return names;
}

void readInput() {
    n = inf.readInt();
    men = readNameList(n, "man");
    women = readNameList(n, "woman");

    for (int i = 0; i < n; ++i) {
        manIndex[men[i]] = i;
        womanIndex[women[i]] = i;
    }

    manRank.assign(n, vector<int>(n, -1));
    womanRank.assign(n, vector<int>(n, -1));

    for (int row = 0; row < n; ++row) {
        string manName = readName(inf, "man_preference_owner");
        int man = manIndex[manName];
        for (int rank = 0; rank < n; ++rank) {
            string womanName = readName(inf, "man_preference");
            int woman = womanIndex[womanName];
            manRank[man][woman] = rank;
        }
    }

    for (int row = 0; row < n; ++row) {
        string womanName = readName(inf, "woman_preference_owner");
        int woman = womanIndex[womanName];
        for (int rank = 0; rank < n; ++rank) {
            string manName = readName(inf, "woman_preference");
            int man = manIndex[manName];
            womanRank[woman][man] = rank;
        }
    }
}

struct Matching {
    vector<int> womanOfMan;
    vector<int> manOfWoman;
};

Matching readMatching(InStream& stream) {
    Matching matching;
    matching.womanOfMan.assign(n, -1);
    matching.manOfWoman.assign(n, -1);

    for (int i = 0; i < n; ++i) {
        string manName = readName(stream, format("matching[%d].man", i + 1));
        string womanName = readName(stream, format("matching[%d].woman", i + 1));
        stream.readEoln();

        auto manIt = manIndex.find(manName);
        if (manIt == manIndex.end()) {
            stream.quitf(_wa, "unknown man name in matching line %d: %s", i + 1, manName.c_str());
        }
        auto womanIt = womanIndex.find(womanName);
        if (womanIt == womanIndex.end()) {
            stream.quitf(_wa, "unknown woman name in matching line %d: %s", i + 1, womanName.c_str());
        }

        int man = manIt->second;
        int woman = womanIt->second;
        if (matching.womanOfMan[man] != -1) {
            stream.quitf(_wa, "man %s is matched more than once", manName.c_str());
        }
        if (matching.manOfWoman[woman] != -1) {
            stream.quitf(_wa, "woman %s is matched more than once", womanName.c_str());
        }

        matching.womanOfMan[man] = woman;
        matching.manOfWoman[woman] = man;
    }

    stream.readEof();

    for (int man = 0; man < n; ++man) {
        if (matching.womanOfMan[man] == -1) {
            stream.quitf(_wa, "man %s is not matched", men[man].c_str());
        }
    }
    for (int woman = 0; woman < n; ++woman) {
        if (matching.manOfWoman[woman] == -1) {
            stream.quitf(_wa, "woman %s is not matched", women[woman].c_str());
        }
    }

    for (int man = 0; man < n; ++man) {
        int currentWoman = matching.womanOfMan[man];
        for (int woman = 0; woman < n; ++woman) {
            if (woman == currentWoman) {
                continue;
            }
            int currentMan = matching.manOfWoman[woman];
            if (manRank[man][woman] < manRank[man][currentWoman] &&
                womanRank[woman][man] < womanRank[woman][currentMan]) {
                stream.quitf(_wa,
                             "blocking pair: man %s and woman %s prefer each other",
                             men[man].c_str(),
                             women[woman].c_str());
            }
        }
    }

    return matching;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    readInput();
    readMatching(ans);
    readMatching(ouf);

    quitf(_ok, "stable matching accepted");
}
