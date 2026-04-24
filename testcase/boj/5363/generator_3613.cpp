#include "testlib.h"
#include <vector>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of sentences
    int N = rnd.next(1, 10);
    // Word count range per sentence
    int minW = 3, maxW = 8;
    // Bias for word count distribution
    int bias = rnd.next(-2, 2);
    // Probability to capitalize a word
    double upProb = rnd.next();
    // Dictionary of sample words
    vector<string> dict = {
        "the","I","you","me","we","they","cat","dog","run","jump",
        "hello","world","yoda","speak","force","star","wars","power","light","dark"
    };
    // Output number of sentences
    println(N);
    // Generate each sentence
    for (int i = 0; i < N; i++) {
        int range = maxW - minW + 1;
        int wcount = minW + rnd.wnext(range, bias);
        vector<string> words;
        words.reserve(wcount);
        for (int j = 0; j < wcount; j++) {
            string w = rnd.any(dict);
            if (rnd.next() < upProb && !w.empty()) {
                w[0] = toupper(w[0]);
            }
            words.push_back(w);
        }
        println(words);
    }
    return 0;
}
