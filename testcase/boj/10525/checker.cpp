#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Answer {
    long long usedFrequencies;
};

int n;
vector<pair<int, int>> edges;

Answer readAnswer(InStream& stream) {
    vector<pair<int, int>> frequency(n + 1);

    for (int node = 1; node <= n; ++node) {
        int first = stream.readInt(0, 999999999, format("frequency[%d][1]", node).c_str());
        stream.readSpace();
        int second = stream.readInt(0, 999999999, format("frequency[%d][2]", node).c_str());
        frequency[node] = {first, second};
        stream.readEoln();
    }
    stream.readEof();

    set<int> used;
    for (int edgeIndex = 0; edgeIndex < (int)edges.size(); ++edgeIndex) {
        int u = edges[edgeIndex].first;
        int v = edges[edgeIndex].second;

        bool canCommunicate = false;
        if (frequency[u].first == frequency[v].first || frequency[u].first == frequency[v].second) {
            used.insert(frequency[u].first);
            canCommunicate = true;
        }
        if (frequency[u].second == frequency[v].first || frequency[u].second == frequency[v].second) {
            used.insert(frequency[u].second);
            canCommunicate = true;
        }

        if (!canCommunicate) {
            stream.quitf(_wa,
                         "edge %d (%d, %d) has no common frequency",
                         edgeIndex + 1,
                         u,
                         v);
        }
    }

    return {(long long)used.size()};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    edges.reserve(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges.push_back({u, v});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.usedFrequencies < jury.usedFrequencies) {
        quitf(_wa,
              "jury uses more frequencies: jury=%lld participant=%lld",
              jury.usedFrequencies,
              participant.usedFrequencies);
    }
    if (participant.usedFrequencies > jury.usedFrequencies) {
        quitf(_fail,
              "participant uses more frequencies: jury=%lld participant=%lld",
              jury.usedFrequencies,
              participant.usedFrequencies);
    }

    quitf(_ok, "used frequencies=%lld", participant.usedFrequencies);
}
