#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> clauses;

struct Claim {
    bool impossible;
    vector<int> values;
};

int parseIntToken(InStream& stream, const string& token, const char* name) {
    char* end = nullptr;
    errno = 0;
    long value = strtol(token.c_str(), &end, 10);
    if (errno != 0 || end == token.c_str() || *end != '\0' || value < INT_MIN || value > INT_MAX) {
        stream.quitf(_wa, "%s must be an integer, found '%s'", name, token.c_str());
    }
    return (int)value;
}

void validateAssignment(InStream& stream, const vector<int>& values) {
    for (int i = 0; i < m; ++i) {
        bool satisfied = false;
        for (int literal : clauses[i]) {
            int variable = abs(literal);
            int value = values[variable];
            if ((literal > 0 && value == 1) || (literal < 0 && value == 0)) {
                satisfied = true;
                break;
            }
        }
        if (!satisfied) {
            stream.quitf(_wa, "clause %d is not satisfied", i + 1);
        }
    }
}

Claim readClaim(InStream& stream) {
    string firstToken = stream.readToken();
    int firstValue = parseIntToken(stream, firstToken, "first output value");

    if (firstValue == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}};
    }

    if (firstValue != 0 && firstValue != 1) {
        stream.quitf(_wa, "assignment value 1 is %d, expected 0 or 1", firstValue);
    }

    vector<int> values(n + 1);
    values[1] = firstValue;
    for (int i = 2; i <= n; ++i) {
        values[i] = stream.readInt(0, 1, format("assignment value %d", i).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after assignment");
    }

    validateAssignment(stream, values);
    return {false, values};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    clauses.resize(m);
    for (int i = 0; i < m; ++i) {
        int k = inf.readInt();
        clauses[i].resize(k);
        for (int j = 0; j < k; ++j) {
            clauses[i][j] = inf.readInt();
        }
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "jury provides a satisfying assignment, but participant printed -1");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant found a satisfying assignment while jury printed -1");
    }

    if (jury.impossible) {
        quitf(_ok, "both outputs report impossible");
    }
    quitf(_ok, "valid satisfying assignment");
}
