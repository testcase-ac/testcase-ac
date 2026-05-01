#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of rooms
    int F = rnd.next(2, 10);
    // Build a random spanning tree to ensure connectivity
    vector<pair<int,int>> edges;
    for (int i = 2; i <= F; i++) {
        int j = rnd.next(1, i-1);
        edges.emplace_back(i, j);
    }
    // Collect all possible non-tree edges
    vector<pair<int,int>> candidates;
    vector<vector<bool>> used(F+1, vector<bool>(F+1, false));
    for (auto &e : edges) {
        used[e.first][e.second] = used[e.second][e.first] = true;
    }
    for (int i = 1; i <= F; i++) {
        for (int j = i+1; j <= F; j++) {
            if (!used[i][j]) candidates.emplace_back(i, j);
        }
    }
    // Add a random number of extra edges
    shuffle(candidates.begin(), candidates.end());
    int addExtra = rnd.next(0, (int)candidates.size());
    for (int i = 0; i < addExtra; i++) {
        edges.push_back(candidates[i]);
    }
    int P = edges.size();
    // Generate capacities
    vector<int> cap(F);
    long long sum_cap = 0;
    for (int i = 0; i < F; i++) {
        cap[i] = rnd.next(0, 10);
        sum_cap += cap[i];
    }
    // Total students <= total capacity to ensure feasibility
    long long total_students = rnd.next(0LL, sum_cap);
    // Distribute students arbitrarily
    vector<int> stud(F);
    long long rem = total_students;
    for (int i = 0; i < F; i++) {
        if (i < F-1) {
            stud[i] = rnd.next(0LL, rem);
            rem -= stud[i];
        } else {
            stud[i] = rem;
        }
    }
    shuffle(stud.begin(), stud.end());
    // Output
    println(F, P);
    for (int i = 0; i < F; i++) {
        println(stud[i], cap[i]);
    }
    for (auto &e : edges) {
        int w = rnd.next(1, 1000);
        println(e.first, e.second, w);
    }
    return 0;
}
