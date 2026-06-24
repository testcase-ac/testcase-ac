#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct Answer {
    string bits;
    int flips;
};

int n;
vector<Edge> edges;

Answer readAnswer(InStream& stream) {
    string bits = stream.readToken("[01]+", "flip bits");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after flip bitstring");
    }

    int m = n - 1;
    if ((int)bits.size() != m) {
        stream.quitf(_wa, "flip bitstring length is %d, expected %d", (int)bits.size(), m);
    }

    vector<int> indegree(n + 1, 0);
    int flips = 0;
    for (int i = 0; i < m; ++i) {
        int from = edges[i].from;
        int to = edges[i].to;
        if (bits[i] == '1') {
            ++flips;
            swap(from, to);
        }
        ++indegree[to];
    }

    int roots = 0;
    for (int v = 1; v <= n; ++v) {
        if (indegree[v] == 0) {
            ++roots;
        } else if (indegree[v] != 1) {
            stream.quitf(_wa, "vertex %d has indegree %d, expected 0 or 1", v, indegree[v]);
        }
    }
    if (roots != 1) {
        stream.quitf(_wa, "orientation has %d possible roots, expected 1", roots);
    }

    return {bits, flips};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    edges.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        edges[i].from = inf.readInt();
        edges[i].to = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.flips < jury.flips) {
        quitf(_fail,
              "participant found better answer: jury flips=%d, participant flips=%d",
              jury.flips,
              participant.flips);
    }
    if (participant.flips > jury.flips) {
        quitf(_wa,
              "jury has better answer: jury flips=%d, participant flips=%d",
              jury.flips,
              participant.flips);
    }

    quitf(_ok, "optimal flip count is %d", participant.flips);
}
