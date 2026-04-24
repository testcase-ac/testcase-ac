#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are exactly 5 lines, each with one integer in [100, 2000].
    int price_sangdeok = inf.readInt(100, 2000, "price_sangdeok");
    inf.readEoln();
    int price_joongdeok = inf.readInt(100, 2000, "price_joongdeok");
    inf.readEoln();
    int price_hadeok = inf.readInt(100, 2000, "price_hadeok");
    inf.readEoln();
    int price_cola = inf.readInt(100, 2000, "price_cola");
    inf.readEoln();
    int price_cider = inf.readInt(100, 2000, "price_cider");
    inf.readEoln();

    // No further content
    inf.readEof();

    return 0;
}
