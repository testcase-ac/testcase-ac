#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string vowels = "aeiou";
    string cons;
    for(char c = 'a'; c <= 'z'; ++c) if (vowels.find(c) == string::npos) cons.push_back(c);
    string letters = vowels + cons;

    int N = rnd.next(1, 8);
    vector<int> types;
    if (N >= 4) {
        types = {0, 1, 2, 3};
        for (int i = 4; i < N; ++i) types.push_back(rnd.next(0, 3));
    } else {
        for (int i = 0; i < N; ++i) types.push_back(i);
    }
    shuffle(types.begin(), types.end());

    for (int t : types) {
        int L = rnd.wnext(20, -1) + 1; // [1..20], bias small
        string w(L, 'a');
        if (t == 0) {
            // start with vowel
            w[0] = rnd.any(vowels);
            for (int i = 1; i < L; ++i) w[i] = rnd.any(letters);
        } else if (t == 1) {
            // start with consonant, ensure a vowel inside
            if (L == 1) {
                // fallback to no-vowel
                w[0] = rnd.any(cons);
            } else {
                w[0] = rnd.any(cons);
                int vidx = rnd.next(1, L - 1);
                for (int i = 1; i < L; ++i) {
                    if (i == vidx) w[i] = rnd.any(vowels);
                    else w[i] = rnd.any(letters);
                }
            }
        } else if (t == 2) {
            // no vowels
            for (int i = 0; i < L; ++i) w[i] = rnd.any(cons);
        } else {
            // only vowels
            for (int i = 0; i < L; ++i) w[i] = rnd.any(vowels);
        }
        println(w);
    }
    println("#");
    return 0;
}
