#include "testlib.h"

#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

namespace {

constexpr int MAX_LINES = 10000;
constexpr int MAX_CLASSES = 500;

int getId(map<string, int>& ids, const string& name) {
    auto it = ids.find(name);
    if (it != ids.end()) {
        return it->second;
    }
    int id = static_cast<int>(ids.size());
    ids[name] = id;
    ensuref(id < MAX_CLASSES, "more than %d distinct class names", MAX_CLASSES);
    return id;
}

string readClassName(const char* name) {
    // CHECK: The statement only says class names are single-word; cap visible ASCII
    // tokens at 64 characters so unbounded names do not create impractical inputs.
    return inf.readToken("[!-~]{1,64}", name);
}

string readRelation(const char* name) {
    string relation = inf.readToken("is-a|has-a", name);
    ensuref(relation == "is-a" || relation == "has-a", "invalid relation: %s", relation.c_str());
    return relation;
}

bool hasNontrivialIsACycle(const vector<vector<int>>& graph) {
    const int n = static_cast<int>(graph.size());
    vector<int> color(n, 0);

    auto dfs = [&](auto&& self, int v) -> bool {
        color[v] = 1;
        for (int to : graph[v]) {
            if (to == v) {
                continue;
            }
            if (color[to] == 1) {
                return true;
            }
            if (color[to] == 0 && self(self, to)) {
                return true;
            }
        }
        color[v] = 2;
        return false;
    };

    for (int i = 0; i < n; ++i) {
        if (color[i] == 0 && dfs(dfs, i)) {
            return true;
        }
    }
    return false;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, MAX_LINES, "n");
    inf.readSpace();
    int m = inf.readInt(1, MAX_LINES, "m");
    inf.readEoln();

    map<string, int> ids;
    set<string> initialClasses;
    vector<pair<int, int>> isARelations;

    for (int i = 0; i < n; ++i) {
        string c1 = readClassName("c1");
        inf.readSpace();
        string relation = readRelation("r");
        inf.readSpace();
        string c2 = readClassName("c2");
        inf.readEoln();

        int a = getId(ids, c1);
        int b = getId(ids, c2);
        initialClasses.insert(c1);
        initialClasses.insert(c2);
        if (relation == "is-a") {
            isARelations.push_back({a, b});
        }
    }

    for (int i = 0; i < m; ++i) {
        string c1 = readClassName("query_c1");
        inf.readSpace();
        readRelation("query_r");
        inf.readSpace();
        string c2 = readClassName("query_c2");
        inf.readEoln();

        ensuref(initialClasses.count(c1) != 0, "query %d first class not present in initial relations: %s",
                i + 1, c1.c_str());
        ensuref(initialClasses.count(c2) != 0, "query %d second class not present in initial relations: %s",
                i + 1, c2.c_str());
        getId(ids, c1);
        getId(ids, c2);
    }

    vector<vector<int>> isAGraph(ids.size());
    for (auto [a, b] : isARelations) {
        isAGraph[a].push_back(b);
    }
    ensuref(!hasNontrivialIsACycle(isAGraph), "is-a relationships contain a nontrivial cycle");

    inf.readEof();
}
