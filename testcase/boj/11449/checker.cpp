#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<int> gas;
    vector<int> dist;
};

struct Claim {
    bool impossible;
    int station;
};

vector<TestCase> cases;

bool isPositiveIntegerToken(const string& token) {
    if (token.empty()) {
        return false;
    }
    for (char ch : token) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

Claim readClaim(InStream& stream, int tc) {
    string token = stream.readToken();
    if (token == "IMPOSSIBLE") {
        return {true, -1};
    }
    if (!isPositiveIntegerToken(token)) {
        stream.quitf(_wa, "test case %d: expected station number or IMPOSSIBLE, found '%s'",
                     tc, token.c_str());
    }

    long long value = 0;
    for (char ch : token) {
        value = value * 10 + (ch - '0');
        if (value > cases[tc - 1].n) {
            stream.quitf(_wa, "test case %d: station %lld is outside range 1..%d",
                         tc, value, cases[tc - 1].n);
        }
    }
    if (value < 1) {
        stream.quitf(_wa, "test case %d: station must be at least 1", tc);
    }
    return {false, static_cast<int>(value)};
}

bool canCompleteTrip(const TestCase& tc, int station) {
    long long fuel = 0;
    int pos = station - 1;
    for (int step = 0; step < tc.n; ++step) {
        fuel += tc.gas[pos];
        fuel -= tc.dist[pos];
        if (fuel < 0) {
            return false;
        }
        ++pos;
        if (pos == tc.n) {
            pos = 0;
        }
    }
    return true;
}

bool hasValidStart(const TestCase& tc) {
    long long balance = 0;
    for (int i = 0; i < tc.n; ++i) {
        balance += tc.gas[i];
        balance -= tc.dist[i];
    }
    return balance >= 0;
}

vector<Claim> readOutput(InStream& stream, bool juryStream) {
    vector<Claim> result;
    result.reserve(cases.size());
    for (int tc = 1; tc <= static_cast<int>(cases.size()); ++tc) {
        result.push_back(readClaim(stream, tc));
    }
    if (!stream.seekEof()) {
        stream.quitf(juryStream ? _fail : _wa, "extra output after %d test case(s)",
                     static_cast<int>(cases.size()));
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    cases.resize(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = inf.readInt();
        cases[tc].n = n;
        cases[tc].gas.resize(n);
        cases[tc].dist.resize(n);
        for (int i = 0; i < n; ++i) {
            cases[tc].gas[i] = inf.readInt();
            cases[tc].dist[i] = inf.readInt();
        }
    }

    vector<Claim> jury = readOutput(ans, true);
    vector<Claim> participant = readOutput(ouf, false);

    for (int tc = 1; tc <= t; ++tc) {
        const TestCase& current = cases[tc - 1];
        const Claim& expected = jury[tc - 1];
        const Claim& actual = participant[tc - 1];
        bool possible = hasValidStart(current);

        if (!expected.impossible && !canCompleteTrip(current, expected.station)) {
            quitf(_fail, "test case %d: jury station %d cannot complete the trip",
                  tc, expected.station);
        }
        if (expected.impossible && possible) {
            quitf(_fail, "test case %d: jury says IMPOSSIBLE, but a trip is possible", tc);
        }

        if (actual.impossible) {
            if (!possible) {
                continue;
            }
            quitf(_wa, "test case %d: participant says IMPOSSIBLE, but a trip is possible", tc);
        }

        if (!canCompleteTrip(current, actual.station)) {
            quitf(_wa, "test case %d: participant station %d cannot complete the trip",
                  tc, actual.station);
        }

        if (expected.impossible) {
            quitf(_fail, "test case %d: participant found valid station %d while jury says IMPOSSIBLE",
                  tc, actual.station);
        }
    }

    quitf(_ok, "%d test case(s) accepted", t);
}
