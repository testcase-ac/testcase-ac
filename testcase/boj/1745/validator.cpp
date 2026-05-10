#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read F, P
    int F = inf.readInt(1, 200, "F");
    inf.readSpace();
    int P = inf.readInt(1, 1500, "P");
    inf.readEoln();

    // 2. Read F rooms: current students and capacity
    vector<int> cur(F), cap(F);
    for (int i = 0; i < F; ++i) {
        cur[i] = inf.readInt(0, 1000, "cur_i");
        inf.readSpace();
        cap[i] = inf.readInt(0, 1000, "cap_i");
        inf.readEoln();
    }

    // 3. Read P passages: a, b, t
    // According to the sample, multiple passages between the same pair of rooms ARE allowed.
    // Only self-loops are forbidden.
    vector<vector<pair<int,int>>> adj(F); // for connectivity check
    for (int i = 0; i < P; ++i) {
        int a = inf.readInt(1, F, "a");
        inf.readSpace();
        int b = inf.readInt(1, F, "b");
        inf.readSpace();
        int t = inf.readInt(0, 1000000000, "t");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at passage %d: (%d, %d)", i+1, a, b);

        // For connectivity check
        adj[a-1].emplace_back(b-1, t);
        adj[b-1].emplace_back(a-1, t);
    }

    // 4. Check that the graph is connected (since all students must be able to reach any room)
    // BFS from node 0
    vector<bool> vis(F, false);
    vector<int> q;
    q.push_back(0);
    vis[0] = true;
    for (size_t i = 0; i < q.size(); ++i) {
        int u = q[i];
        for (auto& e : adj[u]) {
            int v = e.first;
            if (!vis[v]) {
                vis[v] = true;
                q.push_back(v);
            }
        }
    }
    ensuref(count(vis.begin(), vis.end(), true) == F, "The passage graph is not connected");

    // 5. Check that the total number of students does not exceed total capacity
    long long total_students = 0, total_capacity = 0;
    for (int i = 0; i < F; ++i) {
        total_students += cur[i];
        total_capacity += cap[i];
    }
    ensuref(total_students <= total_capacity, "Total number of students (%lld) exceeds total capacity (%lld)", total_students, total_capacity);

    inf.readEof();
}
