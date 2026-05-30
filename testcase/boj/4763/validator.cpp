#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static bool isCanonicalReal(const string& s) {
    int pos = 0;
    int n = (int)s.size();
    if (n == 0) return false;

    int intStart = pos;
    while (pos < n && isdigit((unsigned char)s[pos])) pos++;
    if (pos == intStart) return false;

    if (pos - intStart > 1 && s[intStart] == '0') return false;

    if (pos < n) {
        if (s[pos] != '.') return false;
        pos++;
        int fracStart = pos;
        while (pos < n && isdigit((unsigned char)s[pos])) pos++;
        if (pos == fracStart) return false;
    }

    return pos == n;
}

static double readRealToken(const string& name, bool positive) {
    string token = inf.readToken("[^ ]+", name.c_str());
    ensuref(isCanonicalReal(token), "%s must be a canonical nonnegative real number", name.c_str());

    double value = stod(token);
    if (positive) {
        ensuref(value > 0.0, "%s must be positive", name.c_str());
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    readRealToken("cable_length", false);
    inf.readEoln();

    // CHECK: The statement gives no explicit upper bound. This cap keeps the
    // string-heavy complete graph input practical while preserving the problem shape.
    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    unordered_map<string, int> houseId;
    houseId.reserve((size_t)n * 2);
    for (int i = 0; i < n; i++) {
        string name = inf.readToken("[A-Za-z0-9]{1,20}", "house_name");
        inf.readEoln();
        ensuref(houseId.emplace(name, i).second, "duplicate house name: %s", name.c_str());
    }

    int maxEdges = n * (n - 1) / 2;
    int m = inf.readInt(0, maxEdges, "M");
    inf.readEoln();

    set<pair<int, int>> seenEdges;
    for (int i = 0; i < m; i++) {
        string a = inf.readToken("[A-Za-z0-9]{1,20}", "house_a");
        inf.readSpace();
        string b = inf.readToken("[A-Za-z0-9]{1,20}", "house_b");
        inf.readSpace();
        readRealToken("distance", true);
        inf.readEoln();

        auto itA = houseId.find(a);
        auto itB = houseId.find(b);
        ensuref(itA != houseId.end(), "unknown first house at path %d: %s", i + 1, a.c_str());
        ensuref(itB != houseId.end(), "unknown second house at path %d: %s", i + 1, b.c_str());
        ensuref(itA->second != itB->second, "path %d connects a house to itself", i + 1);

        int u = itA->second;
        int v = itB->second;
        if (u > v) swap(u, v);
        ensuref(seenEdges.insert({u, v}).second, "duplicate path at line %d", i + 1);
    }

    inf.readEof();
}
