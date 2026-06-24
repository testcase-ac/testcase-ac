#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

long long n;

struct Answer {
    bool impossible;
};

bool isPositiveIntegerToken(const string& token) {
    if (token.empty()) {
        return false;
    }
    if (token.size() > 1 && token[0] == '0') {
        return false;
    }
    for (char ch : token) {
        if (ch < '0' || ch > '9') {
            return false;
        }
    }
    return token != "0";
}

long long parsePositiveInteger(const string& token, InStream& stream, const char* name) {
    if (!isPositiveIntegerToken(token)) {
        stream.quitf(_wa, "%s must be a positive integer without leading zeroes", name);
    }

    long long value = 0;
    for (char ch : token) {
        int digit = ch - '0';
        if (value > (n - digit) / 10) {
            stream.quitf(_wa, "%s is too large", name);
        }
        value = value * 10 + digit;
    }
    return value;
}

void markDigits(const string& token, vector<int>& used, InStream& stream) {
    for (char ch : token) {
        int digit = ch - '0';
        if (used[digit]) {
            stream.quitf(_wa, "digit %d is used more than once", digit);
        }
        used[digit] = 1;
    }
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken("[+-]?[0-9]+", "first token");

    if (first == "-1") {
        stream.readEoln();
        stream.readEof();
        return {true};
    }

    long long a = parsePositiveInteger(first, stream, "A");
    string plus = stream.readToken();
    if (plus != "+") {
        stream.quitf(_wa, "expected '+', found '%s'", plus.c_str());
    }

    string second = stream.readToken("[+-]?[0-9]+", "B");
    long long b = parsePositiveInteger(second, stream, "B");

    stream.readEoln();
    stream.readEof();

    if (a + b != n) {
        stream.quitf(_wa, "A + B must equal %lld, found %lld + %lld = %lld", n, a, b, a + b);
    }

    vector<int> used(10, 0);
    markDigits(first, used, stream);
    markDigits(second, used, stream);

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong(1LL, 1000000000LL, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.impossible) {
        if (participant.impossible) {
            quitf(_wa, "jury has a valid decomposition but participant printed -1");
        }
        quitf(_ok, "valid decomposition");
    }

    if (participant.impossible) {
        quitf(_ok, "both outputs claim impossible");
    }

    quitf(_fail, "participant found a valid decomposition while jury printed -1");
}
