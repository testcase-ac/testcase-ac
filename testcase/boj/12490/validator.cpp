#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int p = inf.readInt(2, 400, "P");
        inf.readSpace();
        int maxW = min(2000, p * (p - 1) / 2);
        int w = inf.readInt(1, maxW, "W");
        inf.readEoln();

        vector<vector<int>> graph(p);
        set<pair<int, int>> edges;
        for (int i = 0; i < w; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            string edge = inf.readToken("[0-9]{1,3},[0-9]{1,3}", "edge_i");
            size_t comma = edge.find(',');
            string xs = edge.substr(0, comma);
            string ys = edge.substr(comma + 1);
            ensuref(xs == "0" || xs[0] != '0', "edge %d has leading zero in x: %s", i + 1, edge.c_str());
            ensuref(ys == "0" || ys[0] != '0', "edge %d has leading zero in y: %s", i + 1, edge.c_str());

            int x = atoi(xs.c_str());
            int y = atoi(ys.c_str());
            ensuref(0 <= x && x < p, "edge %d has x out of range: %d", i + 1, x);
            ensuref(0 <= y && y < p, "edge %d has y out of range: %d", i + 1, y);

            ensuref(x < y, "edge %d has x >= y: %d,%d", i + 1, x, y);
            ensuref(edges.insert({x, y}).second, "duplicate edge %d: %d,%d", i + 1, x, y);

            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        inf.readEoln();

        vector<int> stack = {0};
        vector<bool> seen(p, false);
        seen[0] = true;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            for (int to : graph[v]) {
                if (!seen[to]) {
                    seen[to] = true;
                    stack.push_back(to);
                }
            }
        }
        ensuref(seen[1], "planet 1 is not reachable from planet 0");
    }

    inf.readEof();
}
