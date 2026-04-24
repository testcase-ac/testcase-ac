#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small N
    int N = rnd.next(1, 10);
    // Hyper-parameter to bias B
    int tB = rnd.next(-2, 2);
    int B = rnd.wnext(N, tB) + 1;
    // Build permutation 1..N
    vector<int> A(N);
    iota(A.begin(), A.end(), 1);
    shuffle(A.begin(), A.end());
    // Hyper-parameter to bias position of B
    int tpos = rnd.next(-2, 2);
    int posB = rnd.wnext(N, tpos); // 0-based
    // Place B at posB
    int cur = find(A.begin(), A.end(), B) - A.begin();
    swap(A[cur], A[posB]);
    // Output
    println(N, B);
    println(A);
    return 0;
}
