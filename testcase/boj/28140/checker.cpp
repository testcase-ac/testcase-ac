#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

struct Query {
    int l;
    int r;
};

struct Claim {
    bool impossible;
};

int n, q;
string s;
vector<Query> queries;

Claim readClaim(InStream& stream, int queryIndex, bool jury) {
    const Query& query = queries[queryIndex];
    TResult invalid = jury ? _fail : _wa;

    int a = stream.readInt(-1, n - 1, format("query[%d].a_or_minus_one", queryIndex + 1).c_str());
    if (a == -1) {
        stream.readEoln();
        return {true};
    }

    stream.readSpace();
    int b = stream.readInt(0, n - 1, format("query[%d].b", queryIndex + 1).c_str());
    stream.readSpace();
    int c = stream.readInt(0, n - 1, format("query[%d].c", queryIndex + 1).c_str());
    stream.readSpace();
    int d = stream.readInt(0, n - 1, format("query[%d].d", queryIndex + 1).c_str());
    stream.readEoln();

    if (!(query.l <= a && a < b && b < c && c < d && d <= query.r)) {
        stream.quitf(invalid,
                     "query %d indices must satisfy %d <= a < b < c < d <= %d, found %d %d %d %d",
                     queryIndex + 1, query.l, query.r, a, b, c, d);
    }
    if (s[a] != 'R' || s[b] != 'R' || s[c] != 'B' || s[d] != 'B') {
        stream.quitf(invalid,
                     "query %d expected S[a]=S[b]=R and S[c]=S[d]=B, found %c %c %c %c",
                     queryIndex + 1, s[a], s[b], s[c], s[d]);
    }

    return {false};
}

vector<Claim> readOutput(InStream& stream, bool jury) {
    vector<Claim> claims;
    claims.reserve(q);
    for (int i = 0; i < q; ++i) {
        claims.push_back(readClaim(stream, i, jury));
    }
    stream.readEof();
    return claims;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    q = inf.readInt();
    s = inf.readToken();

    queries.resize(q);
    for (int i = 0; i < q; ++i) {
        queries[i].l = inf.readInt();
        queries[i].r = inf.readInt();
    }

    vector<Claim> jury = readOutput(ans, true);
    vector<Claim> participant = readOutput(ouf, false);

    for (int i = 0; i < q; ++i) {
        if (!jury[i].impossible) {
            if (participant[i].impossible) {
                quitf(_wa, "query %d has a jury witness, but participant printed -1", i + 1);
            }
            continue;
        }

        if (!participant[i].impossible) {
            quitf(_fail, "query %d has a valid participant witness while jury printed -1", i + 1);
        }
    }

    quitf(_ok, "all %d query outputs are valid against the jury baseline", q);
}
