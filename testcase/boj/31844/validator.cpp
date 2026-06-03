#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string cells = inf.readToken("[.@#!]{10}", "cells");
    inf.readEoln();

    ensuref(count(cells.begin(), cells.end(), '@') == 1,
            "expected exactly one robot '@'");
    ensuref(count(cells.begin(), cells.end(), '#') == 1,
            "expected exactly one box '#'");
    ensuref(count(cells.begin(), cells.end(), '!') == 1,
            "expected exactly one target '!'");

    inf.readEof();
}
