#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long double readDecimal(long double low, long double high, const string& name) {
    string token = inf.readToken("[0-9]{1,64}|[0-9]{1,64}\\.[0-9]{1,64}", name);

    size_t dot = token.find('.');
    string integerPart = dot == string::npos ? token : token.substr(0, dot);
    ensuref(integerPart == "0" || integerPart[0] != '0',
            "%s has a non-canonical integer part: %s",
            name.c_str(),
            token.c_str());

    long double value = stold(token);
    ensuref(low <= value && value <= high,
            "%s is out of range: %s",
            name.c_str(),
            token.c_str());
    return value;
}

void dfs(int node, const vector<vector<int>>& graph, vector<char>& seen) {
    seen[node] = 1;
    for (int next : graph[node]) {
        if (!seen[next]) {
            dfs(next, graph, seen);
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 25000, "M");
    inf.readSpace();
    readDecimal(1.0L, 1000000000000.0L, "V");
    inf.readSpace();
    int a = inf.readInt(1, n, "A");
    inf.readSpace();
    int b = inf.readInt(1, n, "B");
    inf.readEoln();

    ensuref(a != b, "A and B must be distinct, got %d", a);

    vector<vector<int>> graph(n + 1), reverseGraph(n + 1);
    for (int edge = 1; edge <= m; ++edge) {
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int j = inf.readInt(1, n, "j");
        inf.readSpace();
        long double rate = readDecimal(0.0L, 10.0L, "e_ij");
        inf.readEoln();

        ensuref(rate > 0.1L, "exchange rate at edge %d must be greater than 0.1", edge);
        graph[i].push_back(j);
        reverseGraph[j].push_back(i);
    }

    vector<char> seen(n + 1, 0);
    dfs(1, graph, seen);
    for (int node = 1; node <= n; ++node) {
        ensuref(seen[node], "country %d is not reachable from country 1", node);
    }

    fill(seen.begin(), seen.end(), 0);
    dfs(1, reverseGraph, seen);
    for (int node = 1; node <= n; ++node) {
        ensuref(seen[node], "country 1 is not reachable from country %d", node);
    }

    inf.readEof();
}
