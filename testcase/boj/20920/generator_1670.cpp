#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int M = rnd.next(1, 5);
    int MAX_LEN = rnd.next(M, 5);
    int N = rnd.next(1, 10);
    char max_char;
    int type = rnd.next(0, 2);
    if(type == 0) {
        max_char = 'b';
    } else if(type == 1) {
        max_char = 'c';
    } else {
        max_char = 'z';
    }
    
    vector<string> words;
    
    // Generate the first word with length >= M
    int firstLen = rnd.next(M, MAX_LEN);
    string firstWord;
    for (int i = 0; i < firstLen; ++i) {
        firstWord += rnd.next('a', max_char);
    }
    words.push_back(firstWord);
    
    int gen_cnt = rnd.next(0, N-1);
    // Generate remaining N-1 words with any length (1-MAX_LEN)
    for (int i = 0; i < gen_cnt; ++i) {
        int len = rnd.next(1, MAX_LEN);
        string word;
        for (int j = 0; j < len; ++j) {
            word += rnd.next('a', max_char);
        }
        words.push_back(word);
    }
    
    // Output
    println(N, M);
    vector<string> output;
    for(int i=0; i<N; i++) {
        if(i == 0) {
            output.push_back(words[i]);
        } else {
            output.push_back(words[rnd.next(0, (int)words.size()-1)]);
        }
    }
    shuffle(output.begin(), output.end());
    for(int i=0; i<N; i++) {
        println(output[i]);
    }
    
    return 0;
}
