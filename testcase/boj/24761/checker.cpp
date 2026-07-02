#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n, r;
string currentTeams, requestedTeams;
vector<pair<int, int>> rivalries;

struct Answer {
    int sittingOut;
};

Answer readAnswer(InStream& stream) {
    string formation = stream.readToken("[ABX]+", "team formation");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after team formation");
    }

    if ((int)formation.size() != n) {
        stream.quitf(_wa, "team formation length is %d, expected %d",
                     (int)formation.size(), n);
    }

    int sittingOut = 0;
    for (int i = 0; i < n; ++i) {
        if (formation[i] == 'X') {
            ++sittingOut;
            continue;
        }
        if (requestedTeams[i] != '?' && formation[i] != requestedTeams[i]) {
            stream.quitf(_wa, "student %d requested team %c but got %c",
                         i + 1, requestedTeams[i], formation[i]);
        }
    }

    for (int idx = 0; idx < r; ++idx) {
        int a = rivalries[idx].first;
        int b = rivalries[idx].second;
        if (formation[a] != 'X' && formation[b] != 'X' && formation[a] == formation[b]) {
            stream.quitf(_wa,
                         "rivalry %d has students %d and %d on the same team %c",
                         idx + 1, a + 1, b + 1, formation[a]);
        }
    }

    return {sittingOut};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    r = inf.readInt();
    currentTeams = inf.readToken();
    requestedTeams = inf.readToken();

    rivalries.reserve(r);
    for (int i = 0; i < r; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        rivalries.push_back({a - 1, b - 1});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.sittingOut < jury.sittingOut) {
        quitf(_fail, "participant found better answer: jury=%d participant=%d",
              jury.sittingOut, participant.sittingOut);
    }
    if (participant.sittingOut > jury.sittingOut) {
        quitf(_wa, "jury has better answer: jury=%d participant=%d",
              jury.sittingOut, participant.sittingOut);
    }

    quitf(_ok, "minimum sitting out count is %d", participant.sittingOut);
}
