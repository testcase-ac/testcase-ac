#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomNumber(int mode) {
    if (mode == 0) return to_string(rnd.next(1, 9));
    if (mode == 1) return to_string(rnd.next(10, 99));
    if (mode == 2) return to_string(rnd.next(100, 999));
    return "1000";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string delimiters = ".|:#";
    int mode = rnd.next(0, 5);
    int targetLength = 0;
    int numberMode = 0;

    if (mode == 0) {
        targetLength = rnd.next(1, 12);
        numberMode = 0;
    } else if (mode == 1) {
        targetLength = rnd.next(8, 40);
        numberMode = rnd.next(0, 2);
    } else if (mode == 2) {
        targetLength = rnd.next(30, 120);
        numberMode = rnd.next(0, 3);
    } else if (mode == 3) {
        targetLength = rnd.next(80, 250);
        numberMode = 3;
    } else {
        targetLength = rnd.next(250, 1000);
        numberMode = rnd.next(0, 3);
    }

    vector<string> parts;
    string slogan;
    while (true) {
        string part = randomNumber(numberMode == 3 ? 3 : rnd.next(0, numberMode));
        int added = (slogan.empty() ? 0 : 1) + (int)part.size();
        if (!slogan.empty() && (int)slogan.size() + added > targetLength) break;
        if (slogan.empty() && added > targetLength) {
            part = "1";
            added = 1;
        }
        if (!slogan.empty()) slogan += delimiters[rnd.next((int)delimiters.size())];
        slogan += part;
        parts.push_back(part);
        if ((int)slogan.size() >= targetLength) break;
    }

    println((int)slogan.size());
    println(slogan);
    return 0;
}
