#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200, "M");
    inf.readEoln();

    // 2. Read N energy states, all distinct, 1..1_000_000
    vector<int> energy_states;
    set<int> energy_set;
    for (int i = 0; i < N; ++i) {
        int e = inf.readInt(1, 1000000, "energy_state");
        inf.readEoln();
        ensuref(energy_set.count(e) == 0, "Duplicate energy state at line %d: %d", i+2, e);
        energy_states.push_back(e);
        energy_set.insert(e);
    }

    // 3. Read M proton energies, 1..1_000_000
    vector<int> proton_energies;
    for (int i = 0; i < M; ++i) {
        int p = inf.readInt(1, 1000000, "proton_energy");
        inf.readEoln();
        proton_energies.push_back(p);
    }

    inf.readEof();
}
