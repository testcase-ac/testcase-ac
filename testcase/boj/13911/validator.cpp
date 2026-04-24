#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read V, E
    int V = inf.readInt(3, 10000, "V");
    inf.readSpace();
    int E = inf.readInt(0, 300000, "E");
    inf.readEoln();

    // 2. Read E edges
    // - u, v: 1..V, u != v
    // - w: 1..9999
    // - Multiple edges allowed
    // - Self-loops not allowed
    // We'll store edges for later connectivity check
    vector<vector<pair<int,int>>> adj(V+1); // 1-based

    for (int i = 0; i < E; ++i) {
        int u = inf.readInt(1, V, "u");
        inf.readSpace();
        int v = inf.readInt(1, V, "v");
        inf.readSpace();
        int w = inf.readInt(1, 9999, "w");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);

        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // 3. Read M, x
    int M = inf.readInt(1, V-2, "M");
    inf.readSpace();
    int x = inf.readInt(1, 100000000, "x");
    inf.readEoln();

    // 4. Read M macdonald vertices
    vector<int> macdonalds = inf.readInts(M, 1, V, "macdonalds");
    inf.readEoln();

    // 5. Read S, y
    int S = inf.readInt(1, V-2, "S");
    inf.readSpace();
    int y = inf.readInt(1, 100000000, "y");
    inf.readEoln();

    // 6. Read S starbucks vertices
    vector<int> starbucks = inf.readInts(S, 1, V, "starbucks");
    inf.readEoln();

    // 7. Validate that all macdonalds and starbucks are unique (within each group)
    {
        set<int> mac_set(macdonalds.begin(), macdonalds.end());
        ensuref((int)mac_set.size() == M, "Duplicate macdonald vertex detected");
        set<int> star_set(starbucks.begin(), starbucks.end());
        ensuref((int)star_set.size() == S, "Duplicate starbucks vertex detected");
    }

    // 8. Validate that all macdonalds and starbucks are in 1..V
    for (int i = 0; i < M; ++i) {
        ensuref(1 <= macdonalds[i] && macdonalds[i] <= V, "macdonalds[%d]=%d out of range", i, macdonalds[i]);
    }
    for (int i = 0; i < S; ++i) {
        ensuref(1 <= starbucks[i] && starbucks[i] <= V, "starbucks[%d]=%d out of range", i, starbucks[i]);
    }

    // 9. Validate that there is at least one house (vertex not in macdonalds nor starbucks)
    //    (집이 있는(= 맥도날드나 스타벅스가 위치하지 않은) 정점이 하나 이상 존재한다.)
    set<int> mac_set(macdonalds.begin(), macdonalds.end());
    set<int> star_set(starbucks.begin(), starbucks.end());
    int house_count = 0;
    for (int v = 1; v <= V; ++v) {
        if (mac_set.count(v) == 0 && star_set.count(v) == 0) {
            ++house_count;
        }
    }
    ensuref(house_count >= 1, "There must be at least one house vertex (not macdonald/starbucks)");

    // 10. Validate that M, S <= V-2 (already checked by readInt), and that macdonalds and starbucks can overlap
    //     (한 정점에 맥도날드와 스타벅스가 같이 위치할 수 있다.)

    // 11. (Optional) Validate that the graph is not disconnected in a way that makes some house unreachable from all macdonald/starbucks
    //     But the statement does NOT guarantee connectivity, so we do NOT check for connectivity.

    // 12. (Optional) Validate that all edges are valid (already checked by readInt and u != v)

    // 13. (Optional) Validate that the number of test cases is 1 (since no T is given, only one case per file)

    inf.readEof();
}
