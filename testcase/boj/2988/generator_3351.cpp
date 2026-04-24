#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checking
    int N = rnd.next(1, 10);

    // Row1: a random permutation of 1..N
    vector<int> row1(N);
    iota(row1.begin(), row1.end(), 1);
    shuffle(row1.begin(), row1.end());

    vector<int> row2(N), row3(N);

    // Choose a type of case to increase diversity
    int type = rnd.next(0, 4);
    if (type == 0) {
        // row2 is a permutation, row3 random with mixed bias
        vector<int> tmp = row1;
        shuffle(tmp.begin(), tmp.end());
        row2 = tmp;
        int t3 = rnd.any(vector<int>{-1, 0, 1});
        for (int i = 0; i < N; i++)
            row3[i] = rnd.wnext(N, t3) + 1;
    } else if (type == 1) {
        // row3 is a permutation, row2 random with mixed bias
        vector<int> tmp = row1;
        shuffle(tmp.begin(), tmp.end());
        row3 = tmp;
        int t2 = rnd.any(vector<int>{-1, 0, 1});
        for (int i = 0; i < N; i++)
            row2[i] = rnd.wnext(N, t2) + 1;
    } else if (type == 2) {
        // both row2 and row3 are permutations
        vector<int> tmp2(N), tmp3(N);
        iota(tmp2.begin(), tmp2.end(), 1);
        iota(tmp3.begin(), tmp3.end(), 1);
        shuffle(tmp2.begin(), tmp2.end());
        shuffle(tmp3.begin(), tmp3.end());
        row2 = tmp2;
        row3 = tmp3;
    } else if (type == 3) {
        // both heavily biased to low numbers
        for (int i = 0; i < N; i++) {
            row2[i] = rnd.wnext(N, -1) + 1;
            row3[i] = rnd.wnext(N, -1) + 1;
        }
    } else { // type == 4
        // both heavily biased to high numbers
        for (int i = 0; i < N; i++) {
            row2[i] = rnd.wnext(N, 1) + 1;
            row3[i] = rnd.wnext(N, 1) + 1;
        }
    }

    // Output in the required format
    println(N);
    println(row1);
    println(row2);
    println(row3);

    return 0;
}
