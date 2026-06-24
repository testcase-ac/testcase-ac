#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

int n, m;
string lollipop;
vector<int> queryValue;
vector<long long> prefixSum;

struct Claim {
    bool impossible;
    int l;
    int r;
};

int parseBoundedInt(InStream& stream, const string& token, int minValue, int maxValue, const string& name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name.c_str());
    }
    long long value = 0;
    for (char ch : token) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            stream.quitf(_wa, "%s must be an integer, found '%s'", name.c_str(), token.c_str());
        }
        value = value * 10 + (ch - '0');
        if (value > maxValue) {
            stream.quitf(_wa, "%s must be at most %d, found %lld", name.c_str(), maxValue, value);
        }
    }
    if (value < minValue) {
        stream.quitf(_wa, "%s must be at least %d, found %lld", name.c_str(), minValue, value);
    }
    return static_cast<int>(value);
}

Claim readClaim(InStream& stream, int index) {
    string first = stream.readToken();
    if (first == "NIE") {
        stream.readEoln();
        return {true, -1, -1};
    }

    int l = parseBoundedInt(stream, first, 1, n, format("query[%d] l", index + 1));
    int r = stream.readInt(1, n, format("query[%d] r", index + 1).c_str());
    stream.readEoln();

    if (l > r) {
        stream.quitf(_wa, "query[%d] has l > r: %d > %d", index + 1, l, r);
    }

    long long value = prefixSum[r] - prefixSum[l - 1];
    if (value != queryValue[index]) {
        stream.quitf(_wa,
                     "query[%d] interval [%d, %d] has value %lld, expected %d",
                     index + 1,
                     l,
                     r,
                     value,
                     queryValue[index]);
    }

    return {false, l, r};
}

vector<Claim> readOutput(InStream& stream) {
    vector<Claim> claims;
    claims.reserve(m);
    for (int i = 0; i < m; ++i) {
        claims.push_back(readClaim(stream, i));
    }
    stream.readEof();
    return claims;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    lollipop = inf.readToken();

    prefixSum.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefixSum[i] = prefixSum[i - 1] + (lollipop[i - 1] == 'T' ? 2 : 1);
    }

    queryValue.resize(m);
    for (int i = 0; i < m; ++i) {
        queryValue[i] = inf.readInt();
    }

    vector<Claim> jury = readOutput(ans);
    vector<Claim> participant = readOutput(ouf);

    for (int i = 0; i < m; ++i) {
        if (!jury[i].impossible && participant[i].impossible) {
            quitf(_wa, "query[%d] has a jury witness, but participant printed NIE", i + 1);
        }
        if (jury[i].impossible && !participant[i].impossible) {
            quitf(_fail,
                  "query[%d] jury printed NIE, but participant found valid interval [%d, %d]",
                  i + 1,
                  participant[i].l,
                  participant[i].r);
        }
    }

    quitf(_ok, "all %d queries are valid", m);
}
