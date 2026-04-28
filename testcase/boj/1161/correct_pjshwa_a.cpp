
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define N 50005
#define ll long long 
using namespace std;
 
int k,n,c,ans;
int sum[N];
struct COW{
    int x,y,w;
}cow[N];
int cmp(COW s1,COW s2) {return s1.x<s2.x;}
struct node1{
    int id;
    friend bool operator<(const node1 &s1,const node1 &s2) 
    {return cow[s1.id].y > cow[s2.id].y;}
};
node1 ins1(int idd){node1 w;w.id=idd;return w;}
struct node2{
    int id;
    friend bool operator<(const node2 &s1,const node2 &s2) 
    {return cow[s1.id].y < cow[s2.id].y;}
};
node2 ins2(int idd){node2 w;w.id=idd;return w;}
int solve()
{
    sort(cow+1,cow+k+1,cmp);
    priority_queue<node1>q1;
    priority_queue<node2>q2;
    int j=1,cnt=0;
    for(int i=1;i<=n;i++)
    {
        while(!q1.empty())
        {
            node1 p=q1.top();
            if(cow[p.id].y==i)
            {
                q1.pop();
                ans+=sum[p.id];
                cnt-=sum[p.id];
                sum[p.id]=0;
            }else{
                break;
            }
        }
        while(cow[j].x==i)
        {
            q1.push(ins1(j));
            q2.push(ins2(j));
            cnt+=cow[j].w;
            sum[j]=cow[j].w;
            j++;
        }
        while(cnt>c)
        {
            node2 p=q2.top();
            if(cnt-sum[p.id]>c) 
            {
                q2.pop();
                cnt-=sum[p.id];
                sum[p.id]=0;
            }else{
                sum[p.id]-=(cnt-c);
                cnt=c;
            }
        }
    }
    return ans;
}
 
int main()
{
	scanf("%d%d%d",&k,&n,&c);
	for(int i=1;i<=k;i++) scanf("%d%d%d",&cow[i].x,&cow[i].y,&cow[i].w);
	printf("%d",solve());
    return 0;
}
