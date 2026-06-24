#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int n, m;
vector<int> initialAssignment;
vector<pair<int, int>> queries;

struct Answer {
    vector<long long> value;
};

Answer readAnswer(InStream& stream) {
    Answer answer;
    answer.value.reserve(m);

    for (int qi = 0; qi < m; ++qi) {
        int l = queries[qi].first;
        int r = queries[qi].second;

        vector<int> assignment(n + 1);
        vector<int> seen(n + 1, 0);
        for (int house = 1; house <= n; ++house) {
            assignment[house] = stream.readInt(1, n, format("A[%d][%d]", qi + 1, house).c_str());
            if (seen[assignment[house]]) {
                stream.quitf(_wa,
                             "query %d output is not a permutation: person %d appears more than once",
                             qi + 1,
                             assignment[house]);
            }
            seen[assignment[house]] = 1;
        }

        vector<int> usedMovedPerson(r - l + 1, 0);
        for (int house = 1; house <= n; ++house) {
            bool wasMovableHouse = l <= initialAssignment[house] && initialAssignment[house] <= r;
            bool hasMovedPerson = l <= assignment[house] && assignment[house] <= r;

            if (wasMovableHouse != hasMovedPerson) {
                stream.quitf(_wa,
                             "query %d house %d has person %d, but movable-person membership must match initial person %d",
                             qi + 1,
                             house,
                             assignment[house],
                             initialAssignment[house]);
            }
            if (!wasMovableHouse && assignment[house] != initialAssignment[house]) {
                stream.quitf(_wa,
                             "query %d house %d changed fixed person from %d to %d",
                             qi + 1,
                             house,
                             initialAssignment[house],
                             assignment[house]);
            }
            if (hasMovedPerson) {
                usedMovedPerson[assignment[house] - l] = 1;
            }
        }

        for (int person = l; person <= r; ++person) {
            if (!usedMovedPerson[person - l]) {
                stream.quitf(_wa, "query %d missing movable person %d", qi + 1, person);
            }
        }

        long long value = 0;
        for (int house = 1; house <= n; ++house) {
            value += 1LL * house * assignment[house];
        }
        answer.value.push_back(value);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d query answers", m);
    }
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initialAssignment.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        initialAssignment[i] = inf.readInt();
    }

    m = inf.readInt();
    queries.reserve(m);
    for (int i = 0; i < m; ++i) {
        int l = inf.readInt();
        int r = inf.readInt();
        queries.push_back({l, r});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    for (int qi = 0; qi < m; ++qi) {
        if (participant.value[qi] < jury.value[qi]) {
            quitf(_wa,
                  "query %d has lower objective than jury: jury=%lld participant=%lld",
                  qi + 1,
                  jury.value[qi],
                  participant.value[qi]);
        }
        if (participant.value[qi] > jury.value[qi]) {
            quitf(_fail,
                  "query %d participant found better objective than jury: jury=%lld participant=%lld",
                  qi + 1,
                  jury.value[qi],
                  participant.value[qi]);
        }
    }

    quitf(_ok, "all %d query answers match the jury objective", m);
}
