#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of participants
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // For each participant, read their pokemon combination
    for (int i = 0; i < N; i++) {
        // c_i: number of pokemons
        int c = inf.readInt(1, 17, "c_i");
        inf.readSpace();

        // Read the species list p_1 ... p_c
        vector<int> p;
        p.reserve(c);
        for (int j = 0; j < c; j++) {
            int x = inf.readInt(1, 17, "p_ij");
            p.push_back(x);
            if (j + 1 < c) {
                inf.readSpace();
            }
        }
        inf.readEoln();

        // Ensure strictly increasing species numbers
        for (int j = 0; j + 1 < c; j++) {
            ensuref(p[j] < p[j+1],
                    "Species numbers not strictly increasing for participant %d at positions %d and %d: %d >= %d",
                    i+1, j+1, j+2, p[j], p[j+1]);
        }
    }

    inf.readEof();
    return 0;
}
