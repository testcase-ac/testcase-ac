#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static string lettersPool;

// Generate a random user name (length 3 to 8) from the chosen pool
string genName() {
    int len = rnd.next(3, 8);
    string s;
    for (int i = 0; i < len; i++) {
        s += lettersPool[rnd.next(0, (int)lettersPool.size() - 1)];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose a letter pool for names: lowercase, uppercase, or mixed
    vector<string> letterPools = {
        "abcdefghijklmnopqrstuvwxyz",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    };
    lettersPool = rnd.any(letterPools);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Number of friendship relations in this test
        int F = rnd.next(1, 10);
        println(F);

        vector<string> names;
        set<pair<string,string>> edges;

        for (int i = 0; i < F; i++) {
            string a, b;
            bool done = false;

            // Try up to 50 times to create a diverse kind of edge
            for (int it = 0; it < 50 && !done; it++) {
                double r = rnd.next();
                if ((int)names.size() < 2 || r < 0.3) {
                    // new-new
                    a = genName();
                    b = genName();
                    if (a == b) continue;
                } else if (r < 0.7) {
                    // new-old
                    a = genName();
                    b = rnd.any(names);
                } else {
                    // old-old
                    a = rnd.any(names);
                    b = rnd.any(names);
                    if (a == b) continue;
                }

                // normalize edge
                pair<string,string> p = a < b ? make_pair(a,b) : make_pair(b,a);
                if (edges.count(p)) continue;

                // accept this edge
                edges.insert(p);
                // add new names if needed
                if (find(names.begin(), names.end(), a) == names.end())
                    names.push_back(a);
                if (find(names.begin(), names.end(), b) == names.end())
                    names.push_back(b);
                done = true;
            }

            // Fallback: ensure we still produce a valid (new) edge
            if (!done) {
                do {
                    a = genName();
                    b = genName();
                } while (a == b);
                pair<string,string> p = a < b ? make_pair(a,b) : make_pair(b,a);
                if (!edges.count(p)) {
                    edges.insert(p);
                }
                if (find(names.begin(), names.end(), a) == names.end())
                    names.push_back(a);
                if (find(names.begin(), names.end(), b) == names.end())
                    names.push_back(b);
            }

            // Output this friendship relation
            println(a, b);
        }
    }

    return 0;
}
