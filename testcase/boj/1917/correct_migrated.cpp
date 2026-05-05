#include <iostream>
#include <array>
#include <limits>
#include <cstdint>
#include <queue>

struct Point
{
    size_t y;
    size_t x;
};

enum class Planar : uint8_t
{
    kNone = 0,
    kBase = 1,
    kUp = 2,
    kLeft = 3,
    kDown = 4,
    kRight = 5,
    kOp = 6
};

std::array<Planar, 4> GetAdjacentPlanars(Planar _cur_planar, Planar _adj_planar, size_t _dir)
{
    constexpr std::array<std::array<Planar, 4>, 7> kDefault
    {
        std::array<Planar, 4>{ Planar::kNone, Planar::kNone, Planar::kNone, Planar::kNone }, // kNone
        std::array<Planar, 4>{ Planar::kUp, Planar::kLeft, Planar::kDown, Planar::kRight }, // Base
        std::array<Planar, 4>{ Planar::kOp, Planar::kLeft, Planar::kBase, Planar::kRight }, // kUp
        std::array<Planar, 4>{ Planar::kUp, Planar::kOp, Planar::kDown, Planar::kBase }, // kLeft
        std::array<Planar, 4>{ Planar::kBase, Planar::kLeft, Planar::kOp, Planar::kRight }, // kDown
        std::array<Planar, 4>{ Planar::kUp, Planar::kBase, Planar::kDown, Planar::kOp }, // kRight
        std::array<Planar, 4>{ Planar::kUp, Planar::kRight, Planar::kDown, Planar::kLeft } //kOp
    };
    
    if (_adj_planar == Planar::kNone)
    {
        return kDefault[static_cast<size_t>(_cur_planar)];
    }
    else
    {
        std::array<Planar, 4> res;
        size_t diff = 5;
        
        for (size_t i = 0; i < 4; i++)
        {
            if (kDefault[static_cast<size_t>(_cur_planar)][i] == _adj_planar)
            {
                diff = _dir > i ? _dir - i : 4 - (i - _dir);
                break;
            }
        }
        
        if (diff == 5)
        {
            return kDefault[0];
        }
        
        for (size_t i = 0; i < 4; i++)
        {
            res[i] = kDefault[static_cast<size_t>(_cur_planar)][(4 + i - diff) % 4];
        }
        
        return res;
    }
}

int main()
{
    for (size_t tc = 0; tc < 3; tc++)
    {
        std::array<std::array<bool, 8>, 8> paper = { 0 };
        std::array<std::array<Planar, 8>, 8> type_grid = { Planar::kNone };
        Point base_p{ 0, 0 };
        bool available = true;
        std::array<bool, 7> exist = { false };
        
        for (size_t i = 1; i <= 6; i++)
        {
            for (size_t j = 1; j <= 6; j++)
            {
                std::cin >> paper[i][j];
                
                if (base_p.y == 0 && paper[i][j])
                {
                    base_p = Point{i, j};
                }
            }
        }
        
        type_grid[base_p.y][base_p.x] = Planar::kBase;
        exist[static_cast<size_t>(Planar::kBase)] = true;
        std::queue<Point> que;
        que.push(base_p);
        
        while (!que.empty())
        {
            Point p = que.front(); que.pop();
            
            const std::array<Point, 4> nps = 
            {
                Point{p.y - 1, p.x}, 
                Point{p.y, p.x - 1}, 
                Point{p.y + 1, p.x}, 
                Point{p.y, p.x + 1}
            };
            
            size_t adj_dir = 0;
            Planar adj_planar = Planar::kNone;
            
            for (size_t i = 0; i < 4; i++)
            {
                Point np = nps[i];
                if (type_grid[np.y][np.x] != Planar::kNone)
                {
                    adj_dir = i;
                    adj_planar = type_grid[np.y][np.x];
                    break;
                }
            }
            
            const std::array<Planar, 4> nts = GetAdjacentPlanars(type_grid[p.y][p.x], adj_planar, adj_dir);
            
            for (size_t i = 0; i < 4; i++)
            {
                Point np = nps[i];
                Planar nt = nts[i];
                
                if (!paper[np.y][np.x]) continue;
                
                if (type_grid[np.y][np.x] == Planar::kNone)
                {
                    if (exist[static_cast<size_t>(nt)]) available = false;
                    exist[static_cast<size_t>(nt)] = true;
                    type_grid[np.y][np.x] = nt;
                    que.push(np);
                }
                else if (type_grid[np.y][np.x] != nt)
                {
                    available = false;
                    que = std::queue<Point>();
                }
            }
        }
        
        std::cout << (available ? "yes" : "no") << std::endl;
    }
}
