#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N1 = rnd.next(1, 5); // Number of ants in the first row
    int N2 = rnd.next(1, 5); // Number of ants in the second row
    int T = rnd.next(0, 4);
    if(rnd.next() < 0.2) {
      T = rnd.next(5, 50);
    }

    // Decide whether to use only A-J or the full alphabet
    bool useLimitedLetters = rnd.next(0, 1); // 50% chance

    vector<char> letters;
    if (useLimitedLetters) {
        // Use only A-J
        for (char c = 'A'; c < 'A' + N1 + N2; ++c) {
            letters.push_back(c);
        }
    } else {
        // Use the full alphabet A-Z
        for (char c = 'A'; c <= 'Z'; ++c) {
            letters.push_back(c);
        }
    }
    shuffle(letters.begin(), letters.end());

    // Assign letters to the first and second rows
    string group1, group2;
    for (int i = 0; i < N1; ++i) {
        group1 += letters[i];
    }
    for (int i = N1; i < N1 + N2; ++i) {
        group2 += letters[i];
    }

    // Print the test case
    println(N1, N2);
    println(group1);
    println(group2);
    println(T);

    return 0;
}
