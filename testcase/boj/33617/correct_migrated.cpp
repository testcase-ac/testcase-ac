#include <iostream>
#include <vector>

struct Point
{
    size_t y;
    size_t x;
};

int main()
{
    size_t N;
    
    std::cin >> N;
    
    std::cout << ((N % 2 == 0) ? (N - 1) * (N + 1) - 1 : N * (N - 1)) << '\n';
    std::cout << 1 << ' ' << 1 << '\n';
    
    for (size_t i = 1; i < N; i++)
    {
        if (!(i % 2 == 0))
        {
            if (N % 2 == 0 && i != 1)
            {
                std::cout << N << ' ';
                for (size_t j = N; j >= 1; j--)
                {
                    std::cout << i << ' ' << j << ' ';
                }
                std::cout << '\n';
            }

            Point cp = Point{i, 1};
            Point con = Point{i, N + 1};
            
            for (size_t j = 1; j <= N; j++)
            {
                bool moved = false;
                std::cout << N << ' ';
                
                for (size_t k = 1; k <= N; k++)
                {
                    if (j % 2 == 1)
                    {
                        if (!moved && cp.x == con.x - 1)
                        {
                            cp.y++;
                            moved = true;
                        }
                        else
                        {
                            cp.x++;
                        }
                    }
                    else
                    {
                        if (!moved && cp.x == con.x - 1)
                        {
                            cp.y--;
                            moved = true;
                        }
                        else
                        {
                            cp.x--;
                        }
                    }
                    
                    std::cout << cp.y << ' ' << cp.x << ' ';
                }
                
                con.x--;
                std::cout << '\n';
            }
        }
        else
        {
            if (N % 2 == 0)
            {
                std::cout << N << ' ';
                for (size_t j = 1; j <= N; j++)
                {
                    std::cout << i << ' ' << j << ' ';
                }
                std::cout << '\n';
            }
                
            Point cp = Point{i, N};
            Point con = Point{i, 0};
            
            for (size_t j = 1; j <= N; j++)
            {
                bool moved = false;
                std::cout << N << ' ';
                
                for (size_t k = 1; k <= N; k++)
                {
                    if (j % 2 == 1)
                    {
                        if (!moved && cp.x == con.x + 1)
                            cp.y++, moved = true;
                        else
                            cp.x--;
                    }
                    else
                    {
                        if (!moved && cp.x == con.x + 1)
                            cp.y--, moved = true;
                        else
                            cp.x++;
                    }
                    
                    std::cout << cp.y << ' ' << cp.x << ' ';
                }
                
                con.x++;
                std::cout << '\n';
            }
        }
    }
}
