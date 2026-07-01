#include "testlib.h"

#include <set>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

namespace {

string className(int id) {
    return "C" + to_string(id);
}

void addRelation(vector<tuple<int, string, int>>& relations, set<tuple<int, string, int>>& used,
                 int a, const string& r, int b) {
    tuple<int, string, int> relation = {a, r, b};
    if (used.insert(relation).second) {
        relations.push_back(relation);
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int classCount = rnd.next(2, 18);
    int factTarget = rnd.next(classCount - 1, min(70, classCount * classCount));
    int queryCount = rnd.next(1, 45);

    vector<tuple<int, string, int>> facts;
    set<tuple<int, string, int>> usedFacts;

    if (mode == 0) {
        for (int i = 0; i + 1 < classCount; ++i) {
            addRelation(facts, usedFacts, i, "is-a", i + 1);
        }
    } else if (mode == 1) {
        for (int i = 0; i + 1 < classCount; ++i) {
            addRelation(facts, usedFacts, i, "is-a", rnd.next(i + 1, classCount - 1));
        }
    } else {
        for (int i = 0; i + 1 < classCount; ++i) {
            string relation = rnd.next(0, 1) == 0 ? "is-a" : "has-a";
            addRelation(facts, usedFacts, i, relation, i + 1);
        }
    }

    if (mode == 3) {
        for (int i = 0; i < classCount && static_cast<int>(facts.size()) < factTarget; ++i) {
            addRelation(facts, usedFacts, i, "is-a", i);
        }
    }

    while (static_cast<int>(facts.size()) < factTarget) {
        int a = rnd.next(0, classCount - 1);
        int b = rnd.next(0, classCount - 1);
        string relation;
        if (rnd.next(0, 99) < 45) {
            relation = "is-a";
            if (a > b) {
                swap(a, b);
            }
            if (a == b && rnd.next(0, 2) != 0) {
                continue;
            }
        } else {
            relation = "has-a";
        }
        addRelation(facts, usedFacts, a, relation, b);
    }

    shuffle(facts.begin(), facts.end());

    vector<int> activeClasses;
    vector<int> seen(classCount, 0);
    for (auto [a, relation, b] : facts) {
        seen[a] = 1;
        seen[b] = 1;
    }
    for (int i = 0; i < classCount; ++i) {
        if (seen[i]) {
            activeClasses.push_back(i);
        }
    }

    vector<tuple<int, string, int>> queries;
    for (int i = 0; i < queryCount; ++i) {
        int a = rnd.any(activeClasses);
        int b = rnd.any(activeClasses);
        string relation = rnd.next(0, 1) == 0 ? "is-a" : "has-a";
        queries.push_back({a, relation, b});
    }
    if (!activeClasses.empty()) {
        int c = rnd.any(activeClasses);
        queries[rnd.next(0, queryCount - 1)] = {c, "is-a", c};
    }

    println(static_cast<int>(facts.size()), queryCount);
    for (auto [a, relation, b] : facts) {
        println(className(a), relation, className(b));
    }
    for (auto [a, relation, b] : queries) {
        println(className(a), relation, className(b));
    }

    return 0;
}
