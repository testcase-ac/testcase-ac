#include "testlib.h"
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readEoln();

    for (int theorem = 0; theorem < n; ++theorem) {
        int proofCount = inf.readInt(1, 10, "p_i");
        inf.readEoln();

        for (int proof = 0; proof < proofCount; ++proof) {
            int length = inf.readInt(0, 1000000, "l");
            inf.readSpace();
            int dependencyCount = inf.readInt(0, n - 1, "k");

            set<int> dependencies;
            for (int j = 0; j < dependencyCount; ++j) {
                inf.readSpace();
                int dependency = inf.readInt(0, n - 1, "d_j");
                ensuref(dependency != theorem,
                        "proof %d for theorem %d depends on itself",
                        proof + 1, theorem);
                ensuref(dependencies.insert(dependency).second,
                        "proof %d for theorem %d repeats dependency %d",
                        proof + 1, theorem, dependency);
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
