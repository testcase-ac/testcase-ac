#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    vector<int> firstRound = inf.readInts(n, -10000, 10000, "first_round");
    inf.readEoln();

    vector<int> secondRound = inf.readInts(n, -10000, 10000, "second_round");
    inf.readEoln();

    inf.readEof();
}
