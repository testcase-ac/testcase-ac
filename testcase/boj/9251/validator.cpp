#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("[A-Z]{1,1000}", "first_string");
    inf.readEoln();
    inf.readToken("[A-Z]{1,1000}", "second_string");
    inf.readEoln();
    inf.readEof();
}
