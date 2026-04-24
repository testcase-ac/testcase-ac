#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int N_MAX = 20;

    // Scenario selector
    // 0-1: small edge-case
    // 2-5: valid PPAP string
    // 6-7: invalid by length %3!=1
    // 8-9: invalid by mutation of valid
    int scen = rnd.next(0, 9);
    string s;

    if (scen < 2) {
        // Small edge cases
        vector<string> edges = {"P", "A", "PP", "PA", "AP", "AA"};
        s = rnd.any(edges);
    }
    else if (scen < 6) {
        // Generate a valid PPAP string by random expansions
        s = "P";
        int expansions = rnd.next(0, 5);
        for (int it = 0; it < expansions; ++it) {
            if ((int)s.size() + 3 > N_MAX) break;
            // collect positions of 'P'
            vector<int> pos;
            for (int i = 0; i < (int)s.size(); ++i)
                if (s[i] == 'P') pos.push_back(i);
            if (pos.empty()) break;
            int p = rnd.any(pos);
            // replace P at p with PPAP
            s = s.substr(0, p) + "PPAP" + s.substr(p + 1);
        }
    }
    else if (scen < 8) {
        // Invalid by length mod 3 != 1
        int n;
        do {
            n = rnd.next(1, N_MAX);
        } while (n % 3 == 1);
        s.resize(n);
        for (int i = 0; i < n; ++i)
            s[i] = rnd.next(0, 1) ? 'P' : 'A';
    }
    else {
        // Invalid by mutating a valid string
        // First generate a valid one
        string t = "P";
        int expansions = rnd.next(1, 5);
        for (int it = 0; it < expansions; ++it) {
            if ((int)t.size() + 3 > N_MAX) break;
            vector<int> pos;
            for (int i = 0; i < (int)t.size(); ++i)
                if (t[i] == 'P') pos.push_back(i);
            if (pos.empty()) break;
            int p = rnd.any(pos);
            t = t.substr(0, p) + "PPAP" + t.substr(p + 1);
        }
        s = t;
        if (s.empty()) s = "P";
        // Mutate one character to break validity
        int idx = rnd.next(0, (int)s.size() - 1);
        s[idx] = (s[idx] == 'P' ? 'A' : 'P');
    }

    // Ensure length constraints
    if (s.empty() || s.size() > N_MAX) {
        s = "P";
    }
    println(s);
    return 0;
}
