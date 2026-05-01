#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int DIFF_MAX = 10;

    // Initial number of problems
    int N = rnd.next(1, 7);
    int maxGroup = rnd.next(2, 5); // use a few groups for readability

    vector<int> activeList;              // currently active problem IDs
    unordered_map<int, int> probGroup;   // P -> G for active problems
    map<int, int> groupCount;            // G -> count of active problems in this group
    vector<int> inactivePool;            // solved problems that can be re-added

    activeList.reserve(100);
    inactivePool.reserve(100);

    // Output initial problems
    println(N);
    for (int i = 1; i <= N; i++) {
        int P = i;
        int L = rnd.next(1, DIFF_MAX);
        int G = rnd.next(1, maxGroup);
        println(P, L, G);

        activeList.push_back(P);
        probGroup[P] = G;
        groupCount[G]++;
    }

    int nextP = N + 1;

    // Number of commands
    int M = rnd.next(8, 20);
    println(M);

    // Choose 3 distinct positions for mandatory recommend, recommend2, recommend3
    vector<int> positions(M);
    for (int i = 0; i < M; i++) positions[i] = i;
    shuffle(positions.begin(), positions.end());
    int recIdx1 = positions[0];
    int recIdx2 = positions[1];
    int recIdx3 = positions[2];

    int lastMandatoryIdx = max(recIdx1, max(recIdx2, recIdx3));

    enum CmdType { CMD_ADD, CMD_SOLVED, CMD_REC1, CMD_REC2, CMD_REC3 };

    for (int i = 0; i < M; i++) {
        // Mandatory recommend (type 1)
        if (i == recIdx1) {
            // There must be at least one active problem, by construction
            vector<int> groups;
            for (auto &kv : groupCount)
                if (kv.second > 0) groups.push_back(kv.first);

            // groups must be non-empty since activeList is non-empty
            if (groups.empty()) {
                // Fallback: if something went wrong, force an add to keep validity
                int P;
                if (!inactivePool.empty() && rnd.next(0, 1) == 0) {
                    int idx = rnd.next(0, (int)inactivePool.size() - 1);
                    P = inactivePool[idx];
                    inactivePool[idx] = inactivePool.back();
                    inactivePool.pop_back();
                } else {
                    P = nextP++;
                }
                int L = rnd.next(1, DIFF_MAX);
                int G = rnd.next(1, maxGroup);
                println("add", P, L, G);
                activeList.push_back(P);
                probGroup[P] = G;
                groupCount[G]++;
            } else {
                int G = rnd.any(groups);
                int x = rnd.next(0, 1) ? 1 : -1;
                println("recommend", G, x);
            }
            continue;
        }

        // Mandatory recommend2
        if (i == recIdx2) {
            int x = rnd.next(0, 1) ? 1 : -1;
            println("recommend2", x);
            continue;
        }

        // Mandatory recommend3
        if (i == recIdx3) {
            int x = rnd.next(0, 1) ? 1 : -1;
            int L = rnd.next(1, 15); // some thresholds above all existing difficulties to trigger -1 cases
            println("recommend3", x, L);
            continue;
        }

        // General command generation
        if (activeList.empty()) {
            // Only "add" is allowed when list is empty
            int P;
            if (!inactivePool.empty() && rnd.next(0, 1) == 0) {
                int idx = rnd.next(0, (int)inactivePool.size() - 1);
                P = inactivePool[idx];
                inactivePool[idx] = inactivePool.back();
                inactivePool.pop_back();
            } else {
                P = nextP++;
            }
            int L = rnd.next(1, DIFF_MAX);
            int G = rnd.next(1, maxGroup);
            println("add", P, L, G);
            activeList.push_back(P);
            probGroup[P] = G;
            groupCount[G]++;
            continue;
        }

        // Build list of allowed command types when list is non-empty
        vector<int> allowed;
        allowed.push_back(CMD_ADD); // always allowed

        // Avoid emptying the list before all mandatory recommends
        if ((int)activeList.size() > 1 || i > lastMandatoryIdx)
            allowed.push_back(CMD_SOLVED);

        allowed.push_back(CMD_REC1);
        allowed.push_back(CMD_REC2);
        allowed.push_back(CMD_REC3);

        int cmd = rnd.any(allowed);

        if (cmd == CMD_ADD) {
            int P;
            // Sometimes re-add a previously solved problem to change its L/G
            if (!inactivePool.empty() && rnd.next(0, 1) == 0) {
                int idx = rnd.next(0, (int)inactivePool.size() - 1);
                P = inactivePool[idx];
                inactivePool[idx] = inactivePool.back();
                inactivePool.pop_back();
            } else {
                P = nextP++;
            }
            int L = rnd.next(1, DIFF_MAX);
            int G = rnd.next(1, maxGroup);
            println("add", P, L, G);

            activeList.push_back(P);
            probGroup[P] = G;
            groupCount[G]++;
        } else if (cmd == CMD_SOLVED) {
            // Solve a random active problem
            int idx = rnd.next(0, (int)activeList.size() - 1);
            int P = activeList[idx];
            println("solved", P);

            int G = probGroup[P];
            groupCount[G]--;
            probGroup.erase(P);

            inactivePool.push_back(P);

            activeList[idx] = activeList.back();
            activeList.pop_back();
        } else if (cmd == CMD_REC1) {
            vector<int> groups;
            for (auto &kv : groupCount)
                if (kv.second > 0) groups.push_back(kv.first);

            if (groups.empty()) {
                // Should not happen, but keep input valid: fall back to recommend2
                int x = rnd.next(0, 1) ? 1 : -1;
                println("recommend2", x);
            } else {
                int G = rnd.any(groups);
                int x = rnd.next(0, 1) ? 1 : -1;
                println("recommend", G, x);
            }
        } else if (cmd == CMD_REC2) {
            int x = rnd.next(0, 1) ? 1 : -1;
            println("recommend2", x);
        } else { // CMD_REC3
            int x = rnd.next(0, 1) ? 1 : -1;
            int L = rnd.next(1, 15);
            println("recommend3", x, L);
        }
    }

    return 0;
}
