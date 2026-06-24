#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> names;
map<string, int> idByName;

struct Race {
    int winnerRank;
    vector<int> horses;
};

vector<Race> races;

vector<int> readAnswer(InStream& stream) {
    vector<int> order(n);
    vector<int> seen(n, 0);

    for (int i = 0; i < n; ++i) {
        string name = stream.readToken("[a-z]{1,3}", format("horse[%d]", i + 1).c_str());
        auto it = idByName.find(name);
        if (it == idByName.end()) {
            stream.quitf(_wa, "unknown horse name '%s' at output position %d", name.c_str(), i + 1);
        }
        int id = it->second;
        if (seen[id]) {
            stream.quitf(_wa, "horse '%s' appears more than once", name.c_str());
        }
        seen[id] = 1;
        order[i] = id;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after horse order");
    }

    vector<int> rank(n);
    for (int i = 0; i < n; ++i) {
        rank[order[i]] = i + 1;
    }

    for (int i = 0; i < (int)races.size(); ++i) {
        int bestRank = n + 1;
        int bestHorse = -1;
        for (int horse : races[i].horses) {
            if (rank[horse] < bestRank) {
                bestRank = rank[horse];
                bestHorse = horse;
            }
        }
        if (bestRank != races[i].winnerRank) {
            stream.quitf(_wa,
                         "race %d winner has rank %d (%s), expected rank %d",
                         i + 1,
                         bestRank,
                         names[bestHorse].c_str(),
                         races[i].winnerRank);
        }
    }

    return order;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 300, "N");
    names.resize(n);
    for (int i = 0; i < n; ++i) {
        names[i] = inf.readToken("[a-z]{1,3}", format("name[%d]", i + 1).c_str());
        if (idByName.count(names[i])) {
            quitf(_fail, "duplicate horse name '%s' in input", names[i].c_str());
        }
        idByName[names[i]] = i;
    }

    int r = inf.readInt(1, 100000, "R");
    races.reserve(r);
    long long totalParticipants = 0;
    for (int i = 0; i < r; ++i) {
        int m = inf.readInt(2, n, format("M[%d]", i + 1).c_str());
        int w = inf.readInt(1, n, format("W[%d]", i + 1).c_str());
        totalParticipants += m;
        vector<int> horses;
        horses.reserve(m);
        vector<int> used(n, 0);
        for (int j = 0; j < m; ++j) {
            string name = inf.readToken("[a-z]{1,3}", format("race[%d].horse[%d]", i + 1, j + 1).c_str());
            auto it = idByName.find(name);
            if (it == idByName.end()) {
                quitf(_fail, "unknown horse name '%s' in input race %d", name.c_str(), i + 1);
            }
            int id = it->second;
            if (used[id]) {
                quitf(_fail, "horse '%s' appears twice in input race %d", name.c_str(), i + 1);
            }
            used[id] = 1;
            horses.push_back(id);
        }
        races.push_back({w, horses});
    }
    if (totalParticipants > 100000) {
        quitf(_fail, "sum of M_i is %lld, expected at most 100000", totalParticipants);
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid race order");
}
