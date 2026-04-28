from collections import deque
def ddd(x,g,ass,dist):
    global done
    for I in g[x]:
        if I[-1]>dist:continue
        i=I[0]
        if done[i]:continue
        done[i]=True
        if ass[i]==-1 or ddd(ass[i],g,ass,dist):
            ass[i]=x
            return True
    return False
def match(g,m,dist):
    ass=[-1]*(m+1)
    n=len(g)
    global done
    a=0
    for i in range(n):
        done=[False]*(m+1)
        if ddd(i,g,ass,dist):a+=1
    return a

curid=0
idmap={}
def bfs(x,y,idx):
    global vis,q,b,curid
    impos=1
    vis[x][y]=True
    q.append((x,y,0))
    while q:
        X,Y,D=q.popleft()
        if g[X][Y]=='D':
            for DD in range(D,102):
                if (X,Y,DD) in idmap.keys():
                    b[idx].append((idmap[(X,Y,DD)],X,Y,DD))
                else:
                    curid+=1
                    idmap[(X,Y,DD)]=curid
                    b[idx].append((curid,X,Y,DD))
            impos=0
        for i in range(4):
            nx,ny=X+dx[i],Y+dy[i]
            if 0<=nx<n and 0<=ny<m and not vis[nx][ny]:
                if g[X][Y]=='D' and g[nx][ny]=='D':continue
                if g[nx][ny]!='X':
                    q.append((nx,ny,D+1))
                    vis[nx][ny]=True
    return impos

n,m=map(int,input().split())
g=[]
d=set()
pt=[]
for i in range(n):
    x=input()
    g.append(x)
    for j in range(m):
        if x[j]=='D':d.add((i,j))
        if x[j]=='.':pt.append((i,j))
dx,dy=[-1,1,0,0],[0,0,-1,1]

lpt=len(pt)
b=[[] for _ in range(lpt)]
for i in range(lpt):
    vis=[[False]*m for _ in range(n)]
    q=deque()
    if bfs(pt[i][0],pt[i][1],i):
        print('impossible')
        quit()
#print(b)
#print(idmap)
#직원: 갇힌 죄수 하나
#일: 탈출구와 거리의 쌍
#maxdist=3
left,right=0,101
while left<=right:
    mid=(left+right)//2
    if match(b,curid,mid)==lpt:
        right=mid-1
    else:left=mid+1
print(left)
