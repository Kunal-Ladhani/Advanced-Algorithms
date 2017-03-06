/* Rishabh Arora
   IIIT-Hyderabad */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> II;
typedef vector<int> VI;
typedef vector<II> VII;
typedef long long int LL;
typedef unsigned long long int ULL;

#define MAXSIZE 100005
#define mod 1000000007
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

//-------------Centroid Decomposition----------------//
//function to calculate the sizes of sub-trees
void dfs1(int v, int p) { 
  sub[v] = 1;
  for(auto it : adj[v])
    if( it != p)
      dfs1(it, v), sub[v] += sub[it];
  return;
}
//function that returns the centroid of a given sub-tree
int dfs2(int v, int p, int size) { 
  for(auto it : adj[v]) 
    if( (it != p) && (2*sub[it] > size) ) 
      return dfs2(it, v, size);
  return v;
}
//decomposition function
void decompose(int v, int p, int size) {
  dfs1(v, v);
  int centroid = dfs2(v, v, sub[v]);
  if(p == -1) p = centroid;
  parent[centroid] = p;
  for(auto &it : adj[centroid]) { 
    adj[it].erase(centroid);
    decompose(it, centroid);
  }
  adj[centroid].clear();
  return;
} 

int main() {

  ios::sync_with_stdio(false);	
  cin.tie(NULL);
  
  return 0;
}
