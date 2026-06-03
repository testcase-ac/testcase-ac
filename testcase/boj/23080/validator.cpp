#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(3, 10, "K");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,1000}", "S");
    inf.readEoln();

    inf.readEof();
}
