#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read first list (entry order)
    set<string> s_entry;
    vector<string> entry(N);
    for (int i = 0; i < N; i++) {
        // Each vehicle number: 6 to 8 chars, A-Z or 0-9
        string str = inf.readToken("[A-Z0-9]{6,8}", "entry");
        inf.readEoln();
        bool inserted = s_entry.insert(str).second;
        ensuref(inserted,
                "Duplicate vehicle in entry list at index %d: %s",
                i+1, str.c_str());
        entry[i] = str;
    }

    // Read second list (exit order)
    set<string> s_exit;
    vector<string> exitv(N);
    for (int i = 0; i < N; i++) {
        string str = inf.readToken("[A-Z0-9]{6,8}", "exit");
        inf.readEoln();
        bool inserted = s_exit.insert(str).second;
        ensuref(inserted,
                "Duplicate vehicle in exit list at index %d: %s",
                i+1, str.c_str());
        exitv[i] = str;
    }

    // The two lists must be permutations of each other
    ensuref((int)s_entry.size() == N, "Entry list size mismatch");
    ensuref((int)s_exit.size()  == N, "Exit list size mismatch");
    for (const auto &v : s_entry) {
        ensuref(s_exit.count(v),
                "Vehicle %s appears in entry list but not in exit list",
                v.c_str());
    }
    // No need to check the reverse: same size and above ensures equality.

    inf.readEof();
    return 0;
}
