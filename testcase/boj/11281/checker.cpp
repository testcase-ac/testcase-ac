#include "testlib.h"
#include <vector>
#include <utility>
using namespace std;

int N, M;
vector<pair<int,int>> clauses;

struct Answer {
    bool sat;
    vector<int> assign;
};

// Reads an answer (either from jury or participant), checks its format and,
// if sat == 1, checks that the assignment satisfies all clauses.
// On stream == ouf, any error gives _wa.
// On stream == ans, any error gives _fail.
Answer readAns(InStream& stream) {
    Answer A;
    A.sat = stream.readInt(0, 1, "satisfiable flag");
    if (A.sat) {
        A.assign.resize(N);
        for (int i = 0; i < N; i++) {
            A.assign[i] = stream.readInt(0, 1, format("x[%d]", i+1).c_str());
        }
        // check all clauses
        for (int idx = 0; idx < M; idx++) {
            int u = clauses[idx].first;
            int v = clauses[idx].second;
            int pu = abs(u) - 1;
            int pv = abs(v) - 1;
            bool lu = (u > 0 ? (A.assign[pu] == 1) : (A.assign[pu] == 0));
            bool lv = (v > 0 ? (A.assign[pv] == 1) : (A.assign[pv] == 0));
            if (!(lu || lv)) {
                stream.quitf(_wa, "clause %d (%d %d) is not satisfied by the assignment", idx+1, u, v);
            }
        }
    }
    return A;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // read test data
    N = inf.readInt();
    M = inf.readInt();
    clauses.reserve(M);
    for (int i = 0; i < M; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        clauses.emplace_back(a, b);
    }

    // read jury and participant answers
    Answer jury = readAns(ans);
    Answer part = readAns(ouf);

    // compare satisfiability
    if (jury.sat != part.sat) {
        if (jury.sat && !part.sat)
            quitf(_wa, "declared unsatisfiable, but the formula is satisfiable");
        else
            quitf(_wa, "declared satisfiable, but the formula is unsatisfiable");
    }

    if (!jury.sat) {
        // both say unsatisfiable
        quitf(_ok, "unsatisfiable");
    } else {
        // both say satisfiable and part.assign was already checked
        quitf(_ok, "satisfiable");
    }
}
