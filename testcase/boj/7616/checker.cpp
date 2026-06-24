#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct TestCase {
    int k;
    int n;
    vector<set<int>> adj;
};

struct Answer {
    bool impossible;
};

vector<TestCase> cases;

bool parseIntToken(const string& token, int& value) {
    if (token.empty()) {
        return false;
    }

    long long parsed = 0;
    for (char c : token) {
        if (c < '0' || c > '9') {
            return false;
        }
        parsed = parsed * 10 + (c - '0');
        if (parsed > 5000) {
            return false;
        }
    }

    value = static_cast<int>(parsed);
    return true;
}

vector<int> parsePathLine(InStream& stream, const string& line, int caseIndex, int pathIndex) {
    stringstream ss(line);
    vector<int> path;
    string token;
    while (ss >> token) {
        int vertex;
        if (!parseIntToken(token, vertex)) {
            stream.quitf(_wa, "case %d path %d: invalid vertex token '%s'",
                         caseIndex, pathIndex, token.c_str());
        }
        path.push_back(vertex);
    }
    if (path.empty()) {
        stream.quitf(_wa, "case %d path %d: empty path line", caseIndex, pathIndex);
    }
    return path;
}

Answer readAnswer(InStream& stream, int caseIndex) {
    const TestCase& tc = cases[caseIndex - 1];

    string caseWord = stream.readWord();
    if (caseWord != "Case") {
        stream.quitf(_wa, "case %d: expected 'Case', found '%s'", caseIndex, caseWord.c_str());
    }

    string label = stream.readWord();
    string expectedLabel = format("%d:", caseIndex);
    if (label != expectedLabel) {
        stream.quitf(_wa, "case %d: expected label '%s', found '%s'",
                     caseIndex, expectedLabel.c_str(), label.c_str());
    }
    string headerRest = stream.readLine();
    for (char c : headerRest) {
        if (!isspace((unsigned char)c)) {
            stream.quitf(_wa, "case %d: unexpected token after case header", caseIndex);
        }
    }

    string firstLine = stream.readLine();
    stringstream firstStream(firstLine);
    string firstToken;
    firstStream >> firstToken;
    if (firstToken.empty()) {
        stream.quitf(_wa, "case %d: missing answer line", caseIndex);
    }

    if (firstToken == "Impossible") {
        string extra;
        if (firstStream >> extra) {
            stream.quitf(_wa, "case %d: extra token after Impossible", caseIndex);
        }
        return {true};
    }

    vector<vector<int>> paths;
    paths.reserve(tc.k);
    paths.push_back(parsePathLine(stream, firstLine, caseIndex, 1));
    for (int i = 2; i <= tc.k; ++i) {
        paths.push_back(parsePathLine(stream, stream.readLine(), caseIndex, i));
    }

    vector<int> used(tc.n + 1, 0);
    for (int i = 0; i < tc.k; ++i) {
        const vector<int>& path = paths[i];
        if (path.front() != 1) {
            stream.quitf(_wa, "case %d path %d: starts at %d instead of 1",
                         caseIndex, i + 1, path.front());
        }
        if (path.back() != 2) {
            stream.quitf(_wa, "case %d path %d: ends at %d instead of 2",
                         caseIndex, i + 1, path.back());
        }

        vector<int> localUsed(tc.n + 1, 0);
        for (int j = 0; j < (int)path.size(); ++j) {
            int vertex = path[j];
            if (vertex < 1 || vertex > tc.n) {
                stream.quitf(_wa, "case %d path %d: vertex %d at position %d is outside 1..%d",
                             caseIndex, i + 1, vertex, j + 1, tc.n);
            }
            if (localUsed[vertex]) {
                stream.quitf(_wa, "case %d path %d: vertex %d appears more than once",
                             caseIndex, i + 1, vertex);
            }
            localUsed[vertex] = 1;

            if (vertex != 1 && vertex != 2) {
                if (used[vertex]) {
                    stream.quitf(_wa, "case %d: vertex %d appears in more than one path",
                                 caseIndex, vertex);
                }
                used[vertex] = 1;
            }
        }

        for (int j = 0; j + 1 < (int)path.size(); ++j) {
            int u = path[j];
            int v = path[j + 1];
            if (!tc.adj[u].count(v)) {
                stream.quitf(_wa, "case %d path %d: edge %d-%d is not in the graph",
                             caseIndex, i + 1, u, v);
            }
        }
    }

    return {false};
}

void readInput() {
    while (true) {
        int k = inf.readInt();
        int n = inf.readInt();
        inf.readEoln();
        if (k == 0 && n == 0) {
            break;
        }

        TestCase tc;
        tc.k = k;
        tc.n = n;
        tc.adj.assign(n + 1, {});

        for (int u = 1; u <= n; ++u) {
            string line = inf.readLine();
            stringstream ss(line);
            int v;
            while (ss >> v) {
                tc.adj[u].insert(v);
            }
        }

        cases.push_back(tc);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    readInput();

    for (int caseIndex = 1; caseIndex <= (int)cases.size(); ++caseIndex) {
        Answer jury = readAnswer(ans, caseIndex);
        Answer participant = readAnswer(ouf, caseIndex);

        if (jury.impossible && participant.impossible) {
            continue;
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "case %d: jury provides paths, but participant reports Impossible",
                  caseIndex);
        }
        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "case %d: participant provides valid paths while jury reports Impossible",
                  caseIndex);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answers");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answers");
    }

    quitf(_ok, "all %d case(s) match the jury baseline", (int)cases.size());
}
