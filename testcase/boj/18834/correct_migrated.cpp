#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
using ll=long long;

namespace P4{
    const vector<int>around[14]={{12,1,13,9},{2,5,0},{3,4,1,12},{7,2,10},{2,7,5},{1,4,8,13},{9,13,8,11},{11,8,4,3},{5,7,6},{10,0,6},{3,12,9,11},{10,6,7},{2,0,10},{0,5,6}};
    struct State{int b,d;};
    int encode(State s){return s.b*14+s.d;}
    State decode(int x){return{x/14,x%14};}
    State find_nxt(State x,char dir){
        int b=x.b,d=x.d;
        int k=-1,sz=around[b].size(),nb=-1;
        for(int i=0;i<(int)around[b].size();i++)
            if(around[b][i]==d){k=i;break;}
        if(dir=='D')
            nb=x.d;
        if(dir=='L')
            nb=around[b][(k-1+sz)%sz];
        if(dir=='R')
            nb=around[b][(k+1)%sz];
        if(dir=='U'){
            if(sz==3)return x;
            nb=around[b][(k+2)%sz];
        }
        return{nb,x.b};
    }
    using Func=array<int,196>;
    Func make_func(char c){
        Func f;
        for(int i=0;i<196;i++){
            State s=decode(i);
            s=find_nxt(s,c);
            f[i]=encode(s);
        }
        return f;
    }
    Func compose(const Func&f,const Func&g){
        Func h;
        for(int i=0;i<196;i++)
            h[i]=g[f[i]];
        return h;
    }
    Func power(Func base,long long n){
        Func res;
        for(int i=0;i<196;i++)res[i]=i;
        while(n){
            if(n&1)res=compose(res,base);
            base=compose(base,base);
            n>>=1;
        }
        return res;
    }
    void sol(){
        map<string,int>name_to_idx={{"구데기컵",0},{"하이퍼",1},{"0초제출",2},{"알파고",3},{"박승원",4},{"애이불비",5},{"배중률교",6},{"미니앨범",7},{"주령구",8},{"QR",9},{"퍼즐헌트",10},{"데쿼리",11},{"연속합",12},{"대결!",13}};
        const vector<string>idx_to_name={"구데기컵","하이퍼","0초제출","알파고","박승원","애이불비","배중률교","미니앨범","주령구","QR","퍼즐헌트","데쿼리","연속합","대결!"};
       
        string b,d,s;
        cin>>b>>d>>s;
        State st={name_to_idx[b],name_to_idx[d]};
        stack<Func>st_func;
        stack<int>st_pos;
        Func cur;
        for(int i=0;i<196;i++)cur[i]=i;
        for(int i=0;i<s.size();i++){
            char c=s[i];
            if(c=='L'||c=='R'||c=='U'||c=='D'){
                cur=compose(cur,make_func(c));
            }
            else if(c=='('){
                st_func.push(cur);
                st_pos.push(i);
                for(int j=0;j<196;j++)cur[j]=j;
            }
            else if(c==')'){
                int j=i+1;
                long long num=0;
                while(j<s.size()&&isdigit(s[j])){
                    num=num*10+(s[j]-'0');
                    j++;
                }
                i=j-1;
                cur=power(cur,num);
                Func prev=st_func.top();st_func.pop();
                cur=compose(prev,cur);
            }
        }
        int x=encode(st);
        x=cur[x];
        State res=decode(x);
        cout<<idx_to_name[res.b]<<'\n';
    }
}
int main(){
  P4::sol();
  return 0;
}
