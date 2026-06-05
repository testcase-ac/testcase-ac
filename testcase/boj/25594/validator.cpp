#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[a-z]+", "S");
    ensuref(s.size() <= 8000000, "|S| must be at most 8000000, got %d",
            static_cast<int>(s.size()));
    inf.readEof();
}
