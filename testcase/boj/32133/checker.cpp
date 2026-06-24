#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int N, M, K;
vector<string> moves;

bool beats(char friendMove, char pidoriMove) {
    return (friendMove == 'R' && pidoriMove == 'S') ||
           (friendMove == 'S' && pidoriMove == 'P') ||
           (friendMove == 'P' && pidoriMove == 'R');
}

struct Claim {
    bool impossible;
    int rounds;
};

Claim readClaim(InStream& stream) {
    int first = stream.readInt(-1, M, "round count or -1");
    stream.readEoln();

    if (first == -1) {
        stream.readEof();
        return {true, -1};
    }

    if (first < 1) {
        stream.quitf(_wa, "round count must be -1 or between 1 and %d, found %d", M, first);
    }

    string strategy = stream.readToken("[RSP]+", "strategy");
    stream.readEoln();
    stream.readEof();

    if ((int)strategy.size() != first) {
        stream.quitf(_wa, "strategy length is %d, expected %d", (int)strategy.size(), first);
    }

    vector<int> alive(N);
    iota(alive.begin(), alive.end(), 0);

    for (int round = 0; round < first; ++round) {
        vector<int> nextAlive;
        for (int person : alive) {
            if (beats(moves[person][round], strategy[round])) {
                nextAlive.push_back(person);
            }
        }
        alive.swap(nextAlive);

        if (alive.empty()) {
            stream.quitf(_wa, "strategy eliminates everyone after round %d", round + 1);
        }

        if ((int)alive.size() <= K) {
            if (round + 1 != first) {
                stream.quitf(_wa,
                             "strategy should stop after round %d with %d survivors, but claims %d rounds",
                             round + 1, (int)alive.size(), first);
            }
            return {false, first};
        }
    }

    stream.quitf(_wa, "strategy leaves %d survivors after %d rounds, more than K=%d",
                 (int)alive.size(), first, K);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    N = inf.readInt();
    M = inf.readInt();
    K = inf.readInt();

    moves.resize(N);
    for (int i = 0; i < N; ++i) {
        moves[i] = inf.readToken();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid strategy in %d rounds while jury reports impossible",
              participant.rounds);
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid strategy in %d rounds, but participant reports impossible",
              jury.rounds);
    }

    if (participant.rounds > jury.rounds) {
        quitf(_wa, "participant uses %d rounds, but jury uses %d",
              participant.rounds, jury.rounds);
    }

    if (participant.rounds < jury.rounds) {
        quitf(_fail, "participant found a better strategy: participant=%d jury=%d",
              participant.rounds, jury.rounds);
    }

    quitf(_ok, "valid strategy in %d rounds", participant.rounds);
}
