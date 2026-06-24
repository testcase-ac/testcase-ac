#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using i128 = __int128_t;

struct Edge {
    int to;
    int weight;
};

struct Answer {
    int eVertex;
    int wVertex;
    i128 claimed;
    i128 actual;
};

int n, m;
vector<vector<Edge>> eTree;
vector<vector<Edge>> wTree;

i128 readNonNegativeInteger(InStream& stream, const char* name) {
    string token = stream.readWord();
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name);
    }
    if (token.size() > 1 && token[0] == '+') {
        stream.quitf(_wa, "%s has an explicit plus sign", name);
    }
    i128 value = 0;
    for (char ch : token) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            stream.quitf(_wa, "%s is not a non-negative integer: %s", name, token.c_str());
        }
        value = value * 10 + (ch - '0');
    }
    return value;
}

string toString(i128 value) {
    if (value == 0) {
        return "0";
    }

    string result;
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

i128 distanceSumFrom(const vector<vector<Edge>>& tree, int start) {
    vector<int> parent(tree.size(), 0);
    vector<i128> distance(tree.size(), 0);
    vector<int> stack = {start};
    parent[start] = -1;

    for (size_t i = 0; i < stack.size(); ++i) {
        int v = stack[i];
        for (const Edge& edge : tree[v]) {
            if (edge.to == parent[v]) {
                continue;
            }
            parent[edge.to] = v;
            distance[edge.to] = distance[v] + edge.weight;
            stack.push_back(edge.to);
        }
    }

    i128 sum = 0;
    for (size_t v = 1; v < distance.size(); ++v) {
        sum += distance[v];
    }
    return sum;
}

Answer readAnswer(InStream& stream) {
    int eVertex = stream.readInt(1, n, "E vertex");
    int wVertex = stream.readInt(1, m, "W vertex");
    stream.readEoln();

    i128 claimed = readNonNegativeInteger(stream, "distance sum");
    stream.readEoln();
    stream.readEof();

    i128 eSum = distanceSumFrom(eTree, eVertex);
    i128 wSum = distanceSumFrom(wTree, wVertex);
    i128 actual = eSum * m + wSum * n + i128(n) * m;
    if (claimed != actual) {
        stream.quitf(_wa,
                     "claimed distance sum %s does not match vertices (%d, %d), expected %s",
                     toString(claimed).c_str(),
                     eVertex,
                     wVertex,
                     toString(actual).c_str());
    }

    return {eVertex, wVertex, claimed, actual};
}

void readTree(vector<vector<Edge>>& tree, int vertexCount) {
    tree.assign(vertexCount + 1, {});
    for (int i = 0; i < vertexCount - 1; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        int c = inf.readInt();
        tree[a].push_back({b, c});
        tree[b].push_back({a, c});
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    readTree(eTree, n);
    m = inf.readInt();
    readTree(wTree, m);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.actual < jury.actual) {
        quitf(_fail,
              "participant found better answer: jury=%s participant=%s",
              toString(jury.actual).c_str(),
              toString(participant.actual).c_str());
    }
    if (participant.actual > jury.actual) {
        quitf(_wa,
              "jury has better answer: jury=%s participant=%s",
              toString(jury.actual).c_str(),
              toString(participant.actual).c_str());
    }

    quitf(_ok, "answer=%s", toString(participant.actual).c_str());
}
