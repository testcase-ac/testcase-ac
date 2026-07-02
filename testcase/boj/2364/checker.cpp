#include "testlib.h"

#include <algorithm>
#include <map>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int INF = 1'000'000'000;

int regionCount;
int townCount;
int memberCount;
vector<int> members;
vector<vector<int>> townRegions;
vector<vector<int>> regionGraph;

struct Answer {
    int claimedCost;
    int region;
    int actualCost;
};

int crossingSumForRegion(int targetRegion) {
    vector<int> dist(regionCount + 1, INF);
    queue<int> q;
    dist[targetRegion] = 0;
    q.push(targetRegion);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int next : regionGraph[current]) {
            if (dist[next] != INF) {
                continue;
            }
            dist[next] = dist[current] + 1;
            q.push(next);
        }
    }

    int total = 0;
    for (int memberTown : members) {
        int best = INF;
        for (int region : townRegions[memberTown]) {
            best = min(best, dist[region]);
        }
        if (best == INF) {
            quitf(_fail, "member town %d is not connected to region %d", memberTown, targetRegion);
        }
        total += best;
    }
    return total;
}

Answer readAnswer(InStream& stream) {
    int claimedCost = stream.readInt(0, INF, "minimal crossing-sum");
    int region = stream.readInt(1, regionCount, "optimal region");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after region");
    }

    int actualCost = crossingSumForRegion(region);
    if (claimedCost != actualCost) {
        stream.quitf(_wa,
                     "claimed crossing-sum %d does not match region %d crossing-sum %d",
                     claimedCost,
                     region,
                     actualCost);
    }
    return {claimedCost, region, actualCost};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    regionCount = inf.readInt();
    townCount = inf.readInt();
    memberCount = inf.readInt();

    members.resize(memberCount);
    for (int i = 0; i < memberCount; ++i) {
        members[i] = inf.readInt();
    }

    townRegions.assign(townCount + 1, {});
    regionGraph.assign(regionCount + 1, {});
    map<pair<int, int>, vector<int>> edgeRegions;

    for (int region = 1; region <= regionCount; ++region) {
        int borderSize = inf.readInt();
        vector<int> towns(borderSize);
        for (int i = 0; i < borderSize; ++i) {
            towns[i] = inf.readInt();
            townRegions[towns[i]].push_back(region);
        }

        for (int i = 0; i < borderSize; ++i) {
            int a = towns[i];
            int b = towns[(i + 1) % borderSize];
            edgeRegions[minmax(a, b)].push_back(region);
        }
    }

    for (const auto& entry : edgeRegions) {
        const vector<int>& regions = entry.second;
        if (regions.size() != 2) {
            quitf(_fail,
                  "wall (%d, %d) appears on %d region borders",
                  entry.first.first,
                  entry.first.second,
                  (int)regions.size());
        }
        int a = regions[0];
        int b = regions[1];
        regionGraph[a].push_back(b);
        regionGraph[b].push_back(a);
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.actualCost < jury.actualCost) {
        quitf(_fail,
              "participant found better crossing-sum: jury=%d participant=%d",
              jury.actualCost,
              participant.actualCost);
    }
    if (participant.actualCost > jury.actualCost) {
        quitf(_wa,
              "jury has better crossing-sum: jury=%d participant=%d",
              jury.actualCost,
              participant.actualCost);
    }

    quitf(_ok, "crossing-sum=%d region=%d", participant.actualCost, participant.region);
}
