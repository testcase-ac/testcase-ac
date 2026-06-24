#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int remaining;
    int initialPriority;
};

int T;
vector<int> scheduleIds;
vector<char> selectedId;

struct Claim {
    vector<Process> processes;
};

Claim readClaim(InStream& stream) {
    int n = stream.readInt(1, 1000000, "N");
    stream.readEoln();

    vector<Process> processes(n);
    int previousId = 0;
    long long totalTime = 0;
    for (int i = 0; i < n; ++i) {
        int id = stream.readInt(1, 1000000, format("A_%d", i + 1).c_str());
        int remaining = stream.readInt(1, 1000000, format("B_%d", i + 1).c_str());
        int priority = stream.readInt(1, 1000000, format("C_%d", i + 1).c_str());
        stream.readEoln();

        if (id <= previousId) {
            stream.quitf(_wa, "process ids must be strictly increasing: A_%d=%d after %d",
                         i + 1, id, previousId);
        }
        if (!selectedId[id]) {
            stream.quitf(_wa, "process id %d does not appear in the requested schedule", id);
        }

        processes[i] = {id, remaining, priority};
        previousId = id;
        totalTime += remaining;
        if (totalTime > T) {
            stream.quitf(_wa, "total running time exceeds T: total=%lld T=%d", totalTime, T);
        }
    }
    stream.readEof();

    if (totalTime != T) {
        stream.quitf(_wa, "total running time must equal T: total=%lld T=%d", totalTime, T);
    }

    vector<int> indexById(1000001, -1);
    for (int i = 0; i < n; ++i) {
        indexById[processes[i].id] = i;
    }

    for (int i = 0; i < T; ++i) {
        int id = scheduleIds[i];
        if (indexById[id] == -1) {
            stream.quitf(_wa, "scheduled id %d at second %d is missing from output", id, i + 1);
        }
    }

    using State = tuple<int, int, int>;
    priority_queue<State> pq;
    vector<int> remaining(n);
    vector<int> executed(n, 0);
    for (int i = 0; i < n; ++i) {
        remaining[i] = processes[i].remaining;
        pq.emplace(processes[i].initialPriority, -processes[i].id, i);
    }

    for (int second = 1; second <= T; ++second) {
        if (pq.empty()) {
            stream.quitf(_wa, "all processes finished before second %d", second);
        }

        auto [key, negativeId, index] = pq.top();
        pq.pop();

        int expectedId = scheduleIds[second - 1];
        int actualId = -negativeId;
        if (actualId != expectedId) {
            stream.quitf(_wa,
                         "at second %d scheduler selects id %d, expected id %d",
                         second, actualId, expectedId);
        }

        --remaining[index];
        ++executed[index];
        if (remaining[index] > 0) {
            pq.emplace(processes[index].initialPriority - executed[index],
                       -processes[index].id,
                       index);
        }
    }

    if (!pq.empty()) {
        stream.quitf(_wa, "some processes remain after T seconds");
    }

    return {processes};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    T = inf.readInt(1, 100000, "T");
    scheduleIds.resize(T);
    selectedId.assign(1000001, 0);
    for (int i = 0; i < T; ++i) {
        scheduleIds[i] = inf.readInt(1, 1000000, format("schedule[%d]", i + 1).c_str());
        selectedId[scheduleIds[i]] = 1;
    }

    readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok, "valid schedule reconstruction with %d processes",
          static_cast<int>(participant.processes.size()));
}
