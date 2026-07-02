#include "testlib.h"

#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int n, m;
vector<pair<int, int>> edges;

struct Answer {
    int teams;
};

Answer readAns(InStream& stream) {
    int teams = stream.readInt(0, n, "number of teams");
    stream.readEoln();

    vector<int> assignedTeam(n + 1, -1);
    int assignedCount = 0;

    for (int team = 0; team < teams; ++team) {
        string line = stream.readLine();
        stringstream ss(line);
        int player;
        int teamSize = 0;

        while (ss >> player) {
            if (player < 1 || player > n) {
                stream.quitf(_wa, "player %d in team %d is outside [1, %d]",
                             player, team + 1, n);
            }
            if (assignedTeam[player] != -1) {
                stream.quitf(_wa, "player %d appears in both team %d and team %d",
                             player, assignedTeam[player] + 1, team + 1);
            }
            assignedTeam[player] = team;
            ++assignedCount;
            ++teamSize;
        }

        if (ss.fail() && !ss.eof()) {
            stream.quitf(_wa, "team %d contains a malformed player number", team + 1);
        }
        if (teamSize == 0) {
            stream.quitf(_wa, "team %d is empty", team + 1);
        }
    }

    stream.readEof();

    if (assignedCount != n) {
        for (int player = 1; player <= n; ++player) {
            if (assignedTeam[player] == -1) {
                stream.quitf(_wa, "player %d is not assigned to any team", player);
            }
        }
    }

    for (const auto& edge : edges) {
        int a = edge.first;
        int b = edge.second;
        if (assignedTeam[a] == assignedTeam[b]) {
            stream.quitf(_wa, "players %d and %d dislike each other but are both in team %d",
                         a, b, assignedTeam[a] + 1);
        }
    }

    return {teams};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges.push_back({a, b});
    }

    Answer jury = readAns(ans);
    Answer participant = readAns(ouf);

    if (participant.teams < jury.teams) {
        quitf(_fail, "participant found a valid partition with fewer teams: jury=%d participant=%d",
              jury.teams, participant.teams);
    }
    if (participant.teams > jury.teams) {
        quitf(_wa, "participant used too many teams: jury=%d participant=%d",
              jury.teams, participant.teams);
    }

    quitf(_ok, "valid partition with %d teams", participant.teams);
}
