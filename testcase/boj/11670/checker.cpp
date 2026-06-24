#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

struct PairInput {
    long long a;
    long long b;
};

struct Answer {
    bool impossible;
    vector<long long> results;
};

vector<PairInput> pairs;

long long parseLongLongToken(InStream& stream, const string& token, const char* name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name);
    }

    int pos = 0;
    if (token[pos] == '-') {
        ++pos;
        if (pos == (int)token.size()) {
            stream.quitf(_wa, "%s is not an integer: %s", name, token.c_str());
        }
    }

    long long value = 0;
    const long long limit = token[0] == '-' ? 1000000000000LL : 1000000000000LL;
    for (int i = pos; i < (int)token.size(); ++i) {
        if (token[i] < '0' || token[i] > '9') {
            stream.quitf(_wa, "%s is not an integer: %s", name, token.c_str());
        }
        int digit = token[i] - '0';
        if (value > (limit - digit) / 10) {
            stream.quitf(_wa, "%s is outside the allowed range: %s", name, token.c_str());
        }
        value = value * 10 + digit;
    }

    if (token[0] == '-') {
        value = -value;
    }
    return value;
}

long long eval(long long a, const string& op, long long b) {
    if (op == "+") {
        return a + b;
    }
    if (op == "-") {
        return a - b;
    }
    if (op == "*") {
        return a * b;
    }
    return 0;
}

Answer readAnswer(InStream& stream) {
    string first = stream.readWord();

    if (first == "impossible") {
        stream.readEoln();
        stream.readEof();
        return {true, {}};
    }

    vector<long long> results;
    set<long long> used;

    for (int i = 0; i < (int)pairs.size(); ++i) {
        string aToken = i == 0 ? first : stream.readWord();
        long long a = parseLongLongToken(stream, aToken, format("a[%d]", i + 1).c_str());
        string op = stream.readToken("[+\\-*]", format("operator[%d]", i + 1).c_str());
        long long b = stream.readLong(-1000000LL, 1000000LL, format("b[%d]", i + 1).c_str());
        string eq = stream.readToken("[=]", format("equals[%d]", i + 1).c_str());
        long long result = stream.readLong(-1000000000000LL, 1000000000000LL,
                                           format("result[%d]", i + 1).c_str());
        stream.readEoln();

        if (a != pairs[i].a) {
            stream.quitf(_wa, "line %d has a=%lld, expected %lld", i + 1, a, pairs[i].a);
        }
        if (b != pairs[i].b) {
            stream.quitf(_wa, "line %d has b=%lld, expected %lld", i + 1, b, pairs[i].b);
        }
        if (eq != "=") {
            stream.quitf(_wa, "line %d has invalid equals token %s", i + 1, eq.c_str());
        }

        long long expected = eval(a, op, b);
        if (result != expected) {
            stream.quitf(_wa, "line %d has result %lld, expected %lld", i + 1, result, expected);
        }
        if (!used.insert(result).second) {
            stream.quitf(_wa, "result %lld is repeated", result);
        }
        results.push_back(result);
    }

    stream.readEof();
    return {false, results};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    pairs.resize(n);
    for (int i = 0; i < n; ++i) {
        pairs[i].a = inf.readLong();
        pairs[i].b = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid answer while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury has a valid answer");
    }

    quitf(_ok, "valid answer with %d distinct results", n);
}
