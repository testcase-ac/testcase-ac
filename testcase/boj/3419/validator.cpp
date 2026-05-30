#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_SIZE = 1;
    const int MAX_SIZE = 100;
    const int MAX_FIELDS = 100000; // CHECK: the statement does not bound the number of fields.

    int fieldCount = 0;
    while (true) {
        int n = inf.readInt(0, MAX_SIZE, "N");
        inf.readSpace();
        int e = inf.readInt(0, MAX_SIZE, "E");
        inf.readEoln();

        if (n == 0 && e == 0) {
            inf.readEof();
            return 0;
        }

        ++fieldCount;
        ensuref(fieldCount <= MAX_FIELDS, "too many game fields: %d", fieldCount);
        ensuref(n >= MIN_SIZE, "N = %d is out of bounds [%d, %d]", n, MIN_SIZE, MAX_SIZE);
        ensuref(e >= MIN_SIZE, "E = %d is out of bounds [%d, %d]", e, MIN_SIZE, MAX_SIZE);

        for (int i = 0; i < n; ++i) {
            std::string line = inf.readLine("[.X]{1,100}", "map row");
            ensuref((int)line.size() == e,
                    "field %d row %d: expected length %d, got %d",
                    fieldCount, i + 1, e, (int)line.size());
        }
    }
}
