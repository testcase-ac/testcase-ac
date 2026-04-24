#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of files
    int n = rnd.next(1, 10);

    // Generate unique random file names (1-5 lowercase letters)
    vector<string> names;
    set<string> used;
    while ((int)names.size() < n) {
        int len = rnd.next(1, 5);
        string s;
        for (int i = 0; i < len; i++) {
            char c = char('a' + rnd.next(0, 25));
            s.push_back(c);
        }
        if (used.insert(s).second) {
            names.push_back(s);
        }
    }

    // Adjacency sets for imports
    vector< set<int> > adj(n);

    // Hyper-parameter: whether to force a cycle
    double p_cycle = rnd.next();
    if (p_cycle < 0.5) {
        // Ensure at least one cycle
        if (n == 1) {
            adj[0].insert(0);
        } else {
            // Self-loop with some probability
            if (rnd.next() < 0.2) {
                int u = rnd.next(0, n-1);
                adj[u].insert(u);
            } else {
                // Cycle length between 2 and n
                int L = rnd.next(2, n);
                vector<int> ord(n);
                for (int i = 0; i < n; i++) ord[i] = i;
                shuffle(ord.begin(), ord.end());
                vector<int> cycle(ord.begin(), ord.begin() + L);
                for (int i = 0; i < L-1; i++) {
                    adj[cycle[i]].insert(cycle[i+1]);
                }
                adj[cycle[L-1]].insert(cycle[0]);
            }
        }
    }
    // Hyper-parameter: extra edge density
    double p_extra = rnd.next();
    // Add extra random imports
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && !adj[i].count(j)) {
                if (rnd.next() < p_extra) {
                    adj[i].insert(j);
                }
            }
        }
    }

    // Output
    println(n);
    println(names);

    // For each file, print its import section
    for (int i = 0; i < n; i++) {
        vector<int> deps(adj[i].begin(), adj[i].end());
        shuffle(deps.begin(), deps.end());
        int k_lines = (deps.empty() ? 0 : rnd.next(1, (int)deps.size()));
        println(names[i], k_lines);
        if (k_lines > 0) {
            // Distribute dependencies into k_lines groups
            vector<vector<int>> groups(k_lines);
            for (int j = 0; j < k_lines; j++) {
                groups[j].push_back(deps[j]);
            }
            for (int j = k_lines; j < (int)deps.size(); j++) {
                int idx = rnd.next(0, k_lines - 1);
                groups[idx].push_back(deps[j]);
            }
            // Shuffle the import lines
            shuffle(groups.begin(), groups.end());
            // Print each import line
            for (auto &grp : groups) {
                string line = "import ";
                for (int j = 0; j < (int)grp.size(); j++) {
                    if (j) line += ", ";
                    line += names[grp[j]];
                }
                printf("%s\n", line.c_str());
            }
        }
    }

    return 0;
}
