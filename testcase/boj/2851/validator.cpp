#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 1; i <= 10; ++i) {
        inf.readInt(1, 100, "mushroom_score");
        inf.readEoln();
    }

    inf.readEof();
}
