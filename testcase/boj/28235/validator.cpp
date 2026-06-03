#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const set<string> valid_chants = {"SONGDO", "CODE", "2023", "ALGORITHM"};

    string chant = inf.readToken("SONGDO|CODE|2023|ALGORITHM", "chant");
    inf.readEoln();
    ensuref(valid_chants.count(chant) == 1, "invalid chant: %s", chant.c_str());

    inf.readEof();
}
