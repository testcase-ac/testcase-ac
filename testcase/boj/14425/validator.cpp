#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Read the N strings into set S, ensure no duplicates
    set<string> S;
    for (int i = 0; i < N; i++) {
        // each string: only lowercase letters, length 1 to 500
        string s = inf.readToken("[a-z]{1,500}", "S_string");
        inf.readEoln();
        ensuref(!S.count(s),
                "Duplicate string in S at index %d: \"%s\"", i, s.c_str());
        S.insert(s);
    }

    // Read the M query strings, just validate format
    for (int i = 0; i < M; i++) {
        string t = inf.readToken("[a-z]{1,500}", "query_string");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
