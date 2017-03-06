/* Rishabh Arora
   IIIT-Hyderabad */

#include <bits/stdc++.h>
using namespace std;

typedef pair<long long int, long long int> II;
typedef vector<int> VI;
typedef vector<II> VII;
typedef long long int LL;
typedef unsigned long long int ULL;

#define rep(i, a, b) for(i = a; i < b; i++)
#define rev(i, a, b) for(i = a; i > b; i--)
#define INF INT_MAX
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SET(a,b) memset(a, b, sizeof(a))

//debugging statements
#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

const int N = 1e5+10;
const int mod = 1e9+7;

struct node {
	LL u, i, w;
};

LL start, ans[N], dp1[N], dp2[N], dp1v[N], dp2v[N], timer, low[N], in[N], par[N], btree[N];
vector<vector<node> > g;
vector<VII> tree;
vector<queue<LL > > Q;
LL i;
bool vis[N], isbridge[2*N];
//marking the bridges in a graph 
void dfs0(int v) {
	vis[v] = true;
	in[v] = low[v] = timer++;
	for(auto U : g[v]) {
		LL i = U.i, u = U.u;
		if(!vis[u]) {
			par[u] = v;
			dfs0(u);
			low[v] = min(low[u], low[v]);
			if(low[u] > in[v]) {
				isbridge[i] = true;
			}
		}
		else if(u != par[v]) {
			low[v] = min(low[v], in[u]);
		}
	}
	return;
}

//the real work
void dfs1(int v) {
	start = v;
	Q[v].push(v);
	vis[v] = true;
	btree[v] = v;
	while(!Q[v].empty()) {
		int u = Q[v].front();
		Q[v].pop();
		for(auto x : g[u]) {
			if(isbridge[x.i] && !vis[x.u]) {
				tree[v].PB({x.u, x.w});
				tree[x.u].PB({v, x.w});
				//trace(v, x.u);
				dfs1(x.u);
			}
			else if(!vis[x.u]) {
				Q[v].push(x.u);
				vis[x.u] = true;
				btree[x.u] = v;
			}
		}
	}
	return ;
}
