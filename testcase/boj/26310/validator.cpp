#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(6, 50, "N");
    inf.readEoln();

    // We expect exactly these six countries
    const vector<string> allowed = {
        "Vietnam", "Indonesia", "Philippines", "Korea", "Taiwan", "Japan"
    };
    set<string> seen_countries;
    vector<string> names;
    vector<int> scores; // scaled by 100

    for (int i = 0; i < 6; i++) {
        // country name token
        string s = inf.readToken("Vietnam|Indonesia|Philippines|Korea|Taiwan|Japan", "country");
        // no duplicates
        bool inserted = seen_countries.insert(s).second;
        ensuref(inserted, "Duplicate country: %s", s.c_str());
        names.push_back(s);

        inf.readSpace();
        // Read p_t, p_u, r_t, r_u, f in order with their constraints
        int p_t = inf.readInt(0, 5000, "p_t");
        inf.readSpace();
        int p_u = inf.readInt(0, 5000, "p_u");
        inf.readSpace();
        int r_t = inf.readInt(0, 300, "r_t");
        inf.readSpace();
        int r_u = inf.readInt(0, 300, "r_u");
        inf.readSpace();
        int f   = inf.readInt(0, 30,   "f");
        inf.readEoln();

        // Check implied ordering constraints
        ensuref(p_u <= p_t,
                "p_u (%d) must be <= p_t (%d) for country %s", p_u, p_t, s.c_str());
        ensuref(r_u <= r_t,
                "r_u (%d) must be <= r_t (%d) for country %s", r_u, r_t, s.c_str());

        // Compute site score scaled by 100 to avoid floating issues:
        // score = 0.56*r_u + 0.24*r_t + 0.14*p_u + 0.06*p_t + 0.3*f
        // scaled: 56*r_u + 24*r_t + 14*p_u + 6*p_t + 30*f
        int sc = 56 * r_u + 24 * r_t + 14 * p_u + 6 * p_t + 30 * f;
        scores.push_back(sc);
    }

    // All six distinct?
    ensuref((int)seen_countries.size() == 6,
            "Expected 6 distinct countries, got %d", (int)seen_countries.size());

    // Enforce distinct site scores
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {
            ensuref(scores[i] != scores[j],
                    "Site scores must be distinct, but %s and %s both have score %d",
                    names[i].c_str(), names[j].c_str(), scores[i]);
        }
    }

    inf.readEof();
    return 0;
}
