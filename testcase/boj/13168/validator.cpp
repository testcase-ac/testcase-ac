#include "testlib.h"

#include <algorithm>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

int findRoot(vector<int>& parent, int x) {
    if (parent[x] == x) {
        return x;
    }
    parent[x] = findRoot(parent, parent[x]);
    return parent[x];
}

void unite(vector<int>& parent, int a, int b) {
    a = findRoot(parent, a);
    b = findRoot(parent, b);
    if (a != b) {
        parent[b] = a;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const set<string> transportTypes = {
        "Subway",        "Bus",           "Taxi",      "Airplane",
        "KTX",           "S-Train",       "V-Train",   "ITX-Saemaeul",
        "ITX-Cheongchun", "Mugunghwa",
    };

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int r = inf.readInt(1, 1000000, "R");
    (void)r;
    inf.readEoln();

    map<string, int> cityIndex;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        string city = inf.readToken("[A-Za-z]{1,20}", "city");
        cityIndex.emplace(city, (int)cityIndex.size());
    }
    inf.readEoln();

    int m = inf.readInt(1, 200, "M");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        string city = inf.readToken("[A-Za-z]{1,20}", "plan_city");
        ensuref(cityIndex.count(city) != 0, "plan city %d is not listed: %s", i + 1, city.c_str());
    }
    inf.readEoln();

    int k = inf.readInt(1, 10000, "K");
    inf.readEoln();

    vector<int> parent(cityIndex.size());
    iota(parent.begin(), parent.end(), 0);

    for (int i = 0; i < k; ++i) {
        string type = inf.readToken("[A-Za-z\\-]{1,20}", "Type_i");
        ensuref(transportTypes.count(type) != 0, "invalid transport type at line %d: %s", i + 1, type.c_str());
        inf.readSpace();

        string s = inf.readToken("[A-Za-z]{1,20}", "S_i");
        ensuref(cityIndex.count(s) != 0, "transport start city %d is not listed: %s", i + 1, s.c_str());
        inf.readSpace();

        string e = inf.readToken("[A-Za-z]{1,20}", "E_i");
        ensuref(cityIndex.count(e) != 0, "transport end city %d is not listed: %s", i + 1, e.c_str());
        inf.readSpace();

        int cost = inf.readInt(1, 100000, "Cost_i");
        (void)cost;
        inf.readEoln();

        unite(parent, cityIndex[s], cityIndex[e]);
    }

    int root = findRoot(parent, 0);
    for (int i = 1; i < (int)parent.size(); ++i) {
        ensuref(findRoot(parent, i) == root, "listed cities are not connected by transport lines");
    }

    inf.readEof();
}
