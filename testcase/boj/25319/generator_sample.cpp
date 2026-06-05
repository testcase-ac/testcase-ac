#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int len, const string& alphabet) {
    string result;
    result.reserve(len);
    for (int i = 0; i < len; ++i) result.push_back(rnd.any(alphabet));
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m, sLen;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    vector<string> board;
    string s;

    if (mode == 0) {
        n = rnd.next(2, 6);
        m = rnd.next(2, 6);
        alphabet = alphabet.substr(0, rnd.next(1, 4));
        sLen = rnd.next(1, min(20, n * m));
        for (int i = 0; i < n; ++i) board.push_back(randomString(m, alphabet));
        s = randomString(sLen, alphabet);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
        char common = char('a' + rnd.next(0, 25));
        char rare = char('a' + rnd.next(0, 25));
        while (rare == common) rare = char('a' + rnd.next(0, 25));
        board.assign(n, string(m, common));
        int rareCount = rnd.next(1, min(5, n * m));
        vector<int> cells(n * m);
        for (int i = 0; i < n * m; ++i) cells[i] = i;
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < rareCount; ++i) board[cells[i] / m][cells[i] % m] = rare;
        sLen = rnd.next(1, 18);
        s.assign(sLen, common);
        for (int i = 0; i < sLen; ++i) {
            if (rnd.next(0, 4) == 0) s[i] = rare;
        }
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
        int period = rnd.next(2, 7);
        for (int i = 0; i < n; ++i) {
            string row;
            for (int j = 0; j < m; ++j) row.push_back(char('a' + (i + j) % period));
            board.push_back(row);
        }
        sLen = rnd.next(1, 30);
        for (int i = 0; i < sLen; ++i) s.push_back(char('a' + rnd.next(0, period - 1)));
    } else if (mode == 3) {
        n = rnd.next(2, 7);
        m = rnd.next(2, 7);
        alphabet = alphabet.substr(0, rnd.next(5, 12));
        for (int i = 0; i < n; ++i) board.push_back(randomString(m, alphabet));
        sLen = rnd.next(1, 25);
        s = randomString(sLen, alphabet);
        if (rnd.next(0, 1)) s[rnd.next(0, sLen - 1)] = char('m' + rnd.next(0, 12));
    } else if (mode == 4) {
        n = rnd.next(2, 50);
        m = rnd.next(2, 50);
        alphabet = alphabet.substr(0, rnd.next(1, 26));
        for (int i = 0; i < n; ++i) board.push_back(randomString(m, alphabet));
        sLen = rnd.next(100, 1000);
        s = randomString(sLen, alphabet);
    } else {
        n = 50;
        m = 50;
        for (int i = 0; i < n; ++i) {
            string row;
            for (int j = 0; j < m; ++j) row.push_back(char('a' + (i * 3 + j * 5) % 26));
            board.push_back(row);
        }
        sLen = rnd.next(500, 1000);
        for (int i = 0; i < sLen; ++i) s.push_back(char('a' + (i * 7 + rnd.next(0, 3)) % 26));
    }

    println(n, m, sLen);
    for (const string& row : board) println(row);
    println(s);

    return 0;
}
