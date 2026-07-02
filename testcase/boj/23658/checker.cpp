#include "testlib.h"

#include <queue>
#include <string>
#include <vector>

using namespace std;

int n;

struct Answer {
    int length;
};

string pointToString(int value) {
    string s(n, '0');
    for (int i = n - 1; i >= 0; --i) {
        s[n - 1 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    return s;
}

int readPoint(InStream& stream, const char* name) {
    string s = stream.readToken(format("[01]{%d}", n), name);
    int value = 0;
    for (char c : s) {
        value = value * 2 + (c - '0');
    }
    return value;
}

Answer readAnswer(InStream& stream) {
    int maxVertices = 1 << n;
    int length = stream.readInt(1, maxVertices, "L");
    stream.readEoln();

    vector<int> path(length);
    vector<int> inPath(maxVertices, 0);
    for (int i = 0; i < length; ++i) {
        path[i] = readPoint(stream, format("x[%d]", i + 1).c_str());
        stream.readEoln();
        if (inPath[path[i]]) {
            stream.quitf(_wa, "point %s appears more than once", pointToString(path[i]).c_str());
        }
        inPath[path[i]] = 1;
    }
    stream.readEof();

    for (int i = 0; i + 1 < length; ++i) {
        if (__builtin_popcount((unsigned)(path[i] ^ path[i + 1])) != 1) {
            stream.quitf(_wa, "consecutive points %d and %d differ in more than one coordinate", i + 1, i + 2);
        }
    }

    vector<int> dist(maxVertices, -1);
    queue<int> q;
    dist[path.front()] = 0;
    q.push(path.front());
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int bit = 0; bit < n; ++bit) {
            int to = v ^ (1 << bit);
            if (!inPath[to] || dist[to] != -1) {
                continue;
            }
            dist[to] = dist[v] + 1;
            q.push(to);
        }
    }

    if (dist[path.back()] != length - 1) {
        stream.quitf(_wa, "path is imperfect: shortest subset path has length %d vertices, output has %d vertices",
                     dist[path.back()] + 1, length);
    }

    return {length};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 6, "n");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.length < jury.length) {
        quitf(_wa, "jury path is longer: jury=%d participant=%d", jury.length, participant.length);
    }
    if (participant.length > jury.length) {
        quitf(_fail, "participant found longer perfect path: jury=%d participant=%d", jury.length, participant.length);
    }
    quitf(_ok, "path length %d", participant.length);
}
