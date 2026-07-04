#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

namespace {

bool isVowel(char ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

vector<char> pickLetters(int vowelCount, int consonantCount) {
    string vowels = "aeiou";
    string consonants;
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (!isVowel(ch)) consonants.push_back(ch);
    }

    vector<char> vowelPool(vowels.begin(), vowels.end());
    vector<char> consonantPool(consonants.begin(), consonants.end());
    shuffle(vowelPool.begin(), vowelPool.end());
    shuffle(consonantPool.begin(), consonantPool.end());

    vector<char> letters;
    for (int i = 0; i < vowelCount; ++i) letters.push_back(vowelPool[i]);
    for (int i = 0; i < consonantCount; ++i) letters.push_back(consonantPool[i]);
    shuffle(letters.begin(), letters.end());
    return letters;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int L;
    int C;
    int vowelCount;

    if (mode == 0) {
        C = rnd.next(3, 7);
        L = rnd.next(3, C);
        vowelCount = rnd.next(0, min(5, C));
    } else if (mode == 1) {
        C = rnd.next(8, 12);
        L = rnd.next(3, C);
        vowelCount = rnd.next(1, min(5, C));
    } else if (mode == 2) {
        C = 15;
        L = rnd.any(vector<int>{3, 4, 7, 14, 15});
        vowelCount = rnd.next(1, 5);
    } else if (mode == 3) {
        C = rnd.next(3, 15);
        L = C;
        vowelCount = rnd.next(0, min(5, C));
    } else if (mode == 4) {
        C = rnd.next(3, 15);
        L = rnd.next(3, C);
        vowelCount = min(5, max(0, C - rnd.next(0, 2)));
    } else {
        C = rnd.next(3, 15);
        L = rnd.next(3, C);
        vowelCount = rnd.next(0, min(1, C));
    }

    int consonantCount = C - vowelCount;
    vector<char> letters = pickLetters(vowelCount, consonantCount);

    println(L, C);
    for (int i = 0; i < C; ++i) {
        if (i) cout << ' ';
        cout << letters[i];
    }
    cout << '\n';

    return 0;
}
