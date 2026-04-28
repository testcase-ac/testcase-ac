#include <cstdio>

char buf[1<<17];

inline char read()
{
    static int idx = 1<<17;
    if (idx == 1<<17)
    {
        fread(buf, 1, 1<<17, stdin);
        idx = 0;
    }
    return buf[idx++];
}
inline int readInt()
{
    int sum = 0;
    char now = read();
    
    while (now == 10 || now == 32) now = read();
    while (now >= 48 && now <= 57)
    {
        sum = sum*10 + now-48;
        now = read();
    }
    
    return sum;
}
int main()
{
	int t = readInt();
	
	while (t--)
	{
		int n = readInt();
        
        int L[n+1];
		for (int i = 1; i <= n; ++i) L[i] = readInt();
		
		bool visited[n+1]{};
		int ans = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (visited[i]) continue;
			
			int v = i;
			while (!visited[v])
			{
				visited[v] = 1;
				v = L[v];
			}
			
			int w = i;
			while (w != v)
			{
				ans++;
				w = L[w];
			}
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
}

// https://www.acmicpc.net/source/7702364
