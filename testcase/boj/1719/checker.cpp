#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const int INF = 1'000'000'000;

int n, m;
vector<vector<int>> edgeCost;
vector<vector<int>> distCost;

TResult streamVerdict(const InStream& stream) {
    return &stream == &ouf ? _wa : _fail;
}

void readRouteTable(InStream& stream, const char* label) {
    for (int from = 1; from <= n; ++from) {
        for (int to = 1; to <= n; ++to) {
            string token = stream.readToken();
            if (from == to) {
                if (token != "-") {
                    stream.quitf(streamVerdict(stream),
                                 "%s[%d][%d] must be '-' on the diagonal, found '%s'",
                                 label,
                                 from,
                                 to,
                                 token.c_str());
                }
                continue;
            }

            int firstHop = -1;
            try {
                size_t pos = 0;
                firstHop = stoi(token, &pos);
                if (pos != token.size()) {
                    stream.quitf(streamVerdict(stream),
                                 "%s[%d][%d] must be an integer from 1 to %d, found '%s'",
                                 label,
                                 from,
                                 to,
                                 n,
                                 token.c_str());
                }
            } catch (...) {
                stream.quitf(streamVerdict(stream),
                             "%s[%d][%d] must be an integer from 1 to %d, found '%s'",
                             label,
                             from,
                             to,
                             n,
                             token.c_str());
            }

            if (firstHop < 1 || firstHop > n) {
                stream.quitf(streamVerdict(stream),
                             "%s[%d][%d] has out-of-range first hop %d",
                             label,
                             from,
                             to,
                             firstHop);
            }
            if (edgeCost[from][firstHop] == INF) {
                stream.quitf(streamVerdict(stream),
                             "%s[%d][%d] first hop %d is not adjacent to %d",
                             label,
                             from,
                             to,
                             firstHop,
                             from);
            }
            if (edgeCost[from][firstHop] + distCost[firstHop][to] != distCost[from][to]) {
                stream.quitf(streamVerdict(stream),
                             "%s[%d][%d] first hop %d is not on a shortest path: %d + %d != %d",
                             label,
                             from,
                             to,
                             firstHop,
                             edgeCost[from][firstHop],
                             distCost[firstHop][to],
                             distCost[from][to]);
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(streamVerdict(stream), "extra output after %s route table", label);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    edgeCost.assign(n + 1, vector<int>(n + 1, INF));
    distCost.assign(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; ++i) {
        edgeCost[i][i] = 0;
        distCost[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        int t = inf.readInt();
        edgeCost[a][b] = min(edgeCost[a][b], t);
        edgeCost[b][a] = min(edgeCost[b][a], t);
        distCost[a][b] = min(distCost[a][b], t);
        distCost[b][a] = min(distCost[b][a], t);
    }

    for (int mid = 1; mid <= n; ++mid) {
        for (int from = 1; from <= n; ++from) {
            for (int to = 1; to <= n; ++to) {
                if (distCost[from][mid] == INF || distCost[mid][to] == INF) {
                    continue;
                }
                distCost[from][to] =
                    min(distCost[from][to], distCost[from][mid] + distCost[mid][to]);
            }
        }
    }

    readRouteTable(ans, "jury");
    readRouteTable(ouf, "participant");

    quitf(_ok, "valid shortest-path route table for n=%d", n);
}
