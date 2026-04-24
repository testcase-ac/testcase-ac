#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Small number of students
        int n = rnd.next(2, 10);
        bool includeChains = rnd.next(0, 1);
        // Decide how many cycles
        int maxCycleCount = includeChains ? min(3, n-1) : min(3, n);
        int cycleCount = rnd.next(1, maxCycleCount);
        // Decide total nodes in cycles
        int totalCycleNodes;
        if (includeChains) {
            totalCycleNodes = rnd.next(cycleCount, n-1);
        } else {
            totalCycleNodes = n;
        }
        // Split totalCycleNodes into cycleCount positive parts
        vector<int> cycleLens(cycleCount);
        int rem = totalCycleNodes;
        for (int i = 0; i < cycleCount; i++) {
            if (i + 1 == cycleCount) {
                cycleLens[i] = rem;
            } else {
                int maxL = rem - (cycleCount - i - 1);
                cycleLens[i] = rnd.next(1, maxL);
                rem -= cycleLens[i];
            }
        }
        // Prepare node labels and shuffle
        vector<int> nodes(n);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        // Build the selection array
        vector<int> sel(n+1);
        vector<bool> inCycle(n+1, false);
        vector<int> processed;
        int pos = 0;
        // Create the cycles
        for (int i = 0; i < cycleCount; i++) {
            int len = cycleLens[i];
            vector<int> cyc(nodes.begin() + pos, nodes.begin() + pos + len);
            pos += len;
            for (int j = 0; j < len; j++) {
                int u = cyc[j];
                int v = cyc[(j+1) % len];
                sel[u] = v;
                inCycle[u] = true;
                processed.push_back(u);
            }
        }
        // Create chains pointing into the cycles or earlier chains
        for (int i = pos; i < n; i++) {
            int u = nodes[i];
            int p = rnd.any(processed);
            sel[u] = p;
            processed.push_back(u);
        }
        // Output this test case
        println(n);
        vector<int> out(n);
        for (int i = 1; i <= n; i++) out[i-1] = sel[i];
        println(out);
    }
    return 0;
}
