#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "n");
    inf.readEoln();

    set<string> seats;
    for (int i = 0; i < n; ++i) {
        string seat = inf.readToken("[A-J][0-9]{1,2}", "seat");
        inf.readEoln();

        int number = 0;
        for (int j = 1; j < static_cast<int>(seat.size()); ++j) {
            number = number * 10 + (seat[j] - '0');
        }

        ensuref(seat[1] != '0', "seat number has leading zero at index %d: %s", i + 1,
                seat.c_str());
        ensuref(1 <= number && number <= 20, "seat number out of range at index %d: %s",
                i + 1, seat.c_str());
        ensuref(seats.insert(seat).second, "duplicate seat at index %d: %s", i + 1,
                seat.c_str());
    }

    inf.readEof();
}
