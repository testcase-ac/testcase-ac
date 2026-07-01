#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomWord(int len, const string& alphabet) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string shuffledCopy(string s) {
    if ((int)s.size() >= 2 && rnd.next(0, 2) != 0) {
        string original = s;
        for (int tries = 0; tries < 8; ++tries) {
            shuffle(s.begin(), s.end());
            if (s != original) {
                break;
            }
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "abcde";
    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int segmentCount = rnd.next(1, mode == 4 ? 12 : 7);
        int maxSegmentLength = mode == 4 ? 5 : rnd.next(1, 8);

        vector<string> segments;
        string sentence;
        for (int i = 0; i < segmentCount && (int)sentence.size() < 48; ++i) {
            int len = rnd.next(1, min(maxSegmentLength, 50 - (int)sentence.size()));
            string part;
            if (mode == 0) {
                part = string(len, rnd.any(alphabet));
            } else if (mode == 1 && !segments.empty() && rnd.next(0, 1)) {
                part = rnd.any(segments);
            } else {
                part = randomWord(len, alphabet);
            }
            segments.push_back(part);
            sentence += part;
        }

        bool impossible = (mode == 5);
        if (impossible) {
            if ((int)sentence.size() == 50) {
                sentence.back() = 'q';
            } else {
                sentence += 'q';
            }
        }

        vector<string> words;
        if (!impossible || rnd.next(0, 1)) {
            for (const string& part : segments) {
                words.push_back(shuffledCopy(part));
                if (rnd.next(0, 3) == 0) {
                    words.push_back(part);
                }
            }
        }

        int distractors = rnd.next(2, 10);
        for (int i = 0; i < distractors && (int)words.size() < 50; ++i) {
            int len = rnd.next(1, min(10, max(1, (int)sentence.size())));
            string word = randomWord(len, alphabet);
            if (mode == 2 && len >= 2) {
                word = string(len, rnd.any(alphabet));
            }
            words.push_back(word);
        }

        if (words.empty()) {
            words.push_back(randomWord(1, alphabet));
        }
        while ((int)words.size() > 50) {
            words.pop_back();
        }
        shuffle(words.begin(), words.end());

        println(sentence);
        println((int)words.size());
        for (const string& word : words) {
            println(word);
        }
    }

    return 0;
}
