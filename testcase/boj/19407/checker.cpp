#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct Team {
    string a;
    string b;
    string c;
};

struct Claim {
    bool impossible = false;
    int n = 0;
    vector<Team> teams;
};

bool isIdentifier(const string& s) {
    if (s.empty()) return false;
    for (char ch : s) {
        if (!(ch >= 'a' && ch <= 'z') && !(ch >= '0' && ch <= '9')) return false;
    }
    return true;
}

Claim readClaim(InStream& stream) {
    string first = stream.readToken();
    if (first == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        Claim claim;
        claim.impossible = true;
        return claim;
    }

    int n;
    try {
        n = stoi(first);
    } catch (...) {
        stream.quitf(_wa, "first token must be -1 or n, found '%s'", first.c_str());
    }
    if (to_string(n) != first) {
        stream.quitf(_wa, "n must be a decimal integer, found '%s'", first.c_str());
    }
    if (n < 1 || n > 100) {
        stream.quitf(_wa, "n=%d is outside [1, 100]", n);
    }

    int q = stream.readInt(1, 10000, "q");
    vector<Team> teams;
    teams.reserve(q);
    for (int i = 0; i < q; ++i) {
        string a = stream.readToken();
        string b = stream.readToken();
        string c = stream.readToken();
        if (!isIdentifier(a)) {
            stream.quitf(_wa, "a[%d]='%s' is not a valid identifier", i + 1, a.c_str());
        }
        if (!isIdentifier(b)) {
            stream.quitf(_wa, "b[%d]='%s' is not a valid identifier", i + 1, b.c_str());
        }
        if (!isIdentifier(c)) {
            stream.quitf(_wa, "c[%d]='%s' is not a valid identifier", i + 1, c.c_str());
        }
        if (a == b || a == c || b == c) {
            stream.quitf(_wa, "team %d does not contain three different students", i + 1);
        }
        teams.push_back({a, b, c});
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after team list");
    }
    return {.impossible = false, .n = n, .teams = teams};
}

struct SimulationResult {
    bool allAssigned = true;
    int failedTraining = -1;
};

SimulationResult simulate(const Claim& claim, bool strategyB) {
    map<string, vector<char>> seen;
    vector<int> popularity(claim.n + 1, 0);

    for (int i = 0; i < (int)claim.teams.size(); ++i) {
        const Team& team = claim.teams[i];
        for (const string* id : {&team.a, &team.b, &team.c}) {
            if (!seen.count(*id)) {
                seen[*id] = vector<char>(claim.n + 1, 0);
            }
        }

        int chosen = -1;
        int bestPopularity = -1;
        for (int setId = 1; setId <= claim.n; ++setId) {
            if (seen[team.a][setId] || seen[team.b][setId] || seen[team.c][setId]) {
                continue;
            }
            if (!strategyB) {
                chosen = setId;
                break;
            }
            if (popularity[setId] > bestPopularity) {
                bestPopularity = popularity[setId];
                chosen = setId;
            }
        }

        if (chosen == -1) {
            return {.allAssigned = false, .failedTraining = i + 1};
        }

        seen[team.a][chosen] = 1;
        seen[team.b][chosen] = 1;
        seen[team.c][chosen] = 1;
        popularity[chosen] += 3;
    }

    return {};
}

bool isValidWitnessForInput(int t, const Claim& claim, InStream& stream) {
    if (claim.impossible) return false;
    if (t == 0) return true;

    SimulationResult a = simulate(claim, false);
    SimulationResult b = simulate(claim, true);
    if (t == 1) {
        return a.allAssigned && !b.allAssigned;
    }
    if (t == 2) {
        return b.allAssigned && !a.allAssigned;
    }
    stream.quitf(_fail, "input t=%d is outside [0, 2]", t);
}

void validateJuryClaim(int t, const Claim& jury) {
    if (jury.impossible) return;
    if (!isValidWitnessForInput(t, jury, ans)) {
        quitf(_fail, "jury witness is invalid for t=%d", t);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt(0, 2, "t");
    if (!inf.seekEof()) {
        quitf(_fail, "extra input after t");
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    validateJuryClaim(t, jury);

    bool participantValid = !participant.impossible && isValidWitnessForInput(t, participant, ouf);
    if (jury.impossible) {
        if (participantValid) {
            quitf(_fail, "participant found a valid witness while jury output is -1");
        }
        if (participant.impossible) {
            quitf(_ok, "both outputs report -1");
        }
        quitf(_wa, "participant witness is invalid");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports -1 while jury has a valid witness");
    }
    if (!participantValid) {
        quitf(_wa, "participant witness is invalid for t=%d", t);
    }
    quitf(_ok, "valid witness for t=%d", t);
}
