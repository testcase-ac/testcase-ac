#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N and M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Second line: number of truth-knowers and their ids
    int tcnt = inf.readInt(0, 50, "truth_count");
    vector<int> truth(tcnt);
    for (int i = 0; i < tcnt; i++) {
        inf.readSpace();
        truth[i] = inf.readInt(1, N, "truth_id");
    }
    inf.readEoln();

    // Next M lines: each party's attendee count and their ids
    for (int i = 0; i < M; i++) {
        int pcnt = inf.readInt(1, 50, "party_size");
        // Although party_size ≤ 50 by statement, it must also be ≤ N logically
        ensuref(pcnt <= N, "party_size (%d) exceeds number of people N (%d) at party %d", pcnt, N, i+1);
        vector<int> party(pcnt);
        for (int j = 0; j < pcnt; j++) {
            inf.readSpace();
            party[j] = inf.readInt(1, N, "party_id");
        }
        inf.readEoln();
        // Optional: check duplicates in the same party
        // (Not strictly required by statement, but usually lists are unique)
        for (int x = 0; x < pcnt; x++) {
            for (int y = x+1; y < pcnt; y++) {
                ensuref(party[x] != party[y],
                        "duplicate attendee %d in party %d", party[x], i+1);
            }
        }
    }

    inf.readEof();
    return 0;
}
