#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of words in database
    int N = inf.readInt(1, 30000, "N");
    inf.readEoln();

    // Read database words, ensure lowercase and distinct
    set<string> db;
    for (int i = 0; i < N; i++) {
        string w = inf.readToken("[a-z]{1,29}", "db_word");
        inf.readEoln();
        // Check distinctness
        ensuref(!db.count(w), "Duplicate word in database at line %d: '%s'", i+2, w.c_str());
        db.insert(w);
    }

    // Number of queries
    int Q = inf.readInt(1, 30000, "Q");
    inf.readEoln();

    // Read queries, just check format
    for (int i = 0; i < Q; i++) {
        string q = inf.readToken("[a-z]{1,29}", "query_word");
        inf.readEoln();
        // No need to enforce distinctness among queries
    }

    inf.readEof();
    return 0;
}
