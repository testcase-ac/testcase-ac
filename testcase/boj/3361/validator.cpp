#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string orientations = inf.readToken("[LR]{1,100000}", "orientations");
    ensuref(!orientations.empty(), "orientations must not be empty");
    inf.readEoln();
    inf.readEof();
}
