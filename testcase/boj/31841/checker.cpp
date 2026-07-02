#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

int n, m;
vector<int> degreeOf;
unordered_map<long long, int> edgeId;

long long edgeKey(int u, int v) {
    if (u > v) {
        swap(u, v);
    }
    return 1LL * u * (n + 1) + v;
}

void readAnswer(InStream& stream) {
    vector<int> labelUsed(m + 1, 0);
    vector<int> edgeUsed(m + 1, 0);
    vector<int> incidentGcd(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
        int u = stream.readInt(1, n, format("u[%d]", i).c_str());
        stream.readSpace();
        int v = stream.readInt(1, n, format("v[%d]", i).c_str());
        stream.readSpace();
        int c = stream.readInt(1, m, format("c[%d]", i).c_str());
        stream.readEoln();

        auto it = edgeId.find(edgeKey(u, v));
        if (it == edgeId.end()) {
            stream.quitf(_wa, "output edge %d (%d, %d) is not in the input graph", i, u, v);
        }

        int id = it->second;
        if (edgeUsed[id]) {
            stream.quitf(_wa, "input edge (%d, %d) is printed more than once", u, v);
        }
        edgeUsed[id] = 1;

        if (labelUsed[c]) {
            stream.quitf(_wa, "label %d is used more than once", c);
        }
        labelUsed[c] = 1;

        incidentGcd[u] = gcd(incidentGcd[u], c);
        incidentGcd[v] = gcd(incidentGcd[v], c);
    }

    stream.readEof();

    for (int id = 1; id <= m; ++id) {
        if (!edgeUsed[id]) {
            stream.quitf(_wa, "input edge %d is missing from output", id);
        }
    }
    for (int label = 1; label <= m; ++label) {
        if (!labelUsed[label]) {
            stream.quitf(_wa, "label %d is missing from output", label);
        }
    }
    for (int v = 1; v <= n; ++v) {
        if (degreeOf[v] > 1 && incidentGcd[v] != 1) {
            stream.quitf(_wa,
                         "vertex %d has degree %d and incident label gcd %d",
                         v,
                         degreeOf[v],
                         incidentGcd[v]);
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    degreeOf.assign(n + 1, 0);
    edgeId.reserve(m * 2);
    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        ++degreeOf[u];
        ++degreeOf[v];
        edgeId[edgeKey(u, v)] = i;
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid labeling");
}
