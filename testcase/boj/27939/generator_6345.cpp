#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of varieties
    int n = rnd.next(2, 18);
    // generate colors with diverse distributions
    vector<char> colors(n);
    double mode = rnd.next();
    for (int i = 0; i < n; i++) {
        if (mode < 0.5) {
            colors[i] = rnd.next(0,1) ? 'W' : 'P';
        } else if (mode < 0.75) {
            colors[i] = (rnd.next() < 0.7) ? 'W' : 'P';
        } else {
            colors[i] = (rnd.next() < 0.7) ? 'P' : 'W';
        }
    }
    int cntW = 0;
    for (char c : colors) if (c == 'W') cntW++;
    // each assistant gets k varieties
    int k = rnd.next(2, n);
    // number of assistants
    int m = rnd.next(2, min(8, n));
    // decide if there is at least one all-W assistant
    bool existGood = false;
    if (cntW >= k && rnd.next(0,1) == 1) {
        existGood = true;
    }
    int goodIdx = existGood ? rnd.next(0, m-1) : -1;
    // prepare positions
    vector<int> all(n);
    for (int i = 0; i < n; i++) all[i] = i+1;
    vector<int> wpos, ppos;
    for (int i = 0; i < n; i++) {
        if (colors[i] == 'W') wpos.push_back(i+1);
        else ppos.push_back(i+1);
    }
    vector<vector<int>> a(m);
    for (int i = 0; i < m; i++) {
        if (i == goodIdx) {
            // pick k from W positions
            shuffle(wpos.begin(), wpos.end());
            a[i].assign(wpos.begin(), wpos.begin() + k);
        } else {
            // random subset of size k
            shuffle(all.begin(), all.end());
            a[i].assign(all.begin(), all.begin() + k);
            if (!existGood) {
                // avoid accidentally all-W
                bool allW = true;
                for (int x : a[i]) if (colors[x-1] == 'P') { allW = false; break; }
                if (allW && !ppos.empty()) {
                    // replace one element by a P outside if possible
                    vector<int> outsideP;
                    vector<bool> inSet(n+1, false);
                    for (int x : a[i]) inSet[x] = true;
                    for (int x : ppos) if (!inSet[x]) outsideP.push_back(x);
                    int pos = rnd.next(0, k-1);
                    if (!outsideP.empty()) {
                        a[i][pos] = outsideP[rnd.next(0, (int)outsideP.size()-1)];
                    } else {
                        // no outside P, ensure a P inside
                        a[i][pos] = ppos[rnd.next(0, (int)ppos.size()-1)];
                    }
                }
            }
        }
    }
    // output
    println(n);
    println(colors);
    println(m, k);
    for (int i = 0; i < m; i++) {
        println(a[i]);
    }
    return 0;
}
