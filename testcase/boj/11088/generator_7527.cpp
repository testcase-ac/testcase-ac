#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Total characters
    int N = rnd.next(4, 12);
    // Number of components (disconnected conversation groups)
    int compCount = rnd.next(2, min(4, N));
    // Distribute sizes
    vector<int> compSizes(compCount, 1);
    int rem = N - compCount;
    for (int i = 0; i < rem; i++) {
        compSizes[rnd.next(0, compCount - 1)]++;
    }
    // Prepare storage
    vector<string> names;
    vector<string> speaks;
    vector<vector<string>> understands;
    int globalIdx = 1;
    // For each component
    for (int ci = 0; ci < compCount; ci++) {
        int sz = compSizes[ci];
        // Local languages for this component
        int maxLangs = min(sz, 4);
        int localLangCount = rnd.next(1, maxLangs);
        vector<string> localLangs;
        for (int j = 0; j < localLangCount; j++) {
            localLangs.push_back(string("L") + to_string(ci+1) + "-" + to_string(j+1));
        }
        // Assign characters
        vector<int> compIds;
        for (int k = 0; k < sz; k++) {
            names.push_back(string("C") + to_string(globalIdx));
            // speak one of localLangs
            speaks.push_back(rnd.any(localLangs));
            understands.emplace_back();
            compIds.push_back(globalIdx-1);
            globalIdx++;
        }
        // Build a spanning chain to ensure strong connectivity
        if (sz >= 2) {
            vector<int> order(sz);
            for (int i = 0; i < sz; i++) order[i] = i;
            shuffle(order.begin(), order.end());
            for (int t = 1; t < sz; t++) {
                int u = order[t-1], v = order[t];
                // u speaks speaks[u], ensure v understands it
                understands[compIds[v]].push_back(speaks[compIds[u]]);
                // v speaks speaks[v], ensure u understands it
                understands[compIds[u]].push_back(speaks[compIds[v]]);
            }
        }
        // Add random extra understands within component
        for (int k = 0; k < sz; k++) {
            int idx = compIds[k];
            for (auto &lang : localLangs) {
                if (lang == speaks[idx]) continue;
                if (rnd.next(0,1) == 1) {
                    understands[idx].push_back(lang);
                }
            }
        }
    }
    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        vector<string> fields;
        fields.push_back(names[i]);
        fields.push_back(speaks[i]);
        // Remove duplicates in understands[i]
        sort(understands[i].begin(), understands[i].end());
        understands[i].erase(unique(understands[i].begin(), understands[i].end()), understands[i].end());
        for (auto &u : understands[i]) fields.push_back(u);
        println(fields);
    }
    return 0;
}
