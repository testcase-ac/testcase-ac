#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    string initial = inf.readToken("[01]{1,1000000}", "initial");
    ensuref((int)initial.size() == n, "initial length is %d, expected %d",
            (int)initial.size(), n);
    inf.readEoln();

    string target = inf.readToken("[01]{1,1000000}", "target");
    ensuref((int)target.size() == n, "target length is %d, expected %d",
            (int)target.size(), n);
    inf.readEoln();

    inf.readEof();
}
