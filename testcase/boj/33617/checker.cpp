#include <vector>
#include <algorithm>
#include "testlib.h"

struct Point
{
    int y;
    int x;
};

inline int GetDist(Point p1, Point p2)
{
    return std::abs(p1.y - p2.y) + std::abs(p1.x - p2.x);
}

int main(int argc, char* argv[])
{
    registerTestlibCmd(argc, argv);

    int N = inf.readInt();

    int total_time = ouf.readInt(1, N*N, "total_time");

    int sy = ouf.readInt(1, N, "start_row");
    int sx = ouf.readInt(1, N, "start_col");
    sy--, sx--;

    std::vector<std::vector<bool>> grid(N, std::vector<bool>(N, false));
    grid[sy][sx] = true;
    Point cp = Point{sy, sx};
    std::vector<Point> sfp_arr = { cp };

    for (int t = 0; t < total_time; t++)
    {
        int m = ouf.readInt(1, N, "curr_move_count, m");

        for (int i = 0; i < m; i++)
        {
            int ny = ouf.readInt(1, N, "corr_move_row_pos, cy");
            int nx = ouf.readInt(1, N, "corr_move_col_pos, cx");

            Point np = Point{ny - 1, nx - 1};

            if (GetDist(cp, np) != 1)
                quitf(_wa, "Not adjacent move at sec=%d step=%d: (%d,%d)->(%d,%d)", t, i, cp.y+1, cp.x+1, nx+1, ny+1);
            
            if (!grid[np.y][np.x])
            {
                sfp_arr.push_back(np);
                grid[np.y][np.x] = true;
            }
            cp = np;
        }

        std::vector<Point> nsfp_arr;
        std::vector<Point> erase_p_arr;
        for (Point p : sfp_arr)
        {
            Point np_arr[4] = { Point{p.y - 1, p.x}, Point{p.y + 1, p.x}, Point{p.y, p.x - 1}, Point{p.y, p.x + 1}};
            bool erase = false;

            for (Point np : np_arr)
            {
                if (np.y < 0 || np.y >= N || np.x < 0 || np.x >= N) continue;

                if (grid[np.y][np.x] == false) erase = true;
            }

            if (!erase) nsfp_arr.push_back(p);
            else        erase_p_arr.push_back(p);
        }

        std::swap(sfp_arr, nsfp_arr);
        
        for (Point p : erase_p_arr)
        {
            grid[p.y][p.x] = false;
        }

        if (grid[cp.y][cp.x] == false)
        {
            grid[cp.y][cp.x] = true;
            sfp_arr.push_back(cp);
        }
    }

    if (sfp_arr.size() == N * N)
    {
        quitf(_ok, "caught the cheater");
    }
    else
    {
        quitf(_wa, "cheater can live");
    }
}
