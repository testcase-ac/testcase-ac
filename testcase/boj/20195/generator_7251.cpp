#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // dimensions
    int r = rnd.next(3, 10);
    int s = rnd.next(3, 10);
    int N = r * s;

    // generate a random topological order of cells to avoid cycles
    vector<int> topo(N);
    iota(topo.begin(), topo.end(), 0);
    shuffle(topo.begin(), topo.end());
    vector<int> pos(N);
    for (int i = 0; i < N; i++)
        pos[topo[i]] = i;

    // choose positions for 'o' (interior) and 'x'
    vector<int> interior;
    for (int i = 1; i < r-1; i++)
        for (int j = 1; j < s-1; j++)
            interior.push_back(i * s + j);
    int oidx = rnd.any(interior);
    int xidx;
    do {
        xidx = rnd.next(0, N-1);
    } while (xidx == oidx);

    // choose current density hyper-parameter
    double pCurr;
    if (rnd.next(0,1) == 0)
        pCurr = rnd.next(10, 40) / 100.0;
    else
        pCurr = rnd.next(60, 90) / 100.0;

    // output
    println(r, s);
    for (int i = 0; i < r; i++) {
        string row;
        row.reserve(s);
        for (int j = 0; j < s; j++) {
            int idx = i * s + j;
            if (idx == oidx) {
                row.push_back('o');
            } else if (idx == xidx) {
                row.push_back('x');
            } else {
                // decide to place a current or calm
                if (rnd.next() < pCurr) {
                    vector<char> opts;
                    // '^' moves up
                    if (i > 0 && pos[(i-1)*s + j] > pos[idx]) opts.push_back('^');
                    // 'v' moves down
                    if (i+1 < r && pos[(i+1)*s + j] > pos[idx]) opts.push_back('v');
                    // '<' moves left
                    if (j > 0 && pos[i*s + (j-1)] > pos[idx]) opts.push_back('<');
                    // '>' moves right
                    if (j+1 < s && pos[i*s + (j+1)] > pos[idx]) opts.push_back('>');
                    if (!opts.empty()) {
                        row.push_back(rnd.any(opts));
                    } else {
                        row.push_back('.');
                    }
                } else {
                    row.push_back('.');
                }
            }
        }
        printf("%s\n", row.c_str());
    }
    return 0;
}
