#include <bits/stdc++.h>
using namespace std;
namespace dlx {
	struct node {
		int x,s;
		node *c,*u,*d,*l,*r,*n;
	};
	void cover(node* c) {
		c->n->l=c->l;
		c->l->n=c->n;
		for(node* i=c->d;i!=c;i=i->d) {
			for(node* j=i->n;j!=i;j=j->n) {
				j->d->u=j->u;
				j->u->d=j->d;
				j->c->s--;
			}
		}
	} void uncover(node* c) {
		for(node* i=c->u;i!=c;i=i->u) {
			for(node* j=i->l;j!=i;j=j->l) {
				j->d->u=j;
				j->u->d=j;
				j->c->s++;
			}
		} c->n->l=c;
		c->l->n=c;
	} bool dfs(node* h,vector<int>&v) {
		if(h->n==h) return 1;
		node* p=0;
		int m=2e9;
		for(node* i=h->n;i!=h;i=i->n) {
			if(i->s<m) {
				if(i->s==0) return 0;
				m=i->s;
				p=i;
			}
		} cover(p);
		for(node* i=p->d;i!=p;i=i->d) {
			v.push_back(i->x);
			for(node* j=i->n;j!=i;j=j->n) cover(j->c);
			if(dfs(h,v)) return 1;
			v.pop_back();
			for(node* j=i->l;j!=i;j=j->l) uncover(j->c);
		} uncover(p);
		return 0;
	} vector<int> solve(vector<vector<int>>&a) {
		int m=a[0].size();
		vector<node> c(m);
		node h;
		h.n=&c[0];
		h.l=&c[m-1];
		for(int i=0;i<m;i++) {
			c[i].s=0;
			c[i].u=&c[i];
			c[i].d=&c[i];
			c[i].l=i?&c[i-1]:&h;
			c[i].n=i+1<m?&c[i+1]:&h;
		} vector<node*> t;
		for(int i=0;i<a.size();i++) {
			node* q=0;
			for(int j=0;j<m;j++) if(a[i][j]) {
				node* p=new node;
				p->x=i;
				p->c=&c[j];
				p->u=c[j].u;
				p->d=&c[j];
				if(q) {
					p->l=q;
					p->n=q->n;
					q->n->l=p;
					q->n=p;
				} else p->l=p->n=p;
				c[j].u->d=p;
				c[j].u=p;
				c[j].s++;
				q=p;
				t.push_back(p);
			}
		} vector<int> v;
		dfs(&h,v);
		for(auto p:t) delete p;
		return v;
	}
}
int b[9][9];
int main() {
    int p,q,r;
    for(int x=1;x<=81;x++) {
        vector<vector<int>> a;
        vector<tuple<int,int,int>> d;
        cin>>p>>q>>r;
        p--;q--;
        if(b[p][q]>0) {
            cout<<x;
            return 0;
        } else b[p][q]=r;
	    for(int i=0;i<9;i++) for(int j=0;j<9;j++) {
	    	auto f=[&](int k) {
	    		vector<int> v(324);
	    		v[i*9+j]=1;
	    		v[81+i*9+k]=1;
	    		v[162+j*9+k]=1;
	    		v[243+(i/3*3+j/3)*9+k]=1;
	    		a.push_back(v);
	    		d.push_back({i,j,k});
	    	};
	    	if(b[i][j]) f(b[i][j]-1);
	    	else for(int k=0;k<9;k++) f(k);
	    } if(dlx::solve(a).size()!=81) {
	        cout<<x;
	        return 0;
	    }
    } cout<<-1;
}
