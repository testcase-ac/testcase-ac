#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    bool strong;
};

static vector<int> sortedValues(const set<int>& values) {
    return vector<int>(values.begin(), values.end());
}

static int pickOne(const set<int>& values) {
    vector<int> candidates = sortedValues(values);
    return candidates[rnd.next(static_cast<int>(candidates.size()))];
}

static void pruneLive(set<int>& liveObjects, map<int, bool>& roots, map<int, Edge>& liveEdges, bool strongOnly) {
    map<int, vector<pair<int, bool>>> graph;
    for (const auto& item : liveEdges) {
        graph[item.second.from].push_back({item.second.to, item.second.strong});
    }

    set<int> reachable;
    vector<int> stack;
    for (const auto& item : roots) {
        if (item.second && liveObjects.count(item.first)) {
            reachable.insert(item.first);
            stack.push_back(item.first);
        }
    }

    while (!stack.empty()) {
        int cur = stack.back();
        stack.pop_back();
        for (const auto& next : graph[cur]) {
            if (strongOnly && !next.second) {
                continue;
            }
            if (liveObjects.count(next.first) && reachable.insert(next.first).second) {
                stack.push_back(next.first);
            }
        }
    }

    for (auto it = liveObjects.begin(); it != liveObjects.end();) {
        if (!reachable.count(*it)) {
            roots.erase(*it);
            it = liveObjects.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = liveEdges.begin(); it != liveEdges.end();) {
        if (!liveObjects.count(it->second.from) || !liveObjects.count(it->second.to)) {
            it = liveEdges.erase(it);
        } else {
            ++it;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int initialCount = rnd.next(1, 8);
    int targetEvents = rnd.next(8, 35);
    int cleanupBudget = rnd.next(1, 5);

    vector<pair<int, bool>> initialObjects;
    set<int> usedObjects;
    set<int> liveObjects;
    map<int, bool> roots;
    map<int, Edge> liveEdges;
    set<int> usedRefs;
    vector<string> events;

    int nextObjectId = rnd.next(1, 30);
    while (static_cast<int>(initialObjects.size()) < initialCount) {
        while (usedObjects.count(nextObjectId)) {
            ++nextObjectId;
        }
        bool isRoot = rnd.next(100) < 35;
        initialObjects.push_back({nextObjectId, isRoot});
        usedObjects.insert(nextObjectId);
        liveObjects.insert(nextObjectId);
        roots[nextObjectId] = isRoot;
        ++nextObjectId;
    }

    int nextRefId = rnd.next(1, 40);
    for (int step = 0; step < targetEvents; ++step) {
        int remaining = targetEvents - step;
        bool mustCleanup = cleanupBudget > 0 && remaining == cleanupBudget;
        int op = mustCleanup ? 0 : rnd.next(100);

        if (cleanupBudget > 0 && (mustCleanup || op < 18)) {
            bool strongOnly = rnd.next(2) == 0;
            events.push_back(strongOnly ? "M" : "m");
            pruneLive(liveObjects, roots, liveEdges, strongOnly);
            --cleanupBudget;
            continue;
        }

        if (liveObjects.empty() || op < 42) {
            while (usedObjects.count(nextObjectId)) {
                ++nextObjectId;
            }
            bool isRoot = rnd.next(100) < 30;
            events.push_back("MADE " + to_string(nextObjectId) + (isRoot ? " ROOT" : " -"));
            usedObjects.insert(nextObjectId);
            liveObjects.insert(nextObjectId);
            roots[nextObjectId] = isRoot;
            ++nextObjectId;
            continue;
        }

        if (op < 78 || liveEdges.empty()) {
            while (usedRefs.count(nextRefId)) {
                ++nextRefId;
            }
            int from = pickOne(liveObjects);
            int to = rnd.next(100) < 20 ? from : pickOne(liveObjects);
            bool strong = rnd.next(100) < 60;
            events.push_back("ADD " + to_string(nextRefId) + " " + to_string(from) + (strong ? " => " : " -> ") + to_string(to));
            usedRefs.insert(nextRefId);
            liveEdges[nextRefId] = {from, to, strong};
            ++nextRefId;
            continue;
        }

        vector<int> refs;
        for (const auto& item : liveEdges) {
            refs.push_back(item.first);
        }
        int refId = refs[rnd.next(static_cast<int>(refs.size()))];
        events.push_back("REMOVE " + to_string(refId));
        liveEdges.erase(refId);
        usedRefs.erase(refId);
    }

    if (cleanupBudget > 0) {
        events.push_back(rnd.next(2) == 0 ? "M" : "m");
    }

    println(initialCount, static_cast<int>(events.size()));
    for (const auto& object : initialObjects) {
        println(object.first, object.second ? string("ROOT") : string("-"));
    }
    for (const string& event : events) {
        println(event);
    }

    return 0;
}
