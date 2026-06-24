#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int n;
int k;

struct Answer {
    bool impossible;
};

bool parseIntToken(const string& token, int low, int high, int& value) {
    if (token.empty()) {
        return false;
    }
    int pos = 0;
    if (token[0] == '-') {
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
        if (parsed > 1000000000LL) {
            return false;
        }
    }
    if (pos == 1) {
        parsed = -parsed;
    }
    if (parsed < low || parsed > high) {
        return false;
    }
    value = (int)parsed;
    return true;
}

Answer readAnswer(InStream& stream) {
    string first = stream.readWord("Impossible|[-]?[0-9]+", "first output token");

    if (first == "Impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after Impossible");
        }
        return {true};
    }

    vector<int> a(n + 1);
    vector<int> seen(n + 1, 0);

    int firstValue = 0;
    if (!parseIntToken(first, 1, n, firstValue)) {
        stream.quitf(_wa, "A[1] must be an integer between 1 and %d", n);
    }
    a[1] = firstValue;
    seen[firstValue] = 1;

    for (int i = 2; i <= n; ++i) {
        a[i] = stream.readInt(1, n, format("A[%d]", i).c_str());
        if (seen[a[i]]) {
            stream.quitf(_wa, "value %d appears more than once", a[i]);
        }
        seen[a[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    int good = 0;
    for (int i = 1; i <= n; ++i) {
        if (gcd(i, a[i]) > 1) {
            ++good;
        }
    }
    if (good != k) {
        stream.quitf(_wa, "expected %d positions with gcd(i, A[i]) > 1, found %d", k, good);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs report Impossible");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "jury provides a valid sequence, but participant reports Impossible");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant provides a valid sequence while jury reports Impossible");
    }

    quitf(_ok, "valid sequence");
}
