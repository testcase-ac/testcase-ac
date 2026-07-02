#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
};

struct Route {
    vector<int> ids;
};

struct Claim {
    vector<bool> possible;
};

int T;
vector<int> roadCounts;
vector<vector<Edge> > cases;
const vector<Edge>* currentEdges;

int edgeStart(int signedId) {
    const Edge& edge = (*currentEdges)[abs(signedId)];
    return signedId > 0 ? edge.u : edge.v;
}

int edgeEnd(int signedId) {
    const Edge& edge = (*currentEdges)[abs(signedId)];
    return signedId > 0 ? edge.v : edge.u;
}

Route readRoute(InStream& stream, int testCase, int routeIndex, int m) {
    string routeName = format("case %d route %d", testCase, routeIndex).c_str();
    int count = stream.readInt(0, m, format("%s edge count", routeName.c_str()).c_str());
    Route route;
    route.ids.reserve(count);

    for (int i = 0; i < count; ++i) {
        int signedId = stream.readInt(-m, m, format("%s edge[%d]", routeName.c_str(), i + 1).c_str());
        if (signedId == 0) {
            stream.quitf(_wa, "%s contains edge id 0 at position %d", routeName.c_str(), i + 1);
        }
        route.ids.push_back(signedId);
    }

    return route;
}

void validateWalk(InStream& stream, const Route& route, int testCase, int routeIndex) {
    for (int i = 1; i < (int)route.ids.size(); ++i) {
        int previousEnd = edgeEnd(route.ids[i - 1]);
        int currentStart = edgeStart(route.ids[i]);
        if (previousEnd != currentStart) {
            stream.quitf(_wa,
                         "case %d route %d is not continuous between positions %d and %d: %d != %d",
                         testCase,
                         routeIndex,
                         i,
                         i + 1,
                         previousEnd,
                         currentStart);
        }
    }
}

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.possible.reserve(T);

    for (int tc = 1; tc <= T; ++tc) {
        int m = roadCounts[tc];
        currentEdges = &cases[tc];

        Route route1 = readRoute(stream, tc, 1, m);
        Route route2 = readRoute(stream, tc, 2, m);

        bool saysImpossible = route1.ids.empty() || route2.ids.empty();
        if (saysImpossible) {
            if (!route1.ids.empty() || !route2.ids.empty()) {
                stream.quitf(_wa, "case %d has exactly one empty route", tc);
            }
            claim.possible.push_back(false);
            continue;
        }

        vector<int> used(m + 1, 0);
        for (int routeIndex = 1; routeIndex <= 2; ++routeIndex) {
            const Route& route = routeIndex == 1 ? route1 : route2;
            validateWalk(stream, route, tc, routeIndex);
            for (int i = 0; i < (int)route.ids.size(); ++i) {
                int id = abs(route.ids[i]);
                if (used[id] != 0) {
                    stream.quitf(_wa,
                                 "case %d road %d is used more than once, first in route %d and again in route %d",
                                 tc,
                                 id,
                                 used[id],
                                 routeIndex);
                }
                used[id] = routeIndex;
            }
        }

        for (int id = 1; id <= m; ++id) {
            if (used[id] == 0) {
                stream.quitf(_wa, "case %d road %d is not used", tc, id);
            }
        }
        claim.possible.push_back(true);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d test cases", T);
    }
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    T = inf.readInt();
    roadCounts.assign(T + 1, 0);
    cases.assign(T + 1, vector<Edge>());

    for (int tc = 1; tc <= T; ++tc) {
        int n = inf.readInt();
        int m = inf.readInt();
        roadCounts[tc] = m;

        cases[tc].assign(m + 1, {0, 0});
        vector<int> first(m + 1), second(m + 1);
        for (int i = 1; i <= m; ++i) {
            first[i] = inf.readInt();
        }
        for (int i = 1; i <= m; ++i) {
            second[i] = inf.readInt();
            cases[tc][i] = {first[i], second[i]};
        }

        (void)n;
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    for (int tc = 1; tc <= T; ++tc) {
        bool juryPossible = jury.possible[tc - 1];
        bool participantPossible = participant.possible[tc - 1];
        if (!juryPossible && participantPossible) {
            quitf(_fail, "case %d: participant provided a valid decomposition while jury reports impossible", tc);
        }
        if (juryPossible && !participantPossible) {
            quitf(_wa, "case %d: jury provides a valid decomposition but participant reports impossible", tc);
        }
    }

    quitf(_ok, "valid decomposition");
}
