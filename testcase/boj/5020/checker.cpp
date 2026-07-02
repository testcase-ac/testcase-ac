#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;

int parseSoldierToken(InStream& stream, const string& token, int groupIndex, int position) {
    char* end = nullptr;
    errno = 0;
    long value = strtol(token.c_str(), &end, 10);
    if (errno != 0 || *end != '\0') {
        stream.quitf(_wa,
                     "group %d contains malformed soldier token at position %d: %s",
                     groupIndex,
                     position,
                     token.c_str());
    }
    if (value < 1 || value > n) {
        stream.quitf(_wa,
                     "group %d contains soldier %ld outside range [1, %d]",
                     groupIndex,
                     value,
                     n);
    }
    return static_cast<int>(value);
}

struct Answer {
    int groups;
};

Answer readAnswer(InStream& stream) {
    int k = stream.readInt(1, n, "number of groups");
    stream.readEoln();

    vector<int> groupOf(n + 1, 0);
    vector<vector<int>> groups(k + 1);
    for (int groupIndex = 1; groupIndex <= k; ++groupIndex) {
        string line = stream.readLine();
        istringstream iss(line);
        string token;
        int position = 0;
        while (iss >> token) {
            ++position;
            int soldier = parseSoldierToken(stream, token, groupIndex, position);
            if (groupOf[soldier] != 0) {
                stream.quitf(_wa,
                             "soldier %d appears in both group %d and group %d",
                             soldier,
                             groupOf[soldier],
                             groupIndex);
            }
            groupOf[soldier] = groupIndex;
            groups[groupIndex].push_back(soldier);
        }
        if (groups[groupIndex].empty()) {
            stream.quitf(_wa, "group %d is empty", groupIndex);
        }
    }
    stream.readEof();

    for (int soldier = 1; soldier <= n; ++soldier) {
        if (groupOf[soldier] == 0) {
            stream.quitf(_wa, "soldier %d is missing from all groups", soldier);
        }
    }

    for (int soldier = 1; soldier <= n; ++soldier) {
        int enemiesInGroup = 0;
        for (int enemy : adj[soldier]) {
            if (groupOf[enemy] == groupOf[soldier]) {
                ++enemiesInGroup;
            }
        }
        if (enemiesInGroup > 1) {
            stream.quitf(_wa,
                         "soldier %d has %d enemies in group %d",
                         soldier,
                         enemiesInGroup,
                         groupOf[soldier]);
        }
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    adj.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.groups < jury.groups) {
        quitf(_fail,
              "participant found fewer valid groups: jury=%d participant=%d",
              jury.groups,
              participant.groups);
    }
    if (participant.groups > jury.groups) {
        quitf(_wa,
              "participant used too many groups: jury=%d participant=%d",
              jury.groups,
              participant.groups);
    }

    quitf(_ok, "valid division into %d groups", participant.groups);
}
