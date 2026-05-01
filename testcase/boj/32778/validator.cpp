#include "testlib.h"
#include <string>
#include <cctype>

using namespace std;

bool isAllowedChar(char c) {
    if (c == '-' || c == ' ') return true;
    if ('0' <= c && c <= '9') return true;
    if ('a' <= c && c <= 'z') return true;
    if ('A' <= c && c <= 'Z') return true;
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line input
    string line = inf.readLine("[^]+", "line");

    // Line length constraint
    ensuref((int)line.size() >= 2 && (int)line.size() <= 50,
            "line length must be between 2 and 50, got %d", (int)line.size());

    // Check characters and count parentheses
    int openCnt = 0, closeCnt = 0;
    int openPos = -1, closePos = -1;

    for (int i = 0; i < (int)line.size(); i++) {
        char c = line[i];
        if (c == '(') {
            openCnt++;
            if (openCnt == 1) openPos = i;
        } else if (c == ')') {
            closeCnt++;
            if (closeCnt == 1) closePos = i;
        } else {
            ensuref(isAllowedChar(c),
                    "invalid character '%c' at position %d", c, i);
        }
    }

    // Either no parentheses (form 1) or exactly one pair at the end (form 2)
    if (openCnt == 0 && closeCnt == 0) {
        // Form 1: just station_name, no extra structure constraints
        // Check station_name spacing rules
        ensuref(line.front() != ' ' && line.back() != ' ',
                "station_name cannot start or end with a space in form without sub_station_name");
        for (int i = 1; i < (int)line.size(); i++) {
            ensuref(!(line[i] == ' ' && line[i - 1] == ' '),
                    "consecutive spaces are not allowed in station_name");
        }
    } else {
        // Must be exactly one '(' and one ')'
        ensuref(openCnt == 1 && closeCnt == 1,
                "input must contain either no parentheses or exactly one pair");
        // '(' must appear before ')'
        ensuref(openPos < closePos, "'(' must appear before ')'");

        // ')' must be the last character
        ensuref(closePos == (int)line.size() - 1,
                "closing parenthesis must be the last character");

        // There must be a space before '('
        ensuref(openPos > 0 && line[openPos - 1] == ' ',
                "there must be a single space before '('");

        // The character before that space must not be a space
        ensuref(!(openPos - 2 >= 0 && line[openPos - 2] == ' '),
                "station_name cannot end with a space; also no consecutive spaces around '('");

        // The substring between '(' and ')' (exclusive) is sub_station_name and cannot be empty
        ensuref(closePos - openPos - 1 >= 2,
                "sub_station_name length must be at least 2");

        // Extract station_name and sub_station_name for spacing checks
        string station = line.substr(0, openPos - 1); // exclude space before '('
        string sub = line.substr(openPos + 1, closePos - openPos - 1);

        // station_name length constraints
        ensuref((int)station.size() >= 2 && (int)station.size() <= 50,
                "station_name length must be between 2 and 50, got %d", (int)station.size());
        // sub_station_name length constraints
        ensuref((int)sub.size() >= 2 && (int)sub.size() <= 50,
                "sub_station_name length must be between 2 and 50, got %d", (int)sub.size());

        // Spacing rules for station_name
        ensuref(station.front() != ' ' && station.back() != ' ',
                "station_name cannot start or end with a space");
        for (int i = 1; i < (int)station.size(); i++) {
            ensuref(!(station[i] == ' ' && station[i - 1] == ' '),
                    "consecutive spaces are not allowed in station_name");
        }

        // Spacing rules for sub_station_name
        ensuref(sub.front() != ' ' && sub.back() != ' ',
                "sub_station_name cannot start or end with a space");
        for (int i = 1; i < (int)sub.size(); i++) {
            ensuref(!(sub[i] == ' ' && sub[i - 1] == ' '),
                    "consecutive spaces are not allowed in sub_station_name");
        }
    }

    inf.readEof();
}
