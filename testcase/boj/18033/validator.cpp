#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the circular string B: 3 ≤ |B| ≤ 1e5, characters are 'E' or 'P'
    string B = inf.readLine("[EP]{3,100000}", "B");
    int n = (int)B.size();

    // Read S: 1 ≤ S < |B|
    int S = inf.readInt(1, n - 1, "S");
    inf.readEoln();

    // No more data
    inf.readEof();
}
