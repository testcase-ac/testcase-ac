#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeWord(int x) {
    string word(3, 'a');
    for (int i = 2; i >= 0; --i) {
        word[i] = char('a' + (x % 26));
        x /= 26;
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 4);
    } else if (mode == 6) {
        n = rnd.next(25, 80);
    } else {
        n = rnd.next(5, 18);
    }

    int offset = rnd.next(0, 26 * 26 * 26 - n);
    vector<string> correct;
    correct.reserve(n);
    for (int i = 0; i < n; ++i) {
        correct.push_back(makeWord(offset + i));
    }
    shuffle(correct.begin(), correct.end());

    vector<string> answer = correct;
    if (mode == 0) {
        if (rnd.next(2) == 0) {
            reverse(answer.begin(), answer.end());
        }
    } else if (mode == 1) {
        reverse(answer.begin(), answer.end());
    } else if (mode == 2) {
        rotate(answer.begin(), answer.begin() + rnd.next(1, n - 1), answer.end());
    } else if (mode == 3) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int pos = rnd.next(0, n - 2);
            swap(answer[pos], answer[pos + 1]);
        }
    } else if (mode == 4) {
        int len = rnd.next(1, max(1, n / 3));
        int first = rnd.next(0, n - len);
        vector<string> block(answer.begin() + first, answer.begin() + first + len);
        answer.erase(answer.begin() + first, answer.begin() + first + len);
        int second = rnd.next(0, (int)answer.size());
        answer.insert(answer.begin() + second, block.begin(), block.end());
    } else if (mode == 5) {
        shuffle(answer.begin(), answer.end());
    } else {
        int chunks = rnd.next(3, 8);
        for (int start = 0; start < n; start += chunks) {
            int finish = min(n, start + chunks);
            shuffle(answer.begin() + start, answer.begin() + finish);
        }
        if (rnd.next(2) == 0) {
            reverse(answer.begin(), answer.end());
        }
    }

    println(n);
    println(correct);
    println(answer);

    return 0;
}
