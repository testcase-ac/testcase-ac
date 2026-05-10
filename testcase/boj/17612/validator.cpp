#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "k");
    inf.readEoln();

    // Validate each customer's id and w, and check distinct ids
    const int MAX_ID = 1000000;
    vector<char> seen(MAX_ID+1, 0);
    for (int i = 0; i < N; i++) {
        int id = inf.readInt(1, MAX_ID, "id_i");
        inf.readSpace();
        int w = inf.readInt(1, 20, "w_i");
        inf.readEoln();

        ensuref(!seen[id],
                "Duplicate member ID at line %d: %d", i+2, id);
        seen[id] = 1;
    }

    inf.readEof();
    return 0;
}
