#include <iostream>
#include <array>
#include <queue>

struct Point
{
    size_t y;
    size_t x;
};

enum class Direction : size_t
{
    kNone = 0,
    kNorth = 1,
    kWest = 2,
    kSouth = 3,
    kEast = 4
};

enum class Planar : uint8_t
{
    kNone = 0,
    kBottom = 1,
    kNorth = 2,
    kWest = 3,
    kSouth = 4,
    kEast = 5,
    kTop = 6
};

class Dice
{
public:
    Dice();
    Dice(const Dice& _dice) = default;
    void roll_north();
    void roll_west();
    void roll_south();
    void roll_east();
    Dice roll_north_copy() const { Dice tmp = *this; tmp.roll_north(); return tmp; }
    Dice roll_west_copy() const { Dice tmp = *this; tmp.roll_west(); return tmp; }
    Dice roll_south_copy() const { Dice tmp = *this; tmp.roll_south(); return tmp; }
    Dice roll_east_copy() const { Dice tmp = *this; tmp.roll_east(); return tmp; }
    void roll(Direction _dir);
    
    Planar bottom() const { return bottom_; }
    Planar north() const { return north_; }
    Planar west() const { return west_; }
    Planar south() const { return south_; }
    Planar east() const { return east_; }
    Planar top() const { return top_; }

private:
    Planar bottom_;
    Planar north_;
    Planar west_;
    Planar south_;
    Planar east_;
    Planar top_;
};

Dice::Dice() : 
bottom_{Planar::kBottom}, north_(Planar::kNorth), west_(Planar::kWest), 
south_(Planar::kSouth), east_(Planar::kEast), top_(Planar::kTop)
{}
     

void Dice::roll_north()
{
    std::swap(north_, bottom_); std::swap(top_, north_); std::swap(south_, top_);
}

void Dice::roll_west()
{
    std::swap(west_, bottom_), std::swap(top_, west_), std::swap(east_, top_);
}

void Dice::roll_south()
{
    std::swap(south_, bottom_), std::swap(top_, south_), std::swap(north_, top_);
}

void Dice::roll_east()
{
    std::swap(east_, bottom_), std::swap(top_, east_), std::swap(west_, top_);
}

void Dice::roll(Direction _dir)
{
    switch (_dir)
    {
        case Direction::kNorth:
            roll_north(); break;
        case Direction::kWest:
            roll_west(); break;
        case Direction::kSouth:
            roll_south(); break;
        case Direction::kEast:
            roll_east(); break;
    }
}

using NumGrid = std::array<std::array<size_t, 8>, 8>;
using PlanarGrid = std::array<std::array<Planar, 8>, 8>;

int main()
{
    Point start_p, op_p;
    NumGrid num_grid = { 0 };
    PlanarGrid planar_grid = { Planar::kNone };
    bool available = true;
    std::array<bool, 7> exist = { false };
    
    for (size_t i = 1; i <= 6; i++)
    {
        for (size_t j = 1; j <= 6; j++)
        {
            std::cin >> num_grid[i][j];
            
            if (num_grid[i][j] == 1) start_p.y = i, start_p.x = j;
        }
    }
    
    std::queue<std::pair<Point, Dice>> que;
    planar_grid[start_p.y][start_p.x] = Planar::kBottom;
    exist[static_cast<size_t>(Planar::kBottom)] = true;
    que.push(std::make_pair(start_p, Dice{}));
    
    while (!que.empty())
    {
        auto [p, d] = que.front(); que.pop();
     
        std::array<Point, 4> nps = 
        { 
            Point{p.y - 1, p.x},
            Point{p.y, p.x - 1},
            Point{p.y + 1, p.x},
            Point{p.y, p.x + 1}
        };
        
        std::array<Dice, 4> nds = 
        {
            d.roll_north_copy(),
            d.roll_west_copy(),
            d.roll_south_copy(),
            d.roll_east_copy()
        };
        
        for (size_t i = 0; i < 4; i++)
        {
            Point np = nps[i];
            Dice nd = nds[i];
            
            if      (num_grid[np.y][np.x] != 0 && planar_grid[np.y][np.x] == Planar::kNone)
            {
                exist[static_cast<size_t>(nd.bottom())] = true;
                planar_grid[np.y][np.x] = nd.bottom();
                que.push(std::make_pair(np, nd));
                
                if (nd.bottom() == Planar::kTop) op_p = np;
            }
            else if (num_grid[np.y][np.x] != 0 && planar_grid[np.y][np.x] != nd.bottom())
            {
                available = false;
                que = std::queue<std::pair<Point, Dice>>();
                break;
            }
        }
    }
    
    for (size_t i = 1; i <= 6; i++)
    {
        available &= exist[i];
    }
    
    std::cout << (available ? num_grid[op_p.y][op_p.x] : 0);
}
