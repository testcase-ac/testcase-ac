#include "testlib.h"
#include <vector>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

bool checkWin(const array<char, 9>& b, char p) {
    static const int winLines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };
    for (int k = 0; k < 8; ++k) {
        if (b[winLines[k][0]] == p &&
            b[winLines[k][1]] == p &&
            b[winLines[k][2]] == p)
            return true;
    }
    return false;
}

string genValidTerminal() {
    array<char, 9> b;
    b.fill('.');
    vector<int> empty(9);
    for (int i = 0; i < 9; ++i) empty[i] = i;

    for (int move = 0; move < 9; ++move) {
        char cur = (move % 2 == 0 ? 'X' : 'O');
        int idx = rnd.next(0, (int)empty.size() - 1);
        int pos = empty[idx];
        empty[idx] = empty.back();
        empty.pop_back();
        b[pos] = cur;
        if (move >= 4 && checkWin(b, cur))
            break;
    }

    string s(9, '.');
    for (int i = 0; i < 9; ++i) s[i] = b[i];
    return s;
}

string genRandomBoard() {
    string s(9, '.');
    for (int i = 0; i < 9; ++i) {
        double p = rnd.next();
        if (p < 0.4) s[i] = 'X';
        else if (p < 0.8) s[i] = 'O';
        else s[i] = '.';
    }
    return s;
}

string mutateBoard(const string& base) {
    string s = base;
    int changes = rnd.next(1, 3);
    for (int t = 0; t < changes; ++t) {
        int pos = rnd.next(0, 8);
        char old = s[pos];
        const string cand = "XO.";
        char nw = old;
        while (nw == old) {
            nw = cand[rnd.next(0, (int)cand.size() - 1)];
        }
        s[pos] = nw;
    }
    return s;
}

string genMixedBoard() {
    int type = rnd.next(0, 2); // 0: random, 1: valid terminal, 2: mutated valid
    if (type == 0) return genRandomBoard();
    if (type == 1) return genValidTerminal();
    return mutateBoard(genValidTerminal());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> boards;

    // Some fixed interesting boards
    boards.push_back(".........");   // empty board
    boards.push_back("XXXOOOXXX");   // both X and O have a line
    boards.push_back("XXXOO....");   // quick X win with empty cells
    boards.push_back("XOXXOOOXX");   // full board, no winner (draw)
    boards.push_back("XXXOOOOOO");   // many moves after X already wins
    boards.push_back("XOXOXOXOX");   // alternating, from sample
    boards.push_back("OXOXOXOXO");   // alternating starting with O
    boards.push_back("XXOOOXXOX");   // complex mixed pattern
    boards.push_back("XO.OX...X");   // sample pattern
    boards.push_back(".XXX.XOOO");   // sample pattern
    boards.push_back("X.OO..X..");   // sample pattern

    int extra = rnd.next(5, 12);
    for (int i = 0; i < extra; ++i) {
        boards.push_back(genMixedBoard());
    }

    shuffle(boards.begin(), boards.end());

    for (const string& s : boards)
        println(s);
    println("end");

    return 0;
}
