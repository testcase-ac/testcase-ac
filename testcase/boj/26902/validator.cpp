#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[0-9]{4,12}", "s");
    inf.readEoln();
    inf.readEof();
}
