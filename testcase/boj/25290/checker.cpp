#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct TestCase {
    long long n;
    long long k;
};

struct Claim {
    vector<bool> possible;
};

vector<TestCase> tests;

pair<long long, long long> roomCoord(long long n, long long room) {
    long long layer = 0;
    long long side = n;
    while (side > 1) {
        long long ringSize = side * side - (side - 2) * (side - 2);
        if (room <= ringSize) {
            break;
        }
        room -= ringSize;
        ++layer;
        side -= 2;
    }

    if (side == 1) {
        return {layer, layer};
    }

    long long offset = room - 1;
    if (offset < side) {
        return {layer, layer + offset};
    }
    offset -= side;

    if (offset < side - 1) {
        return {layer + 1 + offset, layer + side - 1};
    }
    offset -= side - 1;

    if (offset < side - 1) {
        return {layer + side - 1, layer + side - 2 - offset};
    }
    offset -= side - 1;

    return {layer + side - 2 - offset, layer};
}

bool adjacentInSpiral(long long n, long long a, long long b) {
    auto [ar, ac] = roomCoord(n, a);
    auto [br, bc] = roomCoord(n, b);
    return llabs(ar - br) + llabs(ac - bc) == 1;
}

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.possible.resize(tests.size());

    for (int tc = 1; tc <= (int)tests.size(); ++tc) {
        const auto& test = tests[tc - 1];
        string caseWord = stream.readWord();
        if (caseWord != "Case") {
            stream.quitf(_wa, "case %d starts with '%s' instead of 'Case'", tc, caseWord.c_str());
        }

        string caseNumber = stream.readWord();
        string expectedCaseNumber = format("#%d:", tc);
        if (caseNumber != expectedCaseNumber) {
            stream.quitf(_wa, "case %d has label '%s' instead of '%s'",
                         tc, caseNumber.c_str(), expectedCaseNumber.c_str());
        }

        string result = stream.readWord();
        if (result == "IMPOSSIBLE") {
            claim.possible[tc - 1] = false;
            continue;
        }

        long long shortcutCount;
        try {
            size_t parsed = 0;
            shortcutCount = stoll(result, &parsed);
            if (parsed != result.size()) {
                stream.quitf(_wa, "case %d result '%s' is neither IMPOSSIBLE nor an integer",
                             tc, result.c_str());
            }
        } catch (...) {
            stream.quitf(_wa, "case %d result '%s' is neither IMPOSSIBLE nor an integer",
                         tc, result.c_str());
        }

        if (shortcutCount < 0 || shortcutCount > test.k) {
            stream.quitf(_wa, "case %d has invalid shortcut count %lld", tc, shortcutCount);
        }

        long long current = 1;
        long long moves = 0;
        long long previousStart = 0;
        long long maxRoom = test.n * test.n;
        for (long long i = 1; i <= shortcutCount; ++i) {
            long long a = stream.readLong(1, maxRoom, format("case %d shortcut %lld start", tc, i).c_str());
            long long b = stream.readLong(1, maxRoom, format("case %d shortcut %lld end", tc, i).c_str());

            if (a <= previousStart) {
                stream.quitf(_wa, "case %d shortcut %lld starts at %lld after previous start %lld",
                             tc, i, a, previousStart);
            }
            if (a < current) {
                stream.quitf(_wa, "case %d shortcut %lld starts at %lld before current room %lld",
                             tc, i, a, current);
            }
            if (a + 1 >= b) {
                stream.quitf(_wa, "case %d shortcut %lld from %lld to %lld is not a shortcut",
                             tc, i, a, b);
            }
            if (!adjacentInSpiral(test.n, a, b)) {
                stream.quitf(_wa, "case %d shortcut %lld from %lld to %lld is not between adjacent rooms",
                             tc, i, a, b);
            }

            moves += a - current;
            moves += 1;
            current = b;
            previousStart = a;
        }

        moves += maxRoom - current;
        if (moves != test.k) {
            stream.quitf(_wa, "case %d takes %lld moves instead of %lld", tc, moves, test.k);
        }

        claim.possible[tc - 1] = true;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after case %d", (int)tests.size());
    }
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    tests.resize(t);
    for (int i = 0; i < t; ++i) {
        tests[i].n = inf.readLong();
        tests[i].k = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    for (int i = 0; i < t; ++i) {
        if (jury.possible[i] && !participant.possible[i]) {
            quitf(_wa, "case %d: participant reported IMPOSSIBLE but jury has a valid certificate", i + 1);
        }
        if (!jury.possible[i] && participant.possible[i]) {
            quitf(_fail, "case %d: participant has a valid certificate while jury reports IMPOSSIBLE", i + 1);
        }
    }

    quitf(_ok, "all %d case(s) match the jury feasibility claim", t);
}
