#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
 
int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    
    int n = inf.readInt();
    set<int> myset;
    for (int i = 0; i < n; i++) {
        myset.insert(inf.readInt());
    }
    
    string yes_ouf = ouf.readToken("YES|NO", "yesorno");
    string yes_ans = ans.readToken();
    if (yes_ans != yes_ouf) {
        quitf(_wa, "wa: yesno wrong");
    }
    
    auto is_prime = [](int x) -> bool {
        if (x == 1) {
            return false;
        }
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    };
    
    if (yes_ans == "YES") {
        int k = ouf.readInt(2, n, "k");
        vector<int> a = ouf.readInts(k, 1, 1'000, "num");
        sort(a.begin(), a.end());
        for (int i = 0; i < k - 1; i++) {
            if (a[i] == a[i + 1]) {
                quitf(_wa, "wa: duplicates");
            }
        }
        for (int i = 0; i < k; i++) {
            if (!myset.count(a[i])) {
                quitf(_wa, "wa: invalid integer");
            }
        }
        
        if (k == 2) {
            if (a[0] == 1 && is_prime(a[1])) {
                quitf(_wa, "wa: lcm prime");
            }
        }
    }
    
    ouf.seekEof();
    quitf(_ok, "ok");
}
