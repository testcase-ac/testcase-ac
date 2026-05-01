#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

string randomName(int maxLen) {
    static const string chars = "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "0123456789";
    int len = rnd.next(1, maxLen);
    string s;
    s.reserve(len);
    for (int i = 0; i < len; i++) {
        s += chars[rnd.next((int)chars.size() - 1)];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: size of the nickname pool
    int K = rnd.next(3, 10);
    int maxNameLen = rnd.next(3, 8);
    vector<string> pool;
    pool.reserve(K);
    // generate distinct names
    set<string> seen;
    while ((int)pool.size() < K) {
        string nm = randomName(maxNameLen);
        if (!seen.count(nm)) {
            seen.insert(nm);
            pool.push_back(nm);
        }
    }

    // number of segments (ENTER blocks)
    int S = rnd.next(1, 5);

    vector<string> lines;
    lines.reserve(1 + S * 10);

    // Build segments
    for (int seg = 0; seg < S; seg++) {
        lines.push_back("ENTER");
        // hyper-parameter for segment length: biased sampling
        int bias = rnd.next(-2, 2);
        int L = rnd.wnext(8, bias);  // up to 8 chats, with bias
        for (int i = 0; i < L; i++) {
            // pick a random name from pool
            string nm = rnd.any(pool);
            lines.push_back(nm);
        }
    }

    // Ensure at least one chat overall
    if ((int)lines.size() == S) {
        // all segments zero-length, force one chat
        lines.push_back("ENTER");
        lines.push_back(pool[0]);
    }

    int N = lines.size();
    println(N);
    for (auto &ln : lines) {
        println(ln);
    }

    return 0;
}
