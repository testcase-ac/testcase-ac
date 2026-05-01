#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Build a pool of possible characters (alphanumeric)
    string letters = "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "0123456789";
    vector<char> pool(letters.begin(), letters.end());

    // Choose one of three modes for diversity
    int mode = rnd.next(1, 3);
    string alphabet;
    string password;

    if (mode == 1) {
        // Edge case: single-character alphabet
        char c = rnd.any(pool);
        alphabet = string(1, c);
        int L = rnd.next(1, 5);  // short password
        password = string(L, c);
    }
    else if (mode == 2) {
        // Small alphabet, short-to-medium password with patterns
        int k = rnd.next(2, 5);
        shuffle(pool.begin(), pool.end());
        vector<char> alph(pool.begin(), pool.begin() + k);
        shuffle(alph.begin(), alph.end());
        for (char c : alph) alphabet.push_back(c);

        int L = rnd.next(1, min(10, k * 3));
        int pat = rnd.next(1, 3);
        if (pat == 1) {
            // all same as first letter
            password = string(L, alph[0]);
        } else if (pat == 2) {
            // all same as last letter
            password = string(L, alph[k - 1]);
        } else {
            // random picks
            for (int i = 0; i < L; i++)
                password.push_back(rnd.any(alph));
        }
    }
    else {
        // Medium alphabet, longer random password
        int k = rnd.next(2, min(10, (int)pool.size()));
        shuffle(pool.begin(), pool.end());
        vector<char> alph(pool.begin(), pool.begin() + k);
        shuffle(alph.begin(), alph.end());
        for (char c : alph) alphabet.push_back(c);

        int L = rnd.next(15, 25);
        for (int i = 0; i < L; i++)
            password.push_back(rnd.any(alph));
    }

    // Output the generated test case
    println(alphabet);
    println(password);

    return 0;
}
