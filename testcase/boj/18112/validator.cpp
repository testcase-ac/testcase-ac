#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string start = inf.readToken("[01]{1,10}", "start");
    ensuref(start[0] == '1', "start must begin with 1");
    inf.readEoln();

    string target = inf.readToken("[01]{1,10}", "target");
    ensuref(target[0] == '1', "target must begin with 1");
    inf.readEoln();

    inf.readEof();
}
