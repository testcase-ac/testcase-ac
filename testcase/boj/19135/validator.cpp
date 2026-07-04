#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[ab]{1,200000}", "s");
    inf.readEoln();

    string t = inf.readToken("[ab]{1,200000}", "t");
    inf.readEoln();

    inf.readEof();
}
