#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read the N stored site-password pairs
    set<string> sites;
    for (int i = 0; i < N; i++) {
        // Site address: lowercase, uppercase, dot, dash; length 1..20
        string site = inf.readToken("[A-Za-z.\\-]{1,20}", "site");
        inf.readSpace();
        // Password: uppercase letters only; length 1..20
        string password = inf.readToken("[A-Z]{1,20}", "password");
        inf.readEoln();

        // Check for duplicate site addresses
        ensuref(!sites.count(site),
                "Duplicate site address at index %d: %s", i, site.c_str());
        sites.insert(site);
    }

    // Read the M queries, each must refer to an existing site
    for (int j = 0; j < M; j++) {
        string query = inf.readToken("[A-Za-z.\\-]{1,20}", "query");
        inf.readEoln();
        ensuref(sites.count(query),
                "Query for unknown site at index %d: %s", j, query.c_str());
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
