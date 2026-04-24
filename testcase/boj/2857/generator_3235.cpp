#include "testlib.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int n = 5;
    // Weight parameter: negative => favor few FBIs, positive => favor many, zero => uniform
    int t = rnd.next(-2, 2);
    // k in [0..5]: number of names containing "FBI"
    int k = rnd.wnext(n+1, t);

    // Choose which positions have "FBI"
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end());
    vector<bool> hasFBI(n, false);
    for (int i = 0; i < k; i++) {
        hasFBI[idx[i]] = true;
    }

    // Character set: A-Z, 0-9, dash
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";

    // Generate and print 5 names
    for (int i = 0; i < n; i++) {
        if (hasFBI[i]) {
            // length between 3 and 10, reserve room for "FBI"
            int totalLen = rnd.next(3, 10);
            int pre = rnd.next(0, totalLen - 3);
            int suf = totalLen - 3 - pre;
            string s;
            for (int j = 0; j < pre; j++)
                s += rnd.any(chars);
            s += "FBI";
            for (int j = 0; j < suf; j++)
                s += rnd.any(chars);
            println(s);
        } else {
            // Generate a name that does NOT contain "FBI"
            string s;
            do {
                int len = rnd.next(1, 10);
                s.clear();
                for (int j = 0; j < len; j++)
                    s += rnd.any(chars);
            } while (s.find("FBI") != string::npos);
            println(s);
        }
    }

    return 0;
}
