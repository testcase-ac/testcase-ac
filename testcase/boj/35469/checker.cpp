#include "testlib.h"

#include <cctype>
#include <limits>
#include <string>
#include <vector>

using namespace std;

int n, k;
vector<vector<int>> a;

bool parseIntToken(const string& token, int& value) {
    if (token.empty()) {
        return false;
    }
    int pos = 0;
    if (token[0] == '-' || token[0] == '+') {
        pos = 1;
    }
    if (pos == (int)token.size()) {
        return false;
    }
    long long parsed = 0;
    for (int i = pos; i < (int)token.size(); ++i) {
        if (!isdigit((unsigned char)token[i])) {
            return false;
        }
        parsed = parsed * 10 + (token[i] - '0');
        if (parsed > (long long)numeric_limits<int>::max() + 1) {
            return false;
        }
    }
    if (token[0] == '-') {
        parsed = -parsed;
    }
    if (parsed < numeric_limits<int>::min() || parsed > numeric_limits<int>::max()) {
        return false;
    }
    value = (int)parsed;
    return true;
}

struct Answer {
    bool lose;
    bool validWitness;
};

Answer readAnswer(InStream& stream) {
    string first = stream.readToken();
    if (first == "LOSE") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after LOSE");
        }
        return {true, false};
    }

    vector<vector<int>> b(n, vector<int>(n));
    int firstValue = 0;
    if (!parseIntToken(first, firstValue)) {
        stream.quitf(_wa, "first output token is neither LOSE nor an integer: %s", first.c_str());
    }
    if (firstValue < -2000 || firstValue > 2000) {
        stream.quitf(_wa, "B[1][1]=%d is outside [-2000, 2000]", firstValue);
    }
    b[0][0] = firstValue;

    bool different = (b[0][0] != a[0][0]);
    for (int i = 0; i < n; ++i) {
        for (int j = (i == 0 ? 1 : 0); j < n; ++j) {
            b[i][j] = stream.readInt(-2000, 2000, format("B[%d][%d]", i + 1, j + 1).c_str());
            if (b[i][j] != a[i][j]) {
                different = true;
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after grid");
    }

    if (!different) {
        stream.quitf(_wa, "B is identical to A");
    }

    vector<vector<long long>> prefix(n + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            long long diff = (long long)b[i][j] - a[i][j];
            prefix[i + 1][j + 1] = prefix[i][j + 1] + prefix[i + 1][j] - prefix[i][j] + diff;
        }
    }

    for (int i = 0; i + k <= n; ++i) {
        for (int j = 0; j + k <= n; ++j) {
            long long sum = prefix[i + k][j + k] - prefix[i][j + k] - prefix[i + k][j] + prefix[i][j];
            if (sum != 0) {
                stream.quitf(_wa, "KxK sum differs at top-left (%d, %d): delta=%lld", i + 1, j + 1, sum);
            }
        }
    }

    return {false, true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    a.assign(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.lose) {
        if (participant.lose) {
            quitf(_ok, "both outputs are LOSE");
        }
        if (participant.validWitness) {
            quitf(_fail, "participant found a valid witness while jury output is LOSE");
        }
    }

    if (participant.lose) {
        quitf(_wa, "participant output is LOSE but jury has a valid witness");
    }

    quitf(_ok, "valid witness");
}
