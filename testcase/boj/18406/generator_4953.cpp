#include "testlib.h"
#include <vector>
#include <string>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose total digit length (even)
    vector<int> lengths = {2, 4, 6, 8};
    int L = rnd.any(lengths);
    int half = L / 2;
    // Hyper-parameter: decide lucky or not
    bool lucky = rnd.next(0, 1);
    // Generate target sum for first half (must be >=1 so first digit >=1)
    int S1 = rnd.next(1, 9 * half);
    // Generate first half digits with sum S1 and first digit >=1
    vector<int> firstHalf(half);
    while (true) {
        firstHalf[0] = rnd.next(1, 9);
        for (int i = 1; i < half; i++) {
            firstHalf[i] = rnd.next(0, 9);
        }
        if (accumulate(firstHalf.begin(), firstHalf.end(), 0) == S1)
            break;
    }
    // Determine sum for second half
    int S2;
    if (lucky) {
        S2 = S1;
    } else {
        // pick any sum != S1
        vector<int> choice;
        for (int s = 0; s <= 9 * half; s++)
            if (s != S1) choice.push_back(s);
        S2 = rnd.any(choice);
    }
    // Generate second half digits with sum S2 (leading zeros allowed)
    vector<int> secondHalf(half);
    while (true) {
        for (int i = 0; i < half; i++) {
            secondHalf[i] = rnd.next(0, 9);
        }
        if (accumulate(secondHalf.begin(), secondHalf.end(), 0) == S2)
            break;
    }
    // Build the number string (no leading zeros overall)
    string N;
    N.reserve(L);
    for (int d : firstHalf) N.push_back(char('0' + d));
    for (int d : secondHalf) N.push_back(char('0' + d));
    // Output the single test case
    println(N);
    return 0;
}
