#include "testlib.h"

#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

namespace {

bool canAssignOrder(const vector<int>& lowerBound,
                    const vector<vector<char>>& requiredAtPosition) {
    int n = static_cast<int>(lowerBound.size());
    vector<vector<int>> adj(n);
    for (int pos = 0; pos < n; ++pos) {
        for (int horse = 0; horse < n; ++horse) {
            if (lowerBound[horse] <= pos + 1 && requiredAtPosition[pos][horse]) {
                adj[pos].push_back(horse);
            }
        }
    }

    vector<int> matchHorse(n, -1), matchPos(n, -1), dist(n);

    auto bfs = [&]() {
        queue<int> q;
        bool foundFreeHorse = false;
        for (int pos = 0; pos < n; ++pos) {
            if (matchPos[pos] == -1) {
                dist[pos] = 0;
                q.push(pos);
            } else {
                dist[pos] = -1;
            }
        }

        while (!q.empty()) {
            int pos = q.front();
            q.pop();
            for (int horse : adj[pos]) {
                int nextPos = matchHorse[horse];
                if (nextPos == -1) {
                    foundFreeHorse = true;
                } else if (dist[nextPos] == -1) {
                    dist[nextPos] = dist[pos] + 1;
                    q.push(nextPos);
                }
            }
        }
        return foundFreeHorse;
    };

    auto dfs = [&](auto&& self, int pos) -> bool {
        for (int horse : adj[pos]) {
            int nextPos = matchHorse[horse];
            if (nextPos == -1 ||
                (dist[nextPos] == dist[pos] + 1 && self(self, nextPos))) {
                matchPos[pos] = horse;
                matchHorse[horse] = pos;
                return true;
            }
        }
        dist[pos] = -1;
        return false;
    };

    int matched = 0;
    while (bfs()) {
        for (int pos = 0; pos < n; ++pos) {
            if (matchPos[pos] == -1 && dfs(dfs, pos)) {
                ++matched;
            }
        }
    }

    return matched == n;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300, "N");
    inf.readEoln();

    unordered_map<string, int> horseIndex;
    vector<string> horses(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        horses[i] = inf.readToken("[a-z]{1,3}", "horse_name");
        ensuref(horseIndex.emplace(horses[i], i).second,
                "duplicate horse name on horse list: %s", horses[i].c_str());
    }
    inf.readEoln();

    int r = inf.readInt(1, 100000, "R");
    inf.readEoln();

    vector<int> lowerBound(n, 1);
    vector<vector<char>> requiredAtPosition(n, vector<char>(n, true));
    vector<char> hasRaceAtPosition(n, false);
    long long totalParticipants = 0;

    for (int race = 1; race <= r; ++race) {
        int m = inf.readInt(2, n, "M_i");
        inf.readSpace();
        int w = inf.readInt(1, n, "W_i");

        totalParticipants += m;
        ensuref(totalParticipants <= 100000,
                "sum of M_i exceeds 100000 at race %d", race);

        vector<char> seenInRace(n, false), participates(n, false);
        for (int j = 0; j < m; ++j) {
            inf.readSpace();
            string name = inf.readToken("[a-z]{1,3}", "participant_name");
            auto it = horseIndex.find(name);
            ensuref(it != horseIndex.end(),
                    "unknown horse name in race %d: %s", race, name.c_str());
            int idx = it->second;
            ensuref(!seenInRace[idx],
                    "duplicate horse name in race %d: %s", race, name.c_str());
            seenInRace[idx] = true;
            participates[idx] = true;
            lowerBound[idx] = max(lowerBound[idx], w);
        }
        inf.readEoln();

        if (!hasRaceAtPosition[w - 1]) {
            hasRaceAtPosition[w - 1] = true;
            requiredAtPosition[w - 1] = participates;
        } else {
            for (int i = 0; i < n; ++i) {
                requiredAtPosition[w - 1][i] =
                    requiredAtPosition[w - 1][i] && participates[i];
            }
        }
    }

    ensuref(canAssignOrder(lowerBound, requiredAtPosition),
            "race notes do not admit any full race order");

    inf.readEof();
}
