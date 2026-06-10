#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

char noiseChar() {
    static const string letters = "ABCDEFGHILMNOPQRTUVWXYZ";
    return rnd.any(letters);
}

string randomNoise(int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) s.push_back(noiseChar());
    return s;
}

string skkBlock(int sCount, int kCount, int noiseCount) {
    vector<char> chars;
    chars.reserve(sCount + kCount + noiseCount);
    for (int i = 0; i < sCount; ++i) chars.push_back('S');
    for (int i = 0; i < kCount; ++i) chars.push_back('K');
    for (int i = 0; i < noiseCount; ++i) chars.push_back(noiseChar());
    shuffle(chars.begin(), chars.end());
    return string(chars.begin(), chars.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string answer;

    if (mode == 0) {
        int len = rnd.next(1, 40);
        answer = randomNoise(len);
    } else if (mode == 1) {
        int sCount = rnd.next(1, 12);
        int noiseCount = rnd.next(0, 16);
        answer = skkBlock(sCount, 2 * sCount, noiseCount);
    } else if (mode == 2) {
        int sCount = rnd.next(1, 8);
        string middle = skkBlock(sCount, 2 * sCount, rnd.next(0, 10));
        answer = randomNoise(rnd.next(0, 12)) + middle + randomNoise(rnd.next(0, 12));
    } else if (mode == 3) {
        int sCount = rnd.next(1, 14);
        int kCount = max(0, 2 * sCount + rnd.any(vector<int>{-2, -1, 1, 2, 3}));
        answer = skkBlock(sCount, kCount, rnd.next(0, 12));
        if (answer.empty()) answer = "S";
    } else if (mode == 4) {
        int groups = rnd.next(2, 9);
        for (int i = 0; i < groups; ++i) {
            if (rnd.next(0, 1)) answer += "SKK";
            else answer += skkBlock(1, 2, rnd.next(0, 3));
            if (rnd.next(0, 2) == 0) answer += randomNoise(rnd.next(1, 4));
        }
    } else {
        int len = rnd.next(1, 60);
        string alphabet = "SKK";
        for (int i = 0; i < len; ++i) {
            if (rnd.next(0, 4) == 0) answer.push_back(noiseChar());
            else answer.push_back(rnd.any(alphabet));
        }
    }

    println(answer);
    return 0;
}
