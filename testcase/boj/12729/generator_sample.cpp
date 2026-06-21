#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string makeName(int index) {
    static const vector<string> roots = {
        "Alpha", "Beta", "Gamma", "Delta", "Echo",
        "Search", "Find", "Query", "Index", "Lookup"
    };
    static const vector<string> suffixes = {
        "One", "Two", "Three", "Four", "Five",
        "6", "7", "8", "9", "10"
    };

    string name = roots[index % (int)roots.size()];
    if (rnd.next(2) == 0) {
        name += " ";
        name += suffixes[(index + rnd.next((int)suffixes.size())) %
                         (int)suffixes.size()];
    } else {
        name += to_string(index + 1);
    }
    return name;
}

vector<string> makeEngines(int s) {
    set<string> used;
    vector<string> engines;

    for (int i = 0; (int)engines.size() < s; ++i) {
        string name = makeName(i);
        if (used.insert(name).second) engines.push_back(name);
    }

    shuffle(engines.begin(), engines.end());
    return engines;
}

vector<string> makeQueries(const vector<string>& engines) {
    int s = (int)engines.size();
    int mode = rnd.next(5);
    vector<string> queries;

    if (mode == 0) {
        return queries;
    }

    if (mode == 1) {
        int q = rnd.next(1, 25);
        string engine = rnd.any(engines);
        queries.assign(q, engine);
        return queries;
    }

    if (mode == 2) {
        int rounds = rnd.next(1, min(8, 100 / s));
        vector<string> order = engines;
        for (int r = 0; r < rounds; ++r) {
            shuffle(order.begin(), order.end());
            for (const string& engine : order) queries.push_back(engine);
        }
        return queries;
    }

    if (mode == 3) {
        int q = rnd.next(s, min(60, max(s, s * 8)));
        vector<string> active = engines;
        shuffle(active.begin(), active.end());
        int prefix = rnd.next(1, s);
        active.resize(prefix);
        for (int i = 0; i < q; ++i) {
            if (rnd.next(5) == 0) shuffle(active.begin(), active.end());
            queries.push_back(rnd.any(active));
        }
        return queries;
    }

    int q = rnd.next(1, 100);
    string current = rnd.any(engines);
    for (int i = 0; i < q; ++i) {
        if (i == 0 || rnd.next(100) < 35) current = rnd.any(engines);
        queries.push_back(current);
    }
    return queries;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int s = rnd.next(2, 10);
        vector<string> engines = makeEngines(s);
        vector<string> queries = makeQueries(engines);

        println(s);
        for (const string& engine : engines) println(engine);
        println((int)queries.size());
        for (const string& query : queries) println(query);
    }

    return 0;
}
