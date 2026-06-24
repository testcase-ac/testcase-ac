#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
vector<long long> x, len;
vector<string> color;

struct Answer {
    bool hasWitness;
    int first;
    int second;
};

Answer readAnswer(InStream& stream) {
    string verdict = stream.readToken("YES|NO", "verdict");

    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false, -1, -1};
    }

    int a = stream.readInt(1, n, "first ribbon index");
    int b = stream.readInt(1, n, "second ribbon index");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after witness");
    }

    if (a == b) {
        stream.quitf(_wa, "ribbon indices must be distinct: both are %d", a);
    }

    int u = a - 1;
    int v = b - 1;
    if (color[u] == color[v]) {
        stream.quitf(_wa, "ribbons %d and %d have the same color %s", a, b, color[u].c_str());
    }

    long long distance = x[u] > x[v] ? x[u] - x[v] : x[v] - x[u];
    if (distance > len[u] + len[v]) {
        stream.quitf(_wa,
                     "ribbons %d and %d cannot be tied: distance=%lld, total length=%lld",
                     a,
                     b,
                     distance,
                     len[u] + len[v]);
    }

    return {true, a, b};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();

    x.resize(n);
    len.resize(n);
    color.resize(n);

    for (int i = 0; i < n; ++i) {
        x[i] = inf.readLong();
    }
    for (int i = 0; i < n; ++i) {
        len[i] = inf.readLong();
    }
    for (int i = 0; i < n; ++i) {
        color[i] = inf.readToken("R|Y|B", format("C[%d]", i + 1).c_str());
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.hasWitness) {
        if (!participant.hasWitness) {
            quitf(_wa, "jury found a valid pair, but participant answered NO");
        }
        quitf(_ok,
              "valid pair: %d %d",
              participant.first,
              participant.second);
    }

    if (participant.hasWitness) {
        quitf(_fail,
              "participant found a valid pair %d %d while jury answered NO",
              participant.first,
              participant.second);
    }

    quitf(_ok, "both outputs report NO");
}
