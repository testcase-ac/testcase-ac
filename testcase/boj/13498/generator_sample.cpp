#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Dataset {
    int n;
    vector<tuple<int, int, string>> relationships;
    vector<tuple<int, int, string>> events;
    int k;
};

string probabilityValue() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return "0";
    if (mode == 1) return "1";
    if (mode == 2) return "0." + rnd.any(vector<string>{"1", "2", "25", "333", "5", "75", "9"});
    if (mode == 3) return rnd.any(vector<string>{"0.01", "0.05", "0.95", "0.99"});
    return rnd.any(vector<string>{"0.4", "0.8", "0.85", "0.9"});
}

string damageValue() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return "0";
    if (mode == 1) return to_string(rnd.next(1, 30));
    if (mode == 2) return to_string(rnd.next(1, 999)) + "." + rnd.any(vector<string>{"25", "5", "75"});
    if (mode == 3) return rnd.any(vector<string>{"1000", "9999.99", "10000"});
    return to_string(rnd.next(31, 3000));
}

void addRelationship(Dataset& ds, set<pair<int, int>>& used, int u, int v, const string& p) {
    if (used.insert({u, v}).second) {
        ds.relationships.push_back({u, v, p});
    }
}

Dataset makeDataset(int mode) {
    Dataset ds{};
    ds.n = rnd.next(2, mode == 4 ? 14 : 9);
    set<pair<int, int>> used;

    if (mode == 0) {
        ds.k = 0;
        int r = rnd.next(0, min(6, ds.n * ds.n));
        while ((int)ds.relationships.size() < r) {
            addRelationship(ds, used, rnd.next(1, ds.n), rnd.next(1, ds.n), probabilityValue());
        }
    } else if (mode == 1) {
        addRelationship(ds, used, 1, 2, probabilityValue());
        if (rnd.next(0, 1)) addRelationship(ds, used, 2, 1, probabilityValue());
        ds.k = rnd.next(0, 2);
    } else if (mode == 2) {
        int len = rnd.next(2, min(ds.n, 6));
        vector<int> path = {1};
        for (int v = 3; (int)path.size() + 1 < len && v <= ds.n; ++v) {
            path.push_back(v);
        }
        path.push_back(2);
        for (int i = 0; i + 1 < (int)path.size(); ++i) {
            addRelationship(ds, used, path[i], path[i + 1], probabilityValue());
        }
        if (ds.n >= 4) {
            addRelationship(ds, used, 1, 3, "1");
            addRelationship(ds, used, 3, 2, "0");
        }
        ds.k = rnd.next(0, 3);
    } else if (mode == 3) {
        for (int u = 1; u <= ds.n; ++u) {
            for (int v = 1; v <= ds.n; ++v) {
                if (rnd.next(0, 3) == 0) addRelationship(ds, used, u, v, probabilityValue());
            }
        }
        ds.k = rnd.next(0, 5);
    } else {
        vector<pair<int, int>> pairs;
        for (int u = 1; u <= ds.n; ++u) {
            for (int v = 1; v <= ds.n; ++v) pairs.push_back({u, v});
        }
        shuffle(pairs.begin(), pairs.end());
        int r = rnd.next(ds.n, min((int)pairs.size(), 35));
        for (int i = 0; i < r; ++i) {
            addRelationship(ds, used, pairs[i].first, pairs[i].second, probabilityValue());
        }
        ds.k = rnd.next(0, 8);
    }

    int m;
    if (mode == 0) {
        m = rnd.next(0, 4);
    } else if (mode == 4) {
        m = rnd.next(12, 40);
    } else {
        m = rnd.next(3, 12);
    }

    for (int i = 0; i < m; ++i) {
        int u;
        int v;
        if (mode == 1 && i < 3) {
            u = 1;
            v = 2;
        } else if (mode == 2 && i % 3 == 0) {
            u = rnd.any(vector<int>{1, 2});
            v = rnd.next(1, ds.n);
        } else {
            u = rnd.next(1, ds.n);
            v = rnd.next(1, ds.n);
        }
        ds.events.push_back({u, v, damageValue()});
    }

    ds.k = min(ds.k, (int)ds.events.size());
    if (!ds.events.empty() && rnd.next(0, 3) == 0) {
        ds.k = rnd.next(0, (int)ds.events.size());
    }

    shuffle(ds.relationships.begin(), ds.relationships.end());
    shuffle(ds.events.begin(), ds.events.end());
    return ds;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasetCount = rnd.next(1, 5);
    vector<Dataset> datasets;
    datasets.reserve(datasetCount);

    for (int tc = 0; tc < datasetCount; ++tc) {
        int mode = tc < 5 ? tc : rnd.next(0, 4);
        datasets.push_back(makeDataset(mode));
    }

    println(datasetCount);
    for (const Dataset& ds : datasets) {
        println(ds.n, (int)ds.relationships.size(), (int)ds.events.size(), ds.k);
        for (const auto& [u, v, p] : ds.relationships) {
            println(u, v, p);
        }
        for (const auto& [u, v, d] : ds.events) {
            println(u, v, d);
        }
    }

    return 0;
}
