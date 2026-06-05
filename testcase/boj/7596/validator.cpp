#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int scenario = 1;
    int totalTracks = 0;
    int totalNameChars = 0;

    while (true) {
        int n = inf.readInt(0, 200, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        setTestCase(scenario);
        ensuref(n > 1, "n must be greater than 1, got %d", n);

        totalTracks += n;
        // CHECK: the statement has no scenario-count bound; cap total tracks to keep validation practical.
        ensuref(totalTracks <= 1000000, "too many total tracks: %d", totalTracks);

        for (int i = 0; i < n; ++i) {
            string name = inf.readLine("[^]{1,250}", "name");
            ensuref(isalpha(static_cast<unsigned char>(name[0])),
                    "track name %d must begin with an alphabetic character", i + 1);

            totalNameChars += static_cast<int>(name.size());
            // CHECK: the statement has no total input-size bound; cap name text near the local string limit.
            ensuref(totalNameChars < 10000000, "too many total name characters: %d", totalNameChars);
        }

        ++scenario;
    }

    inf.readEof();
}
