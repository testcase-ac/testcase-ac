#include "testlib.h"
#include <vector>
#include <utility>
using namespace std;

int N, M;
vector<pair<int,int>> clauses;

// Reads an answer from stream (either ouf or ans), checks correctness,
// and returns {possible, assignment}. If the stream is ans and it's wrong,
// quits with _fail; if it's ouf and wrong, quits with _wa.
pair<bool, vector<int>> readAns(InStream& stream) {
    int possible = stream.readInt(0, 1, "possible");
    vector<int> a;
    if (!possible) {
        // unsatisfiable
        return {false, a};
    }
    // satisfiable: read assignment
    a.resize(N);
    for (int i = 0; i < N; i++) {
        a[i] = stream.readInt(0, 1, format("x_%d", i+1).c_str());
    }
    // check all clauses
    for (int k = 0; k < M; k++) {
        int u = clauses[k].first;
        int v = clauses[k].second;
        bool lu = (u > 0 ? a[abs(u)-1] == 1 : a[abs(u)-1] == 0);
        bool lv = (v > 0 ? a[abs(v)-1] == 1 : a[abs(v)-1] == 0);
        if (!lu && !lv) {
            stream.quitf(_wa, 
                "clause %d (%s) is not satisfied by the assignment", 
                k+1, format("(%d %d)", u, v).c_str());
        }
    }
    return {true, a};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    N = inf.readInt();
    M = inf.readInt();
    clauses.reserve(M);
    for (int i = 0; i < M; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        clauses.emplace_back(u, v);
    }
    // Read jury and participant answers
    auto jans = readAns(ans);
    auto pans = readAns(ouf);

    // Compare
    if (jans.first) {
        // Jury says SAT
        if (!pans.first)
            quitf(_wa, "participant reports UNSAT but a solution exists");
        else
            quitf(_ok, "satisfiable assignment");
    } else {
        // Jury says UNSAT
        if (pans.first)
            quitf(_wa, "participant reports SAT but no solution exists");
        else
            quitf(_ok, "correctly reports UNSAT");
    }
    return 0;
}
