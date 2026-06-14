#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement says the string may have spaces, despite also saying
    // it only contains uppercase A-Z.
    string s = inf.readLine("[A-Z\\ ]{1,1000}", "s");
    ensuref(s.front() != ' ', "s must not start with a space");
    ensuref(s.back() != ' ', "s must not end with a space");
    for (int i = 1; i < (int)s.size(); ++i) {
        ensuref(!(s[i - 1] == ' ' && s[i] == ' '),
                "s must not contain repeated spaces at positions %d and %d",
                i, i + 1);
    }

    inf.readEof();
}
