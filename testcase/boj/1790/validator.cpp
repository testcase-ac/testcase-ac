#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string line = inf.readLine("[1-9][0-9]*\\ +[1-9][0-9]*", "N_k");

    size_t space = line.find(' ');
    long long N = stoll(line.substr(0, space));
    long long k = stoll(line.substr(line.find_last_of(' ') + 1));
    ensuref(N <= 100000000LL, "N must be at most 100000000, found %lld", N);
    ensuref(k <= 1000000000LL, "k must be at most 1000000000, found %lld", k);

    inf.readEof();
    return 0;
}
