#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string a = inf.readToken("[a-z]{1,1000}", "A");
    inf.readEoln();
    string b = inf.readToken("[a-z]{1,1000}", "B");
    inf.readEoln();
    inf.readEof();
}
