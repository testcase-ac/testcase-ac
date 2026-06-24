#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int n;
vector<long long> valueByIndex;
vector<pair<int, int>> edges;

string readDecision(InStream& stream) {
    string decision = stream.readToken("YES|NO", "decision");
    return decision;
}

struct Answer {
    bool possible;
};

Answer readAnswer(InStream& stream) {
    string decision = readDecision(stream);
    if (decision == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }

    vector<int> assignedIndex(n + 1);
    vector<int> used(n + 1, 0);
    for (int vertex = 1; vertex <= n; ++vertex) {
        assignedIndex[vertex] = stream.readInt(1, n, format("assignedIndex[%d]", vertex).c_str());
        if (used[assignedIndex[vertex]]) {
            stream.quitf(_wa, "array index %d is assigned more than once", assignedIndex[vertex]);
        }
        used[assignedIndex[vertex]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after assignment");
    }

    set<long long> sums;
    for (int i = 0; i < int(edges.size()); ++i) {
        int u = edges[i].first;
        int v = edges[i].second;
        long long sum = valueByIndex[assignedIndex[u]] + valueByIndex[assignedIndex[v]];
        if (!sums.insert(sum).second) {
            stream.quitf(_wa, "edge sum %lld is repeated", sum);
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    valueByIndex.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        valueByIndex[i] = inf.readLong();
    }
    edges.reserve(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges.push_back({u, v});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible) {
        if (participant.possible) {
            quitf(_fail, "participant supplied a valid assignment while jury says NO");
        }
        quitf(_ok, "both outputs say NO");
    }

    if (!participant.possible) {
        quitf(_wa, "jury has a valid assignment but participant says NO");
    }

    quitf(_ok, "valid assignment");
}
