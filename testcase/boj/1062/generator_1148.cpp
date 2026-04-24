#include "testlib.h"
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]){
    // initialize the generator with a random seed
    registerGen(argc, argv, 1);

    // Choose a small N (number of words) and K (number of letters taught)
    int N = rnd.next(1, 10);
    int K = rnd.next(0, 26);
    println(N, K);

    char ub = rnd.next('b', 'z');

    // Use a set to avoid duplicate words.
    set<string> used;
    for (int i = 0; i < N; i++) {
        string middle;
        // The total word length must be between 8 and 15.
        // Since "anta" and "tica" contribute 8 characters, the middle part can have 0 to 7 characters.
        int middleLen = rnd.next(0, 7);
        for (int j = 0; j < middleLen; j++) {
            char c = char(rnd.next('a', ub));
            middle.push_back(c);
        }
        string word = "anta" + middle + "tica";
        // Ensure the word is distinct.
        while (used.count(word)) {
            middle = "";
            middleLen = rnd.next(0, 7);
            for (int j = 0; j < middleLen; j++) {
                char c = char(rnd.next('a', ub));
                middle.push_back(c);
            }
            word = "anta" + middle + "tica";
        }
        used.insert(word);
        println(word);
    }
    
    return 0;
}
