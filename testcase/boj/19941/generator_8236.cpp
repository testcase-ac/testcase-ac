#include "testlib.h"
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Length of the bench
    int N = rnd.next(2, 30);
    // Maximum reach distance
    int K = rnd.next(1, min(10, N - 1));
    // Number of people (at least 1 and at most N-1)
    int M = rnd.next(1, N - 1);
    // Build the configuration: M people ('P') and N-M hamburgers ('H')
    vector<char> v;
    v.reserve(N);
    for (int i = 0; i < M; i++) v.push_back('P');
    for (int i = 0; i < N - M; i++) v.push_back('H');
    // Shuffle to create varied patterns
    shuffle(v.begin(), v.end());
    string s(v.begin(), v.end());
    // Output
    println(N, K);
    printf("%s\n", s.c_str());
    return 0;
}
