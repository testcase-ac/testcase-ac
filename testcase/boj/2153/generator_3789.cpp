#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for length bias
    vector<int> tChoices = { -3, -1, 0, 1, 3 };
    int t = rnd.any(tChoices);
    // rnd.wnext(20, t) gives [0..19], so +1 => [1..20]
    int L = rnd.wnext(20, t) + 1;

    // Hyperparameter for uppercase probability
    double pUpper = rnd.next();

    // Build the word
    string word;
    word.reserve(L);
    for (int i = 0; i < L; i++) {
        if (rnd.next() < pUpper) {
            // Uppercase A-Z
            char c = char('A' + rnd.next(0, 25));
            word.push_back(c);
        } else {
            // Lowercase a-z
            char c = char('a' + rnd.next(0, 25));
            word.push_back(c);
        }
    }

    // Output the single test case
    println(word);
    return 0;
}
