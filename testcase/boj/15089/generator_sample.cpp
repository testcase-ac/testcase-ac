#include "testlib.h"

#include <string>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int classCount = rnd.next(2, 12);
    vector<string> classes;
    for (int i = 0; i < classCount; ++i) {
        classes.push_back(string("C") + to_string(i));
    }

    int mode = rnd.next(4);
    vector<pair<int, int>> isA;
    vector<pair<int, int>> hasA;

    if (mode == 0) {
        for (int i = 0; i + 1 < classCount; ++i) {
            isA.push_back({i, i + 1});
        }
    } else if (mode == 1) {
        for (int i = 1; i < classCount; ++i) {
            isA.push_back({rnd.next(0, i - 1), i});
        }
    } else if (mode == 2) {
        for (int i = 0; i + 1 < classCount; ++i) {
            if (rnd.next(2) == 0) {
                isA.push_back({i, i + 1});
            } else {
                hasA.push_back({i, i + 1});
            }
        }
    } else {
        for (int i = 1; i < classCount; ++i) {
            if (rnd.next(3) == 0) {
                isA.push_back({rnd.next(0, i - 1), i});
            }
        }
    }

    int extraEdges = rnd.next(0, classCount);
    for (int t = 0; t < extraEdges; ++t) {
        int a = rnd.next(0, classCount - 1);
        int b = rnd.next(0, classCount - 1);
        if (a == b || rnd.next(3) != 0) {
            hasA.push_back({a, b});
        } else {
            if (a < b) {
                isA.push_back({a, b});
            } else {
                isA.push_back({b, a});
            }
        }
    }

    vector<pair<int, int>> relations;
    vector<string> relationTypes;
    for (auto edge : isA) {
        relations.push_back(edge);
        relationTypes.push_back("is-a");
    }
    for (auto edge : hasA) {
        relations.push_back(edge);
        relationTypes.push_back("has-a");
    }

    if (relations.empty()) {
        relations.push_back({0, 1});
        relationTypes.push_back("is-a");
    }

    vector<int> active;
    vector<int> seen(classCount, 0);
    for (auto edge : relations) {
        seen[edge.first] = 1;
        seen[edge.second] = 1;
    }
    for (int i = 0; i < classCount; ++i) {
        if (seen[i]) {
            active.push_back(i);
        }
    }

    vector<int> order(relations.size());
    for (int i = 0; i < static_cast<int>(order.size()); ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    int queryCount = rnd.next(4, 18);
    println(static_cast<int>(relations.size()), queryCount);
    for (int index : order) {
        println(classes[relations[index].first], relationTypes[index], classes[relations[index].second]);
    }

    for (int q = 0; q < queryCount; ++q) {
        int a = rnd.any(active);
        int b = rnd.any(active);
        string relation = rnd.next(2) == 0 ? "is-a" : "has-a";

        if (q == 0) {
            b = a;
            relation = "is-a";
        } else if (q == 1 && !relations.empty()) {
            int index = rnd.next(0, static_cast<int>(relations.size()) - 1);
            a = relations[index].first;
            b = relations[index].second;
            relation = relationTypes[index];
        } else if (q == 2 && active.size() >= 2) {
            a = active.back();
            b = active.front();
            relation = "is-a";
        }

        println(classes[a], relation, classes[b]);
    }

    return 0;
}
