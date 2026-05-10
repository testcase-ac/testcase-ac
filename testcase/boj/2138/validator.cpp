#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of switches/bulbs
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read current state string: exactly N chars, each '0' or '1', no spaces
    string cur = inf.readToken("[01]+", "current_state");
    inf.readEoln();
    ensuref((int)cur.size() == N,
            "current_state length must be exactly N=%d, but is %d",
            N, (int)cur.size());

    // Read target state string: exactly N chars, each '0' or '1', no spaces
    string target = inf.readToken("[01]+", "target_state");
    inf.readEoln();
    ensuref((int)target.size() == N,
            "target_state length must be exactly N=%d, but is %d",
            N, (int)target.size());

    inf.readEof();
}
