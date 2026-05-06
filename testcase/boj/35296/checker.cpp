#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    
    int n = inf.readInt();
    int m = inf.readInt();
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = inf.readToken();
    }
    
    int k_ouf = ouf.readInt(1, n * m, "k");
    int k_ans = ans.readInt();
 
    if (k_ouf > k_ans) {
        quitf(_wa, "better k exists");
    }
    
    for (int i = 0; i < k_ouf; i++) {
        int t = ouf.readInt(1, 2, "type");
        vector<int> p = ouf.readInts(t, 1, n * m, "list");
        if (t == 2) {
            if (abs(p[1] - p[0]) != 1) {
                quitf(_wa, "not adjacent no.");
            }
            if (n != 1 && (min(p[0], p[1]) - 1) % n == n - 1) {
                quitf(_wa, "not adjacent cell");
            }
        }
        for (int x : p) {
            int c = (x - 1) / n;
            int r = (x - 1) % n;
            if (a[r][c] == 'O') {
                quitf(_wa, "already done");
            }
            a[r][c] = 'O';
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (find(a[i].begin(), a[i].end(), 'X') != a[i].end()) {
            quitf(_wa, "not done");
        }
    }
    
    ouf.seekEof();
    if (k_ouf < k_ans) {
        quitf(_fail, "participant answer better");
    }
    quitf(_ok, "ok");
    return 0;
}
