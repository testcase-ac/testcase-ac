#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of observations
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read each observation: cow ID and position
    for (int i = 0; i < N; i++) {
        // cow ID: 1 to 10
        string cow_name = "cow_id_" + to_string(i+1);
        int cow = inf.readInt(1, 10, cow_name.c_str());

        inf.readSpace();

        // position: 0 or 1
        string pos_name = "pos_" + to_string(i+1);
        int pos = inf.readInt(0, 1, pos_name.c_str());

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
