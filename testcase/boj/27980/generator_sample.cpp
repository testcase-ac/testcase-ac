#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char letterFromAlphabet(const string& alphabet) {
    return alphabet[rnd.next((int)alphabet.size())];
}

string randomString(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(letterFromAlphabet(alphabet));
    }
    return s;
}

char differentLetter(char c, const string& alphabet) {
    if ((int)alphabet.size() == 1) {
        return c == 'A' ? 'B' : 'A';
    }

    char next = c;
    while (next == c) {
        next = letterFromAlphabet(alphabet);
    }
    return next;
}

string alternatingString(int len, char a, char b) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(i % 2 == 0 ? a : b);
    }
    return s;
}

string makeWalkWord(const string& board, int m, const string& alphabet, double mutateProb) {
    int pos = rnd.next((int)board.size());
    string word;
    word.reserve(m);

    for (int i = 0; i < m; ++i) {
        char c = board[pos];
        if (rnd.next() < mutateProb) {
            c = differentLetter(c, alphabet);
        }
        word.push_back(c);

        if (i + 1 == m) {
            break;
        }
        if (pos == 0) {
            ++pos;
        } else if (pos + 1 == (int)board.size()) {
            --pos;
        } else if (rnd.next(2) == 0) {
            --pos;
        } else {
            ++pos;
        }
    }

    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(2, 30);
    int m = rnd.next(2, 30);
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string board;
    string word;

    if (mode == 0) {
        n = 2;
        m = rnd.next(2, 30);
        char a = rnd.next('A', 'Z');
        char b = differentLetter(a, alphabet);
        board = string() + a + b;
        word = randomString(m, string() + a + b);
    } else if (mode == 1) {
        alphabet = "ABC";
        board = randomString(n, alphabet);
        word = randomString(m, alphabet);
    } else if (mode == 2) {
        char c = rnd.next('A', 'Z');
        board = string(n, c);
        word = randomString(m, string() + c + differentLetter(c, alphabet));
    } else if (mode == 3) {
        char a = rnd.next('A', 'Z');
        char b = differentLetter(a, alphabet);
        board = alternatingString(n, a, b);
        word = alternatingString(m, rnd.next(2) == 0 ? a : b, rnd.next(2) == 0 ? a : b);
    } else if (mode == 4) {
        alphabet = "KONDUC";
        board = randomString(n, alphabet);
        word = makeWalkWord(board, m, alphabet, rnd.next(0.0, 0.35));
    } else {
        int alphabetSize = rnd.next(1, 8);
        alphabet = alphabet.substr(0, alphabetSize);
        n = rnd.next(2, 20);
        m = rnd.next(2, 35);
        board = randomString(n, alphabet);
        word = makeWalkWord(board, m, alphabet, rnd.next(0.15, 0.65));
    }

    println(n, m);
    println(board);
    println(word);
    return 0;
}
