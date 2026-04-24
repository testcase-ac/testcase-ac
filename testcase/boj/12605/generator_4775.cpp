#include "testlib.h"
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Number of test cases N between 1 and 5, with bias for small or large
    int tN = rnd.next(-1, 1);
    int N = rnd.wnext(5, tN) + 1;
    println(N);
    
    for (int i = 0; i < N; i++) {
        // Total alphabet count Lsum between 1 and 25, biased toward ends
        int tL = rnd.next(-1, 1);
        int L0 = rnd.wnext(25, tL); // in [0,24]
        int Lsum = L0 + 1;
        
        // Number of words w between 1 and min(Lsum,8)
        int maxW = min(Lsum, 8);
        int w = rnd.next(1, maxW);
        
        // Partition Lsum into w positive parts
        vector<int> parts(w, 1);
        int rem = Lsum - w;
        for (int j = 0; j < rem; j++) {
            parts[rnd.next(w)]++;
        }
        
        // Alphabet size: pick letters from 'a' to some maxC
        int lexSize = rnd.next(1, 26);
        char maxC = char('a' + lexSize - 1);
        string alphabet;
        for (char c = 'a'; c <= maxC; c++) alphabet.push_back(c);
        
        // Build each word of given lengths
        vector<string> words;
        for (int j = 0; j < w; j++) {
            string s;
            for (int k = 0; k < parts[j]; k++) {
                s.push_back(rnd.any(alphabet));
            }
            words.push_back(s);
        }
        
        // Shuffle word order for randomness
        shuffle(words.begin(), words.end());
        
        // Output the line
        println(words);
    }
    
    return 0;
}
