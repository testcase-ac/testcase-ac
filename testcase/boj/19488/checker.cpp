#include "testlib.h"

#include <bits/stdc++.h>

using namespace std;

int n, m, d;
vector<vector<int>> graph;

struct Answer {
    bool impossible;
    int size;
};

int parseSizeToken(InStream& stream, const string& token) {
    if (token.empty()) {
        stream.quitf(_wa, "empty size token");
    }
    for (char ch : token) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            stream.quitf(_wa, "size token is neither NIE nor an integer: %s", token.c_str());
        }
    }

    long long value = 0;
    for (char ch : token) {
        value = value * 10 + (ch - '0');
        if (value > n) {
            stream.quitf(_wa, "claimed set size %lld exceeds n=%d", value, n);
        }
    }
    if (value < 1) {
        stream.quitf(_wa, "claimed set size must be positive, found %lld", value);
    }
    return static_cast<int>(value);
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken("[A-Za-z0-9]+", "first output token");
    if (first == "NIE") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NIE");
        }
        return {true, 0};
    }

    int k = parseSizeToken(stream, first);
    vector<int> vertices(k);
    vector<char> inSet(n + 1, false);

    int previous = 0;
    for (int i = 0; i < k; ++i) {
        vertices[i] = stream.readInt(1, n, format("city[%d]", i + 1).c_str());
        if (vertices[i] <= previous) {
            stream.quitf(_wa,
                         "cities must be listed in strictly ascending order, found %d after %d",
                         vertices[i],
                         previous);
        }
        previous = vertices[i];
        inSet[vertices[i]] = true;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after city list");
    }

    vector<int> degree(n + 1, 0);
    for (int u : vertices) {
        for (int v : graph[u]) {
            if (inSet[v]) {
                ++degree[u];
            }
        }
        if (degree[u] < d) {
            stream.quitf(_wa,
                         "city %d has only %d direct connections inside the set, expected at least %d",
                         u,
                         degree[u],
                         d);
        }
    }

    vector<char> seen(n + 1, false);
    queue<int> q;
    q.push(vertices[0]);
    seen[vertices[0]] = true;
    int reached = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ++reached;
        for (int v : graph[u]) {
            if (inSet[v] && !seen[v]) {
                seen[v] = true;
                q.push(v);
            }
        }
    }
    if (reached != k) {
        stream.quitf(_wa, "the chosen set is not connected: reached %d of %d cities", reached, k);
    }

    return {false, k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    d = inf.readInt();
    graph.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim no well connected set exists");
        }
        quitf(_fail,
              "jury claims no solution, but participant provided a valid set of size %d",
              participant.size);
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid set of size %d, but participant printed NIE", jury.size);
    }
    if (participant.size < jury.size) {
        quitf(_wa,
              "participant set is smaller than jury set: participant=%d jury=%d",
              participant.size,
              jury.size);
    }
    if (participant.size > jury.size) {
        quitf(_fail,
              "participant found a larger valid set: participant=%d jury=%d",
              participant.size,
              jury.size);
    }
    quitf(_ok, "valid well connected set of size %d", participant.size);
}
