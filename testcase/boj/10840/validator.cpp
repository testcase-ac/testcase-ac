#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string a = inf.readToken("[a-z]{1,1500}", "S_A");
    inf.readEoln();
    string b = inf.readToken("[a-z]{1,1500}", "S_B");
    inf.readEoln();

    inf.readEof();
}
