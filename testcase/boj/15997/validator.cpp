#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the four distinct team names
    vector<string> teams(4);
    for (int i = 0; i < 4; i++) {
        teams[i] = inf.readToken("[A-Z]{1,10}", "team");
        if (i < 3) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }
    // Check distinctness
    {
        set<string> st(teams.begin(), teams.end());
        ensuref(st.size() == 4, "Team names must be distinct");
    }
    // Map team name to index
    unordered_map<string,int> idx;
    for (int i = 0; i < 4; i++) {
        idx[teams[i]] = i;
    }

    // We'll record encountered matches to ensure each unordered pair appears exactly once
    set<pair<int,int>> matches;
    // Regex for a probability with up to 3 decimal places, and if ==1 then decimals must be zeros
    // Matches: "0", "0.xxx", "1", "1.0", "1.00", "1.000"
    const string prob_re = "(0\\.[0-9]{1,3}|0|1|1\\.0{1,3})";

    for (int match_i = 0; match_i < 6; match_i++) {
        // A B W D L
        string A = inf.readToken("[A-Z]{1,10}", "A");
        inf.readSpace();
        string B = inf.readToken("[A-Z]{1,10}", "B");
        // Validate teams
        ensuref(idx.count(A), "Unknown team name '%s' in match %d", A.c_str(), match_i+1);
        ensuref(idx.count(B), "Unknown team name '%s' in match %d", B.c_str(), match_i+1);
        ensuref(A != B, "A and B must differ in match %d, got both '%s'", match_i+1, A.c_str());
        inf.readSpace();
        string Ws = inf.readToken(prob_re, "W");
        inf.readSpace();
        string Ds = inf.readToken(prob_re, "D");
        inf.readSpace();
        string Ls = inf.readToken(prob_re, "L");
        inf.readEoln();

        // Parse to double
        double W = stod(Ws);
        double D = stod(Ds);
        double L = stod(Ls);

        // Check each is in [0,1]
        ensuref(W >= 0.0 && W <= 1.0, "W out of range in match %d: %f", match_i+1, W);
        ensuref(D >= 0.0 && D <= 1.0, "D out of range in match %d: %f", match_i+1, D);
        ensuref(L >= 0.0 && L <= 1.0, "L out of range in match %d: %f", match_i+1, L);

        // Check sum to 1
        double sum = W + D + L;
        ensuref(fabs(sum - 1.0) <= 1e-6,
                "Probabilities in match %d sum to %f != 1", match_i+1, sum);

        // Record the unordered pair
        int i1 = idx[A], i2 = idx[B];
        int u = min(i1,i2), v = max(i1,i2);
        ensuref(!matches.count({u,v}),
                "Duplicate match between '%s' and '%s'", A.c_str(), B.c_str());
        matches.insert({u,v});
    }

    // Ensure we've got exactly all 6 distinct pairs
    ensuref((int)matches.size() == 6, "Number of distinct matches is %d, expected 6", (int)matches.size());

    inf.readEof();
    return 0;
}
