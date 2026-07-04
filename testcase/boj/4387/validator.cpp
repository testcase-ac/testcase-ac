#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLine("\"[A-Za-z]{0,10}\"", "initial_string");

    int ruleCount = 0;
    while (!inf.eof()) {
        ++ruleCount;
        ensuref(ruleCount <= 100, "too many replacement rules: more than 100");
        inf.readLine("\"[A-Za-z]{0,10}\"->\"[A-Za-z]{0,10}\"", "replacement_rule");
    }

    inf.readEof();
}
