#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    // Hyper-parameter: probability of a space in a message
    double spaceProb = rnd.next(0.0, 1.0);
    for (int tc = 0; tc < T; tc++) {
        // Message length
        int L = rnd.next(1, 20);
        string msg;
        msg.reserve(L);
        for (int i = 0; i < L; i++) {
            // avoid leading/trailing spaces
            if (i > 0 && i < L - 1 && rnd.next() < spaceProb) {
                msg.push_back(' ');
            } else {
                char c = char(rnd.next('A', 'Z'));
                msg.push_back(c);
            }
        }
        // Generate a random decryption mapping: mapping[cipher - 'A'] = plain letter
        vector<char> letters(26);
        for (int i = 0; i < 26; i++) letters[i] = char('A' + i);
        shuffle(letters.begin(), letters.end());
        string mapping;
        mapping.reserve(26);
        for (char c : letters) mapping.push_back(c);
        // Output encrypted message and mapping
        println(msg);
        println(mapping);
    }
    return 0;
}
