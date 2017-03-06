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

const LL N = 1e5+2;
bool big[N];
LL ans[N], c[N], ac[N], sub[N], bigchild[N];
bool vis[N];
vector<VI> g;
LL cnt[N];

void dfs0(LL v)
{
  vis[v] = true;
  sub[v] = 1;
  bigchild[v] = -1;
  LL Max = -1;
  for(auto u: g[v])
    if(!vis[u])
      {
	dfs0(u);
	sub[v] += sub[u];
	if(sub[u] > Max)
	  {
	    Max = sub[u];
	    bigchild[v] = u;
	  }
      }
  vis[v] = false;
  return;
}

void add(LL j, LL v, LL p, LL x)
{
  cnt[c[v]] += x;

  if(x == 1)
    {
      if( cnt[c[v]] > ac[j])
	{
	  ans[j] = c[v];
	  ac[j] = cnt[c[v]];
	}
      else if(cnt[c[v]] == ac[j])
	ans[j] += c[v];
    }
  
  for(auto u : g[v])
    if(u != p  && !big[u])
      add(j, u, v, x);
  return;
}

void dfs1(LL v, LL p, bool keep)
{
  ac[v] = 0, ans[v] = 0;
  for(auto u: g[v])
    if( u != p  && u != bigchild[v])
      dfs1(u, v, false);
  
  if(bigchild[v] != -1)
    {
      dfs1(bigchild[v], v, true);
      big[bigchild[v]] = true;
      ans[v] = ans[bigchild[v]];
      ac[v] = ac[bigchild[v]];
    }
  
  add(v, v, p, 1);

  big[bigchild[v]] = false;
  if(keep == false)
    add(v, v, p, -1);
  
  vis[v] = false;
  return;
}
int main() {

  ios::sync_with_stdio(false);	
  cin.tie(NULL);

  LL n;

  cin>>n;

  LL i;

  rep(i, 1, n+1)
    cin>>c[i];

  LL u, v;

  g.resize(n+1);
  
  rep(i, 1, n)
    {
      cin>>u>>v;
      g[u].PB(v);
      g[v].PB(u);
    }

  dfs0(1);
  dfs1(1, 1, 1);
  rep(i, 1, n+1)
    cout<<ans[i]<<" ";
  cout<<endl;
  
  return 0;
}
