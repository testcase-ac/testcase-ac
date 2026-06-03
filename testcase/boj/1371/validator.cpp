#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int lineCount = 0;
    int letterCount = 0;

    while (!inf.eof()) {
        ensuref(lineCount < 50, "too many lines: at least %d", lineCount + 1);

        string line = inf.readLine("[a-z\\ ]{0,50}", "line");
        lineCount++;

        for (char c : line) {
            if ('a' <= c && c <= 'z') {
                letterCount++;
            }
        }
    }

    ensuref(lineCount >= 1, "input must contain at least one line");
    ensuref(letterCount >= 1, "input must contain at least one lowercase letter");

    inf.readEof();
}
