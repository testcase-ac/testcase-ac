#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

bool isNameChar(char c) {
    return c == '-' || c == ' ' ||
           ('0' <= c && c <= '9') ||
           ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z');
}

void validateName(const string& name, const char* fieldName) {
    ensuref(2 <= (int)name.size() && (int)name.size() <= 50,
            "%s length must be between 2 and 50, got %d",
            fieldName, (int)name.size());
    ensuref(name.front() != ' ', "%s must not start with a space", fieldName);
    ensuref(name.back() != ' ', "%s must not end with a space", fieldName);

    for (int i = 0; i < (int)name.size(); ++i) {
        ensuref(isNameChar(name[i]),
                "%s contains invalid character '%c' at position %d",
                fieldName, name[i], i);
        if (i > 0) {
            ensuref(!(name[i - 1] == ' ' && name[i] == ' '),
                    "%s must not contain consecutive spaces", fieldName);
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string line = inf.readLine();
    ensuref(2 <= (int)line.size() && (int)line.size() <= 103,
            "station_info length must be between 2 and 103, got %d",
            (int)line.size());

    size_t openPos = line.find('(');
    size_t closePos = line.find(')');

    if (openPos == string::npos && closePos == string::npos) {
        validateName(line, "station_name");
    } else {
        ensuref(openPos != string::npos && closePos != string::npos,
                "station_info must contain both '(' and ')' or neither");
        ensuref(openPos == line.rfind('(') && closePos == line.rfind(')'),
                "station_info must contain exactly one pair of parentheses");
        ensuref(openPos < closePos, "'(' must appear before ')'");
        ensuref(closePos == line.size() - 1, "')' must be the last character");
        ensuref(openPos >= 3 && line[openPos - 1] == ' ',
                "second format must be: station_name (sub_station_name)");

        string stationName = line.substr(0, openPos - 1);
        string subStationName = line.substr(openPos + 1, closePos - openPos - 1);

        validateName(stationName, "station_name");
        validateName(subStationName, "sub_station_name");
    }

    inf.readEof();
}
