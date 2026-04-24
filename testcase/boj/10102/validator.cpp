#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of judges V: 1 ≤ V ≤ 15
    int V = inf.readInt(1, 15, "V");
    inf.readEoln();

    // Read the votes line: exactly V characters, each 'A' or 'B'
    string votes = inf.readToken("[AB]{1,15}", "votes");
    ensuref((int)votes.size() == V,
            "Length of votes (%d) must be exactly V (%d)", (int)votes.size(), V);
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
