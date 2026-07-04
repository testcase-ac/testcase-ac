#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

static char letter(int index) {
    return char('A' + index);
}

static string randomWord(int length, int alphabetSize) {
    string word;
    for (int i = 0; i < length; ++i) {
        word += letter(rnd.next(alphabetSize));
    }
    return word;
}

static vector<string> randomGrid(int n, int m, int alphabetSize) {
    vector<string> grid(n, string(m, 'A'));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            grid[r][c] = letter(rnd.next(alphabetSize));
        }
    }
    return grid;
}

static void printCase(int n, int m, int alphabetSize, const string& word, const vector<string>& grid) {
    println(n, m, alphabetSize);
    println(word);
    for (const string& row : grid) {
        println(row);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n, m, alphabetSize, wordLength;
    string word;
    vector<string> grid;

    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 12);
        alphabetSize = rnd.next(1, 4);
        wordLength = rnd.next(1, 14);
        grid = randomGrid(n, m, alphabetSize);
        word = randomWord(wordLength, alphabetSize);
    } else if (mode == 1) {
        n = rnd.next(3, 9);
        m = rnd.next(3, 9);
        alphabetSize = 1;
        wordLength = rnd.next(1, 18);
        grid.assign(n, string(m, 'A'));
        word.assign(wordLength, 'A');
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        m = rnd.next(4, 12);
        alphabetSize = rnd.next(2, 5);
        wordLength = rnd.next(2, 12);
        grid = randomGrid(n, m, alphabetSize);
        word = randomWord(wordLength, alphabetSize);

        int r = rnd.next(n);
        int c = rnd.next(m);
        grid[r][c] = word[0];
        for (int i = 1; i < wordLength; ++i) {
            vector<pair<int, int>> nextCells;
            for (int nr = 0; nr < n; ++nr) {
                for (int nc = 0; nc < m; ++nc) {
                    int dr = abs(nr - r);
                    int dc = abs(nc - c);
                    if ((dr > 2 && dc > 1) || (dr > 1 && dc > 2)) {
                        nextCells.push_back({nr, nc});
                    }
                }
            }
            if (nextCells.empty()) {
                break;
            }
            auto next = rnd.any(nextCells);
            r = next.first;
            c = next.second;
            grid[r][c] = word[i];
        }
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
        alphabetSize = rnd.next(2, 8);
        wordLength = rnd.next(1, 16);
        grid = randomGrid(n, m, alphabetSize);
        word = randomWord(wordLength, alphabetSize);
        word[rnd.next(wordLength)] = letter(rnd.next(alphabetSize, 25));
    } else if (mode == 4) {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
        alphabetSize = rnd.next(2, 26);
        wordLength = rnd.next(10, 30);
        grid = randomGrid(n, m, alphabetSize);
        word = randomWord(wordLength, alphabetSize);
    } else {
        n = rnd.next(1, 14);
        m = rnd.next(1, 14);
        alphabetSize = rnd.next(1, 6);
        wordLength = rnd.next(1, 20);
        grid = randomGrid(n, m, alphabetSize);
        word = randomWord(wordLength, alphabetSize);
        if (rnd.next(2) == 0) {
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < m; ++c) {
                    if ((r + c) % 2 == 0) {
                        grid[r][c] = letter(0);
                    }
                }
            }
        }
    }

    printCase(n, m, alphabetSize, word, grid);
    return 0;
}
