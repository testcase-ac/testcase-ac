#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read number of animals
    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();
    
    // Read coordinates
    set<pair<int,int>> coords;
    for (int i = 1; i <= n; i++) {
        int x = inf.readInt(0, 1000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000000, "y_i");
        inf.readEoln();
        
        // No duplicates
        ensuref(!coords.count({x,y}),
                "Duplicate point at index %d: (%d, %d)", i, x, y);
        // Point must not coincide with the starting point (0,0)
        ensuref(!(x == 0 && y == 0),
                "Point at index %d equals starting point (0, 0)", i);
        coords.insert({x,y});
    }
    
    // Read time intervals
    for (int i = 1; i <= n; i++) {
        int v = inf.readInt(0, 1000000000, "v_i");
        inf.readSpace();
        int w = inf.readInt(0, 1000000000, "w_i");
        inf.readEoln();
        
        // Start time must be strictly less than end time
        ensuref(v < w,
                "Invalid time interval at index %d: [%d, %d]", i, v, w);
    }
    
    inf.readEof();
    return 0;
}
