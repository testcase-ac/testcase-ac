#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<bool>> adj;
vector<string> files;
unordered_map<string,int> mp;

// Reads an answer (either from jury or contestant), validates it, and returns
// the cycle as a vector of indices. An empty vector means "SHIP IT".
// On error in contestant output -> _wa, in jury output -> _fail.
vector<int> readAns(InStream& stream) {
    vector<int> cycle;
    vector<bool> used(n, false);

    // Read first token
    if (stream.eoln()) {
        stream.quitf(_wa, "empty line in answer");
    }
    string tok = stream.readToken();
    // Check for "SHIP IT"
    if (tok == "SHIP") {
        string tok2 = stream.readToken();
        if (tok2 != "IT")
            stream.quitf(_wa, "expected \"SHIP IT\", found \"%s %s\"", tok.c_str(), tok2.c_str());
        stream.readEoln();
        return cycle; // empty => no cycle
    }
    // Otherwise it's a file name
    // First name
    if (!mp.count(tok))
        stream.quitf(_wa, "file \"%s\" not found", tok.c_str());
    int id = mp[tok];
    cycle.push_back(id);
    used[id] = true;
    // Read remaining names on this line
    while (!stream.eoln()) {
        string s2 = stream.readToken();
        if (!mp.count(s2))
            stream.quitf(_wa, "file \"%s\" not found", s2.c_str());
        int id2 = mp[s2];
        if (used[id2])
            stream.quitf(_wa, "file \"%s\" is duplicated in cycle", s2.c_str());
        used[id2] = true;
        cycle.push_back(id2);
    }
    stream.readEoln();

    int L = cycle.size();
    if (L == 0) {
        // should not happen
        stream.quitf(_wa, "invalid cycle length 0");
    }
    // Validate edges
    for (int i = 0; i < L; i++) {
        int u = cycle[i];
        int v = cycle[(i+1)%L];
        if (!adj[u][v])
            stream.quitf(_wa, "no dependency from \"%s\" to \"%s\"",
                         files[u].c_str(), files[v].c_str());
    }
    return cycle;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    n = inf.readInt();
    files.resize(n);
    adj.assign(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        files[i] = inf.readToken();
        mp[files[i]] = i;
    }
    // For each file, read its imports
    for (int i = 0; i < n; i++) {
        string fname = inf.readToken();
        int k = inf.readInt();
        // fname should match files[i], but we don't enforce
        inf.readEoln();
        for (int j = 0; j < k; j++) {
            // read line: "import x, y, z"
            string imp = inf.readToken();
            if (imp != "import")
                inf.quitf(_fail, "expected 'import', found '%s'", imp.c_str());
            string line = inf.readLine();
            // strip leading spaces
            if (!line.empty() && line[0] == ' ') line.erase(line.begin());
            // split by ", "
            while (!line.empty()) {
                size_t pos = line.find(", ");
                string dep = (pos == string::npos ? line : line.substr(0, pos));
                if (!mp.count(dep))
                    inf.quitf(_fail, "imported file \"%s\" not in list", dep.c_str());
                int u = mp[fname];
                int v = mp[dep];
                adj[u][v] = true;
                if (pos == string::npos) break;
                line = line.substr(pos + 2);
            }
        }
    }
    // Read jury and participant answers
    vector<int> jans = readAns(ans);
    vector<int> pans = readAns(ouf);

    // Compare
    if (jans.empty()) {
        // No cycle exists
        if (!pans.empty()) {
            quitf(_wa, "found a dependency cycle of length %d while expected none", (int)pans.size());
        } else {
            quitf(_ok, "SHIP IT");
        }
    } else {
        // A shortest cycle of length L exists
        int L = jans.size();
        if (pans.empty()) {
            quitf(_wa, "expected a cycle of length %d, found none", L);
        }
        int P = pans.size();
        if (P > L) {
            quitf(_wa, "cycle is longer than shortest: jury = %d, found = %d", L, P);
        } else if (P < L) {
            quitf(_fail, "participant found shorter cycle than jury: jury = %d, found = %d", L, P);
        } else {
            quitf(_ok, "cycle of length %d", P);
        }
    }
    return 0;
}
