#include "testlib.h"

#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Edge {
    long long from;
    long long to;
    bool strong;
};

static long long readIdToken(const string& token, const char* name) {
    ensuref(!token.empty(), "%s is empty", name);
    ensuref(token.size() <= 10, "%s is too long: %s", name, token.c_str());
    ensuref(token[0] != '0', "%s has leading zero: %s", name, token.c_str());

    long long value = 0;
    for (char c : token) {
        ensuref('0' <= c && c <= '9', "%s is not a positive integer: %s", name, token.c_str());
        value = value * 10 + (c - '0');
    }
    ensuref(1LL <= value && value <= 1000000000LL, "%s out of range: %lld", name, value);
    return value;
}

static vector<string> splitSpaces(const string& line) {
    vector<string> tokens;
    string cur;
    for (char c : line) {
        if (c == ' ') {
            ensuref(!cur.empty(), "empty token from repeated or leading space in line: %s", line.c_str());
            tokens.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    ensuref(!cur.empty(), "trailing space in line: %s", line.c_str());
    tokens.push_back(cur);
    return tokens;
}

static void pruneObjects(unordered_set<long long>& objects,
                         unordered_map<long long, bool>& roots,
                         unordered_map<long long, Edge>& edges,
                         bool strongOnly) {
    unordered_map<long long, vector<pair<long long, bool>>> adj;
    adj.reserve(edges.size() * 2 + 1);
    for (const auto& item : edges) {
        const Edge& edge = item.second;
        adj[edge.from].push_back({edge.to, edge.strong});
    }

    unordered_set<long long> reachable;
    reachable.reserve(objects.size() * 2 + 1);
    queue<long long> q;
    for (const auto& item : roots) {
        if (item.second && objects.count(item.first) && reachable.insert(item.first).second) {
            q.push(item.first);
        }
    }

    while (!q.empty()) {
        long long cur = q.front();
        q.pop();
        auto it = adj.find(cur);
        if (it == adj.end()) {
            continue;
        }
        for (const auto& next : it->second) {
            if (strongOnly && !next.second) {
                continue;
            }
            if (objects.count(next.first) && reachable.insert(next.first).second) {
                q.push(next.first);
            }
        }
    }

    for (auto it = objects.begin(); it != objects.end();) {
        if (!reachable.count(*it)) {
            roots.erase(*it);
            it = objects.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = edges.begin(); it != edges.end();) {
        const Edge& edge = it->second;
        if (!objects.count(edge.from) || !objects.count(edge.to)) {
            it = edges.erase(it);
        } else {
            ++it;
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int objectCount = inf.readInt(1, 200000, "O");
    inf.readSpace();
    int eventCount = inf.readInt(1, 200000, "E");
    inf.readEoln();

    unordered_set<long long> objects;
    unordered_map<long long, bool> roots;
    unordered_map<long long, Edge> edges;
    objects.reserve(400001);
    roots.reserve(400001);
    edges.reserve(400001);

    for (int i = 0; i < objectCount; ++i) {
        long long objectId = inf.readLong(1LL, 1000000000LL, "object_id");
        inf.readSpace();
        string isRoot = inf.readToken("ROOT|-", "is_root");
        inf.readEoln();

        ensuref(objects.insert(objectId).second, "duplicate initial object_id: %lld", objectId);
        roots[objectId] = isRoot == "ROOT";
    }

    int cleanupCount = 0;
    for (int i = 0; i < eventCount; ++i) {
        string line = inf.readLine("[A-Z0-9a-z=\\>\\-\\ ]{1,64}", "event_line");
        vector<string> tokens = splitSpaces(line);

        if (tokens[0] == "M" || tokens[0] == "m") {
            ensuref(tokens.size() == 1, "%s event has extra tokens", tokens[0].c_str());
            ++cleanupCount;
            ensuref(cleanupCount <= 20, "more than 20 M/m events");
            pruneObjects(objects, roots, edges, tokens[0] == "M");
        } else if (tokens[0] == "MADE") {
            ensuref(tokens.size() == 3, "MADE event must have 3 tokens");
            long long objectId = readIdToken(tokens[1], "object_id");
            ensuref(tokens[2] == "ROOT" || tokens[2] == "-", "invalid is_root in MADE: %s", tokens[2].c_str());
            ensuref(objects.insert(objectId).second, "MADE duplicates live object_id: %lld", objectId);
            roots[objectId] = tokens[2] == "ROOT";
        } else if (tokens[0] == "ADD") {
            ensuref(tokens.size() == 5, "ADD event must have 5 tokens");
            long long refId = readIdToken(tokens[1], "ref_id");
            long long from = readIdToken(tokens[2], "object_id_1");
            ensuref(tokens[3] == "->" || tokens[3] == "=>", "invalid relation token: %s", tokens[3].c_str());
            long long to = readIdToken(tokens[4], "object_id_2");
            ensuref(!edges.count(refId), "ADD duplicates live ref_id: %lld", refId);
            ensuref(objects.count(from), "ADD from object does not exist: %lld", from);
            ensuref(objects.count(to), "ADD to object does not exist: %lld", to);
            edges[refId] = {from, to, tokens[3] == "=>"};
        } else if (tokens[0] == "REMOVE") {
            ensuref(tokens.size() == 2, "REMOVE event must have 2 tokens");
            long long refId = readIdToken(tokens[1], "ref_id");
            ensuref(edges.erase(refId) == 1, "REMOVE references missing ref_id: %lld", refId);
        } else {
            ensuref(false, "unknown event type: %s", tokens[0].c_str());
        }
    }

    ensuref(cleanupCount >= 1, "at least one M/m event is required");
    inf.readEof();
}
