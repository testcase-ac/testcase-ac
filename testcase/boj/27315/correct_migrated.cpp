#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <algorithm>

struct Entry
{
    uint32_t idea;
    uint32_t impl;    
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    size_t N, M;
    uint32_t HD, HP;
    const auto idea_comp = [](const Entry& e1, const Entry& e2)->bool
    {
        return e1.idea > e2.idea;
    };
    const auto impl_comp = [](const Entry& e1, const Entry& e2)->bool
    {
        return e1.impl > e2.impl;
    };
    
    std::cin >> N >> M;
    
    std::priority_queue<Entry, std::vector<Entry>, decltype(idea_comp)> idea_que(idea_comp);
    std::priority_queue<Entry, std::vector<Entry>, decltype(impl_comp)> impl_que(impl_comp);
    
    for (size_t i = 0; i < N; i++)
    {
        uint32_t D, P;
        bool tc, edit;
        
        std::cin >> D >> P >> tc >> edit;
        
        if (edit)
        {
            D = (D + 1) / 2;
            P = P / 2;
        }
        
        if (tc)
        {
            P = 0;
        }
        idea_que.push(Entry{D, P});
    }
    
    std::cin >> HD >> HP;
    
    size_t solved = 0;
    int64_t wa = 0;
    
    for (size_t i = 0; i < M; i++)
    {
        while (!idea_que.empty() && idea_que.top().idea <= HD)
        {
            Entry e = idea_que.top();
            idea_que.pop();
            
            impl_que.push(e);
        }
        
        if (!impl_que.empty())
        {
            Entry e = impl_que.top();
            impl_que.pop();
            
            wa += (HP >= e.impl) ? 0 : e.impl - HP;
            
            HD++, HP++;
        }
        else
        {
            wa = -1;
            break;
        }
    }
    
    std::cout << wa << std::endl;
}
