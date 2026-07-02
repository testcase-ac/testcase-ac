#include "testlib.h"

#include <cctype>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    long long h;
};

struct Claim {
    bool impossible;
};

int n;
vector<Edge> edges;

bool isImpossibleToken(const string& token) {
    string lower;
    lower.reserve(token.size());
    for (char ch : token) {
        lower.push_back(char(tolower(static_cast<unsigned char>(ch))));
    }
    return lower == "impossible";
}

Claim readClaim(InStream& stream) {
    string first = stream.readToken("[A-Za-z0-9+-]+", "first output token");
    if (isImpossibleToken(first)) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true};
    }

    vector<int> starts(n + 1);
    long long firstStart = stringToLongLong(stream, first);
    if (firstStart < 1 || firstStart > n) {
        stream.quitf(_wa, "start vertex for street 1 is %lld, outside [1, %d]", firstStart, n);
    }
    starts[1] = int(firstStart);
    for (int i = 2; i <= n; ++i) {
        starts[i] = stream.readInt(1, n, format("start[%d]", i).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after numbering");
    }

    vector<map<long long, int>> adjacentNumbers(n + 1);
    for (int i = 1; i <= n; ++i) {
        const Edge& edge = edges[i];
        int start = starts[i];
        if (start != edge.u && start != edge.v) {
            stream.quitf(_wa,
                         "start vertex for street %d is %d, expected %d or %d",
                         i,
                         start,
                         edge.u,
                         edge.v);
        }

        long long atU = (start == edge.u ? 1 : edge.h);
        long long atV = (start == edge.v ? 1 : edge.h);
        auto insertedU = adjacentNumbers[edge.u].insert({atU, i});
        if (!insertedU.second) {
            stream.quitf(_wa,
                         "intersection %d has adjacent house number %lld on streets %d and %d",
                         edge.u,
                         atU,
                         insertedU.first->second,
                         i);
        }
        auto insertedV = adjacentNumbers[edge.v].insert({atV, i});
        if (!insertedV.second) {
            stream.quitf(_wa,
                         "intersection %d has adjacent house number %lld on streets %d and %d",
                         edge.v,
                         atV,
                         insertedV.first->second,
                         i);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    edges.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        edges[i].u = inf.readInt();
        edges[i].v = inf.readInt();
        edges[i].h = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid numbering while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible but jury provides a valid numbering");
    }

    quitf(_ok, "valid numbering");
}
