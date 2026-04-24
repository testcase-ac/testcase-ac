#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of link info lines
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // To store defined sites
    set<string> defined;
    vector<string> targets(N);
    vector<vector<string>> incoming(N);

    // Read each link info line
    for (int i = 0; i < N; i++) {
        // Target site name
        string tgt = inf.readToken("[A-Z]{1,50}", "site_name");
        ensuref(!defined.count(tgt),
                "Duplicate definition of site \"%s\" at line %d",
                tgt.c_str(), i + 2);
        defined.insert(tgt);
        targets[i] = tgt;

        // Number of incoming sites
        inf.readSpace();
        int K = inf.readInt(0, 24, "K");

        // Read the K incoming site names
        set<string> seen_in;
        vector<string> incs;
        for (int j = 0; j < K; j++) {
            inf.readSpace();
            string inc = inf.readToken("[A-Z]{1,50}", "incoming_site");
            // Check duplicates in this list
            ensuref(seen_in.insert(inc).second,
                    "Duplicate incoming site \"%s\" for target site \"%s\" at line %d",
                    inc.c_str(), tgt.c_str(), i + 2);
            incs.push_back(inc);
        }
        incoming[i] = incs;

        inf.readEoln();
    }

    // Read the query site
    string query = inf.readToken("[A-Z]{1,50}", "query_site");
    inf.readEoln();
    // Must be one of the defined target sites
    ensuref(defined.count(query),
            "Query site \"%s\" is not defined among the %d link infos", 
            query.c_str(), N);

    // No extra content
    inf.readEof();
    return 0;
}
