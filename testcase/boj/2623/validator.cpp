#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N (number of singers) and M (number of assistant PDs)
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // For each assistant PD, read their sequence
    for (int i = 0; i < M; i++) {
        // k = number of singers this PD has ordered
        int k = inf.readInt(1, N, "k_i");
        if (k > 0) {
            inf.readSpace();
            // Read exactly k singer IDs
            for (int j = 0; j < k; j++) {
                if (j > 0) inf.readSpace();
                inf.readInt(1, N, "s_i_j");
            }
        }
        // End of this PD's line
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
