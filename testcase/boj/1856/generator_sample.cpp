#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomWord(int len, const string& alphabet) {
    string word;
    for (int i = 0; i < len; ++i) {
        word += rnd.any(alphabet);
    }
    return word;
}

string noisyMessage(const vector<string>& parts, const string& alphabet, int maxNoiseBeforeChar) {
    string message;
    for (const string& part : parts) {
        for (char ch : part) {
            int noise = rnd.next(0, maxNoiseBeforeChar);
            for (int i = 0; i < noise; ++i) {
                message += rnd.any(alphabet);
            }
            message += ch;
        }
    }

    while ((int)message.size() < 2) {
        message += rnd.any(alphabet);
    }
    return message;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = rnd.next(0, 3) == 0 ? "abc" : "abcdefghijklmnopqrstuvwxyz";
    int mode = rnd.next(0, 4);

    vector<string> dictionary;
    vector<string> chosen;
    string s;

    if (mode == 0) {
        int parts = rnd.next(1, 6);
        for (int i = 0; i < parts; ++i) {
            string word = randomWord(rnd.next(1, 8), alphabet);
            dictionary.push_back(word);
            chosen.push_back(word);
        }
        s = noisyMessage(chosen, alphabet, rnd.next(0, 2));
    } else if (mode == 1) {
        int wordCount = rnd.next(1, 8);
        for (int i = 0; i < wordCount; ++i) {
            dictionary.push_back(string(1, rnd.any(alphabet)));
        }
        int len = rnd.next(2, 30);
        s = randomWord(len, alphabet);
    } else if (mode == 2) {
        int len = rnd.next(20, 25);
        string longWord = randomWord(len, alphabet);
        dictionary.push_back(longWord);
        chosen.push_back(longWord);
        s = noisyMessage(chosen, alphabet, rnd.next(0, 1));
    } else if (mode == 3) {
        int parts = rnd.next(2, 8);
        for (int i = 0; i < parts; ++i) {
            string word = randomWord(rnd.next(1, 5), alphabet);
            dictionary.push_back(word);
            chosen.push_back(word);
        }
        s = noisyMessage(chosen, alphabet, 0);
    } else {
        int len = rnd.next(2, 35);
        s = randomWord(len, alphabet);
        int wordCount = rnd.next(1, 10);
        for (int i = 0; i < wordCount; ++i) {
            dictionary.push_back(randomWord(rnd.next(1, min(25, len)), alphabet));
        }
    }

    while ((int)s.size() > 300) {
        s.pop_back();
    }

    int extraWords = rnd.next(0, 8);
    for (int i = 0; i < extraWords; ++i) {
        dictionary.push_back(randomWord(rnd.next(1, 12), alphabet));
    }

    shuffle(dictionary.begin(), dictionary.end());

    println((int)dictionary.size(), (int)s.size());
    println(s);
    for (const string& word : dictionary) {
        println(word);
    }

    return 0;
}
