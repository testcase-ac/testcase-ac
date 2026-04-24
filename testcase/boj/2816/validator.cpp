#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 100, "N");
    inf.readEoln();

    vector<string> names(N);
    set<string> seen;
    for (int i = 0; i < N; i++) {
        // Each channel name: 1 to 10 chars, uppercase letters and digits only
        string s = inf.readToken("[A-Z0-9]{1,10}", "channel_name");
        inf.readEoln();
        ensuref(!seen.count(s),
                "Duplicate channel name at index %d: '%s'", i, s.c_str());
        names[i] = s;
        seen.insert(s);
    }

    // Must contain both KBS1 and KBS2
    ensuref(seen.count("KBS1"), "Missing required channel: KBS1");
    ensuref(seen.count("KBS2"), "Missing required channel: KBS2");

    // Input must not already have KBS1 at 1st and KBS2 at 2nd positions
    ensuref(!(names[0] == "KBS1" && names[1] == "KBS2"),
            "Channels already in desired positions: KBS1 at 1 and KBS2 at 2");

    inf.readEof();
    return 0;
}
