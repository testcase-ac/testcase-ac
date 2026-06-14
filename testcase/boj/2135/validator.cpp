#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-z]{1,200}", "s");
    inf.readEoln();
    inf.readEof();
}
