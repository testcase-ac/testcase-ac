#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

vector<string> splitAddress(const string& address) {
    vector<string> parts;
    string current;
    for (char ch : address) {
        if (ch == '.') {
            parts.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    parts.push_back(current);
    return parts;
}

int parseByte(const string& part, int addressIndex, int byteIndex) {
    ensuref(!part.empty(), "empty byte in address %d at byte %d", addressIndex, byteIndex);
    ensuref(part.size() == 1 || part[0] != '0',
            "leading zero in address %d at byte %d: %s",
            addressIndex,
            byteIndex,
            part.c_str());

    int value = 0;
    for (char ch : part) {
        ensuref('0' <= ch && ch <= '9',
                "non-digit in address %d at byte %d: %s",
                addressIndex,
                byteIndex,
                part.c_str());
        value = value * 10 + (ch - '0');
    }

    ensuref(value <= 255,
            "byte out of range in address %d at byte %d: %d",
            addressIndex,
            byteIndex,
            value);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string address = inf.readLine("[0-9.]{7,15}", "ip");
        vector<string> parts = splitAddress(address);
        ensuref(parts.size() == 4,
                "address %d must contain exactly four bytes: %s",
                i + 1,
                address.c_str());
        for (int j = 0; j < 4; ++j) {
            parseByte(parts[j], i + 1, j + 1);
        }
    }

    inf.readEof();
    return 0;
}
