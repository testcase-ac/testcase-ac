#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int INF = 1'000'000'000;

int n, m;
vector<vector<int>> targetDist;

struct Answer {
    int possible;
};

void validateWitness(InStream& stream, vector<vector<int>>& dist) {
    for (int i = 0; i < m; ++i) {
        int a = stream.readInt(1, n, format("edge[%d].a", i + 1).c_str());
        stream.readSpace();
        int b = stream.readInt(1, n, format("edge[%d].b", i + 1).c_str());
        stream.readSpace();
        int c = stream.readInt(1, 500, format("edge[%d].c", i + 1).c_str());
        stream.readEoln();

        if (a == b) {
            stream.quitf(_wa, "edge %d has equal endpoints %d", i + 1, a);
        }
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (dist[i][j] != targetDist[i][j]) {
                stream.quitf(_wa,
                             "distance between %d and %d is %d, expected %d",
                             i,
                             j,
                             dist[i][j],
                             targetDist[i][j]);
            }
        }
    }
}

Answer readAnswer(InStream& stream) {
    int possible = stream.readInt(0, 1, "possible");
    stream.readEoln();

    if (possible == 0) {
        stream.readEof();
        return {0};
    }

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; ++i) {
        dist[i][i] = 0;
    }

    validateWitness(stream, dist);
    stream.readEof();

    return {1};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    targetDist.assign(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            targetDist[i][j] = targetDist[j][i] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.possible == 1 && participant.possible == 0) {
        quitf(_wa, "participant reported impossible while jury has a valid graph");
    }
    if (jury.possible == 0 && participant.possible == 1) {
        quitf(_fail, "participant produced a valid graph while jury reported impossible");
    }

    quitf(_ok, "valid graph restoration claim");
}
