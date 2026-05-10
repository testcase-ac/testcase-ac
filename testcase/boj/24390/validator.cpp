#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line in format "MM:SS"
    string line = inf.readLine("[0-9]{2}:[0-9]{2}", "time");

    int M = (line[0] - '0') * 10 + (line[1] - '0');
    int S = (line[3] - '0') * 10 + (line[4] - '0');

    // Constraints from statement
    ensuref(0 <= M && M <= 60, "Minutes M must be between 0 and 60, got %d", M);
    ensuref(0 <= S && S <= 59, "Seconds S must be between 0 and 59, got %d", S);

    int total = M * 60 + S;

    // "조리시간은 10초 이상 60분(3600초) 이하이며, 항상 10의 배수이다."
    ensuref(total >= 10, "Total time must be at least 10 seconds, got %d", total);
    ensuref(total <= 3600, "Total time must be at most 3600 seconds, got %d", total);
    ensuref(total % 10 == 0, "Total time must be a multiple of 10 seconds, got %d", total);

    inf.readEof();
}
