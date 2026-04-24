#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input data: we only need participant names to validate output
    int n = inf.readInt(); 
    string s = inf.readToken(); // the target sum, unused in checker
    set<string> participants;
    for (int i = 0; i < n; i++) {
        string name = inf.readWord();
        string bet  = inf.readToken(); // unused
        participants.insert(name);
    }

    // A helper to read the answer (jury or contestant) and return
    // a sorted vector of names. On error, quits with WA for contestant
    // or FAIL for jury.
    auto readAns = [&](InStream &stream) {
        int k = stream.readInt(0, n, "number of winners");
        vector<string> names;
        set<string> seen;
        for (int i = 0; i < k; i++) {
            string t = stream.readWord();
            if (!participants.count(t))
                stream.quitf(_wa, "unknown participant '%s'", t.c_str());
            if (!seen.insert(t).second)
                stream.quitf(_wa, "participant '%s' listed twice", t.c_str());
            names.push_back(t);
        }
        // No extra tokens allowed
        if (!stream.seekEof())
            stream.quitf(_wa, "extraneous data after participants list");
        sort(names.begin(), names.end());
        return names;
    };

    // Read jury and contestant outputs
    vector<string> juryAns = readAns(ans);
    vector<string> partAns = readAns(ouf);

    // Compare the two sorted lists
    if (juryAns.size() != partAns.size())
        quitf(_wa, "jury has %d winners, contestant has %d winners",
              (int)juryAns.size(), (int)partAns.size());
    for (size_t i = 0; i < juryAns.size(); i++) {
        if (juryAns[i] != partAns[i])
            quitf(_wa, "expected participant '%s', found '%s'",
                  juryAns[i].c_str(), partAns[i].c_str());
    }

    // All good
    quitf(_ok, "%d winners", (int)juryAns.size());
}
