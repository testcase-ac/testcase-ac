#include "testlib.h"

#include <algorithm>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Fraction {
    __int128 num = 0;
    __int128 den = 1;
};

struct Edge {
    int to;
    long long num;
    long long den;
};

__int128 abs128(__int128 x) {
    return x < 0 ? -x : x;
}

__int128 gcd128(__int128 a, __int128 b) {
    a = abs128(a);
    b = abs128(b);
    while (b != 0) {
        __int128 r = a % b;
        a = b;
        b = r;
    }
    return a;
}

Fraction normalize(__int128 num, __int128 den) {
    ensuref(den > 0, "fraction denominator must be positive");
    ensuref(num > 0, "fraction numerator must be positive");
    __int128 g = gcd128(num, den);
    return {num / g, den / g};
}

bool sameFraction(const Fraction& a, const Fraction& b) {
    return a.num == b.num && a.den == b.den;
}

bool sameExcess(__int128 lhsNum, __int128 lhsDen, __int128 rhsNum, __int128 rhsDen) {
    return lhsNum * rhsDen == rhsNum * lhsDen;
}

bool lessExcess(__int128 lhsNum, __int128 lhsDen, __int128 rhsNum, __int128 rhsDen) {
    return lhsNum * rhsDen < rhsNum * lhsDen;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int caseNo = 1;; ++caseNo) {
        int n = inf.readInt(0, 28, "n");
        inf.readEoln();
        if (n == 0) {
            inf.readEof();
            break;
        }
        setTestCase(caseNo);

        map<string, int> currencyId;
        vector<string> currencyNames;
        vector<vector<Edge>> graph;

        auto getCurrencyId = [&](const string& name) -> int {
            auto it = currencyId.find(name);
            if (it != currencyId.end()) return it->second;
            int id = (int)currencyNames.size();
            currencyId[name] = id;
            currencyNames.push_back(name);
            graph.push_back({});
            ensuref((int)currencyNames.size() <= 8, "more than 8 distinct currency names");
            return id;
        };

        set<pair<int, int>> seenPairs;
        for (int i = 0; i < n; ++i) {
            int val1 = inf.readInt(1, 30, "val_1");
            inf.readSpace();
            string name1 = inf.readToken("[A-Za-z]{1,10}", "name_1");
            inf.readSpace();
            string equals = inf.readToken("=", "equals");
            (void)equals;
            inf.readSpace();
            int val2 = inf.readInt(1, 30, "val_2");
            inf.readSpace();
            string name2 = inf.readToken("[A-Za-z]{1,10}", "name_2");
            inf.readEoln();

            int a = getCurrencyId(name1);
            int b = getCurrencyId(name2);
            ensuref(a != b, "exchange rate %d uses the same currency twice", i + 1);
            auto normalizedPair = minmax(a, b);
            ensuref(seenPairs.insert(normalizedPair).second,
                    "currency pair appears more than once at exchange rate %d", i + 1);

            graph[a].push_back({b, val2, val1});
            graph[b].push_back({a, val1, val2});
        }

        int requestedValue = inf.readInt(1, 100000, "val");
        inf.readSpace();
        string requestedName = inf.readToken("[A-Za-z]{1,10}", "name");
        inf.readEoln();
        int requestedId = getCurrencyId(requestedName);

        int currencyCount = (int)currencyNames.size();
        vector<bool> visited(currencyCount, false);
        vector<Fraction> relative(currencyCount);

        for (int start = 0; start < currencyCount; ++start) {
            if (visited[start]) continue;
            visited[start] = true;
            relative[start] = {1, 1};
            queue<int> q;
            q.push(start);

            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                for (const Edge& edge : graph[cur]) {
                    Fraction next = normalize(relative[cur].num * edge.num,
                                              relative[cur].den * edge.den);
                    if (!visited[edge.to]) {
                        visited[edge.to] = true;
                        relative[edge.to] = next;
                        q.push(edge.to);
                    } else {
                        ensuref(sameFraction(relative[edge.to], next),
                                "inconsistent exchange rates in case %d", caseNo);
                    }
                }
            }
        }

        vector<bool> reachable(currencyCount, false);
        vector<Fraction> fromRequested(currencyCount);
        reachable[requestedId] = true;
        fromRequested[requestedId] = {1, 1};
        queue<int> q;
        q.push(requestedId);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (const Edge& edge : graph[cur]) {
                Fraction next = normalize(fromRequested[cur].num * edge.num,
                                          fromRequested[cur].den * edge.den);
                if (!reachable[edge.to]) {
                    reachable[edge.to] = true;
                    fromRequested[edge.to] = next;
                    q.push(edge.to);
                }
            }
        }

        bool hasBest = false;
        bool tiedBest = false;
        __int128 bestExcessNum = 0;
        __int128 bestExcessDen = 1;
        for (int id = 0; id < currencyCount; ++id) {
            if (id == requestedId || !reachable[id]) continue;
            Fraction rate = fromRequested[id];
            __int128 needed = ((__int128)requestedValue * rate.num + rate.den - 1) / rate.den;
            if (needed > 100000) continue;

            __int128 excessNum = needed * rate.den - (__int128)requestedValue * rate.num;
            __int128 excessDen = rate.num;
            ensuref(excessNum >= 0, "negative computed excess");

            if (!hasBest || lessExcess(excessNum, excessDen, bestExcessNum, bestExcessDen)) {
                hasBest = true;
                tiedBest = false;
                bestExcessNum = excessNum;
                bestExcessDen = excessDen;
            } else if (sameExcess(excessNum, excessDen, bestExcessNum, bestExcessDen)) {
                tiedBest = true;
            }
        }

        ensuref(hasBest, "case %d has no substitute currency within stock limit", caseNo);
        ensuref(!tiedBest, "case %d does not have a unique best answer", caseNo);
    }
}
