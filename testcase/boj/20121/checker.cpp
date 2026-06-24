#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct TestCase {
    ll n;
    ll a;
    ll b;
};

struct Claim {
    string moves;
};

ll applyMove(ll pos, ll n, char move) {
    if (move == 'X') {
        return (2 * pos) % n;
    }
    return (2 * pos + 1) % n;
}

Claim readClaim(InStream& stream, const vector<TestCase>& cases) {
    vector<string> moves(cases.size());
    for (int tc = 0; tc < int(cases.size()); ++tc) {
        string s = stream.readToken("[XY]+", format("S[%d]", tc + 1).c_str());

        ll pos = cases[tc].a;
        for (char move : s) {
            pos = applyMove(pos, cases[tc].n, move);
        }
        if (pos != cases[tc].b) {
            stream.quitf(_wa,
                         "case %d: sequence sends card %lld to position %lld, expected %lld",
                         tc + 1,
                         cases[tc].a + 1,
                         pos + 1,
                         cases[tc].b + 1);
        }
        moves[tc] = s;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d sequence(s)", int(cases.size()));
    }

    Claim claim;
    for (const string& s : moves) {
        claim.moves += s;
        claim.moves.push_back('\n');
    }
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<TestCase> cases(t);
    for (int i = 0; i < t; ++i) {
        ll n = inf.readLong();
        ll a = inf.readLong();
        ll b = inf.readLong();
        cases[i] = {n, a - 1, b - 1};
    }

    Claim jury = readClaim(ans, cases);
    Claim participant = readClaim(ouf, cases);

    vector<string> juryMoves;
    vector<string> participantMoves;
    {
        stringstream js(jury.moves), ps(participant.moves);
        string s;
        while (getline(js, s)) juryMoves.push_back(s);
        while (getline(ps, s)) participantMoves.push_back(s);
    }

    for (int tc = 0; tc < t; ++tc) {
        int juryLen = int(juryMoves[tc].size());
        int participantLen = int(participantMoves[tc].size());
        if (participantLen < juryLen) {
            quitf(_fail,
                  "case %d: participant found shorter valid sequence: jury=%d participant=%d",
                  tc + 1,
                  juryLen,
                  participantLen);
        }
        if (participantLen > juryLen) {
            quitf(_wa,
                  "case %d: sequence is not minimum length: jury=%d participant=%d",
                  tc + 1,
                  juryLen,
                  participantLen);
        }
    }

    quitf(_ok, "%d minimum shuffle sequence(s)", t);
}
