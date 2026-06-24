#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
    long long w;
};

struct Answer {
    bool possible;
    vector<long long> x;
    __int128 cost;
};

int n, m;
vector<Edge> edges;

string lowerWord(string s) {
    for (char& ch : s) {
        ch = char(tolower((unsigned char)ch));
    }
    return s;
}

string toString(__int128 value) {
    if (value == 0) {
        return "0";
    }
    bool negative = value < 0;
    if (negative) {
        value = -value;
    }
    string result;
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    if (negative) {
        result.push_back('-');
    }
    reverse(result.begin(), result.end());
    return result;
}

Answer readAnswer(InStream& stream) {
    string decision = lowerWord(stream.readWord("[Yy][Ee][Ss]|[Nn][Oo]", "decision"));

    if (decision == "no") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after No");
        }
        return {false, {}, 0};
    }

    const long long xLimit = 1000000000000000LL;
    vector<long long> x(n + 1);
    __int128 cost = 0;
    for (int i = 1; i <= n; ++i) {
        x[i] = stream.readLong(-xLimit, xLimit, format("x[%d]", i).c_str());
        cost += x[i] < 0 ? -(__int128)x[i] : (__int128)x[i];
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after assignment");
    }

    for (int j = 0; j < m; ++j) {
        const Edge& edge = edges[j];
        if (x[edge.u] + x[edge.v] != edge.w) {
            stream.quitf(_wa,
                         "edge %d is not balanced: x[%d]+x[%d]=%lld, expected %lld",
                         j + 1,
                         edge.u,
                         edge.v,
                         x[edge.u] + x[edge.v],
                         edge.w);
        }
    }

    return {true, x, cost};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.reserve(m);
    for (int j = 0; j < m; ++j) {
        int u = inf.readInt();
        int v = inf.readInt();
        long long w = inf.readLong();
        edges.push_back({u, v, w});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible) {
        if (!participant.possible) {
            quitf(_ok, "both answers report impossible");
        }
        quitf(_fail, "participant found a valid assignment while jury reported impossible");
    }

    if (!participant.possible) {
        quitf(_wa, "participant reported impossible while jury has an assignment");
    }

    if (participant.cost < jury.cost) {
        quitf(_fail,
              "participant found lower cost than jury: participant=%s jury=%s",
              toString(participant.cost).c_str(),
              toString(jury.cost).c_str());
    }
    if (participant.cost > jury.cost) {
        quitf(_wa,
              "assignment is not minimum cost: participant=%s jury=%s",
              toString(participant.cost).c_str(),
              toString(jury.cost).c_str());
    }

    quitf(_ok, "minimum cost is %s", toString(jury.cost).c_str());
}
