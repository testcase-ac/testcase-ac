#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string first = inf.readLine("[ABC]{2,5000}", "s_1");
    string second = inf.readLine("[ABC]{2,5000}", "s_2");
    string third = inf.readLine("[ABC]{2,5000}", "s_3");

    ensuref(second.size() == first.size(),
            "s_2 length must match s_1 length: got %d, expected %d",
            static_cast<int>(second.size()), static_cast<int>(first.size()));
    ensuref(third.size() == first.size(),
            "s_3 length must match s_1 length: got %d, expected %d",
            static_cast<int>(third.size()), static_cast<int>(first.size()));

    inf.readEof();
}
