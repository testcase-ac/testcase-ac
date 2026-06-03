#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    string answers = inf.readToken("[BSA]{1,100000}", "answers");
    ensuref((int)answers.size() == n, "answers length is %d, expected %d",
            (int)answers.size(), n);
    inf.readEoln();

    inf.readEof();
}
