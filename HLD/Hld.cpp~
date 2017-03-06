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

// //debugging statements
// #define TRACE
// #ifdef TRACE
// #define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
// template <typename Arg1>
// void __f(const char* name, Arg1&& arg1){
// 	cerr << name << " : " << arg1 << std::endl;
// }
// template <typename Arg1, typename... Args>
// void __f(const char* names, Arg1&& arg1, Args&&... args){
// 	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
// }
// #else
// #define trace(...)
// #endif

const int N = 1e4+5;
const int LOGN = 15;

int n;
bool vis[N];
map<II, int> E;
vector<VII> adj;
int edge_ind[N], edge_val[N], seg[4*N], basearr[N], T[N], L[N], special[N], P[N][LOGN], sub[N], position[N], head[N], chno[N];	    

//SegTree ka bakchodi
void make_seg(int low, int high, int pos)
{
  if(low == high)
    {
      seg[pos] = basearr[low];
      return;
    }
  int mid = (low + high) >> 1;
  make_seg(low, mid, 2*pos);
  make_seg(mid+1, high, 2*pos+1);
  seg[pos] = max(seg[2*pos], seg[2*pos+1]);
  return;
}
//Range-max-query
int query_seg(int low, int high, int pos, int l, int r)
{
  if(l > r)
    return INT_MIN;
  else if(l <= low && r >= high)
    return seg[pos];
  else if( (r < low) || (l > high) )
    return INT_MIN;
  int mid = ( low + high) >> 1;
  return max( query_seg(low, mid, 2*pos, l, r), query_seg(mid + 1, high, 2*pos+1, l, r) );
}
//update in the seg-tree
void update_seg(int low, int high, int pos, int ind, int val)
{
  if(low == high && low == ind)
    {
      seg[pos] = val;
      return;
    }
  else if( (ind < low) || (ind > high) )
    return;
  int mid = (low + high ) >> 1;
  update_seg(low, mid, 2*pos, ind, val);
  update_seg(mid+1, high, 2*pos+1, ind, val);
  seg[pos] = max(seg[2*pos], seg[2*pos+1]);
  return;
}

//find parent, subTree-size, level wrt to root and special child and array edge_val and edge_ind
//edge_val stores the weight of the edge that will terminate on the (it.F)[The child]
//edge_ind stores the node at which the ith edge is stored
//The Map 'E' stores the pair of vertices corresponding to an edge
//L[] - level of a vertex wrt. to '1'{the root I've decided}
//T[] - the parent of a vertex, T[1] = -1{root};
//sub[] - the subtree size of a vertex
//special[] - stores the special child of a vertex (The one with the max subtree size in it's corresponding subtree)

void dfs(int v)
{
  int size = 1, val = -1, ind = -1;
  vis[v] = true;
  for(VII::iterator it = adj[v].begin(); it != adj[v].end(); it++)
    {
      if(!vis[(*it).F])
	{
	  L[(*it).F] = L[v]+1;
	  T[(*it).F] = v;
	  dfs((*it).F);
	  if( sub[(*it).F] > val)
	    {
	      val = sub[(*it).F];
	      ind = (*it).F;
	    }
	  size += sub[(*it).F];
	  edge_val[(*it).F] = (*it).S;   //edge_val saves the value of the edge that ends on it.F
	  edge_ind[E[MP((*it).F, v)]] = (*it).F;   //stores the node at which the edge ends;
	}
    }
  sub[v] = size;
  special[v] = ind;
  vis[v] = false;
  return;
}

//Function for LCA
void process(int N) { 
  int i, j;
  rep(i, 1, N+1)
    P[i][0] = T[i];
  for(j = 1; (1 << j) < N; j++) 
    rep(i, 1, N+1)
      if(P[i][j-1] != -1)
	P[i][j] = P[P[i][j-1]][j-1];
  return;
}

int LCA(int p, int q) { 
  int i;
  if(L[p] < L[q])
    swap(p, q);
  int log;
  for(log = 1; (1 << log) <= L[p]; log++);
  log--;
  rev(i, log, -1)
    {
      if(L[p] - (1 << i) >= L[q])
	p = P[p][i];
    }
 if(p == q)
   return p;
 rev(i, log, -1) 
   if(P[p][i] != -1 && P[p][i] != P[q][i])
     p = P[p][i], q = P[q][i];
 return T[p];
}

//Heavy-Light Decomposition Part :)
int ch = 1, pos = 1;
void HLD(int curr)
{
  if(head[ch] == -1)
    head[ch] = curr;   //storing the head of the chain 
  vis[curr] = true;
  chno[curr] = ch;     //storing the chain number of the current node 
  basearr[pos] = edge_val[curr];  //storing the value in the basearray on which the segment-tree will be build 
  position[curr] = pos++;      //storing the position in which the edge ending on 'curr' is stored in the basearray
  if(special[curr] != -1)
    HLD(special[curr]);
  for(VII::iterator it = adj[curr].begin(); it != adj[curr].end(); it++)
    if( (!vis[(*it).F]) & ((*it).F != special[curr]) )
      {
	ch++;
	HLD((*it).F);
      }
  vis[curr] = false;
  return;
}

int query(int a, int b)
{
  int L = LCA(a, b);
  //Query from a to LCA
  int temp = a, ans = 0;
  while(chno[temp] != chno[L])
    {
      ans = max(ans, query_seg(1, n, 1, position[head[chno[temp]]], position[temp]) );
      temp = T[head[chno[temp]]];
    }
  //considering pos[L]+1 because pos[L] will contain the edge from T[L]->L and that's not included in our path :)
  ans = max(ans, query_seg(1, n, 1, position[L]+1, position[temp]) );
  
  //Query from b to LCA
  temp = b;
  while(chno[temp] != chno[L] )
    {
      ans = max(ans, query_seg(1, n, 1, position[head[chno[temp]]], position[temp]) );
      temp = T[head[chno[temp]]];
    }
  ans = max(ans, query_seg(1, n, 1, position[L]+1, position[temp]));
  return ans;
}

//initialise everything 
void init(int n)
{
  T[1] = -1;
  L[1] = 0;
  int i, j;
  rep(i, 1, n+1)
    {
      head[i] = -1;
      special[i] = -1;
      rep(j, 0, 15)
	P[i][j] = -1;
      adj[i].clear();
    }
  rep(i, 1, 4*n+1)
    seg[i] = INT_MIN;
  E.clear();
  return;
}

#define SI(n) scanf("%d", &n);

int main()
{
  
  int t, i;
  SI(t);

  while(t--)
    {
      SI(n);
      adj.resize(n+1);
      init(n);
      int a, b, w;
      rep(i, 1, n)
	{
	  SI(a);SI(b);SI(w);
	  adj[a].PB(MP(b, w));
	  adj[b].PB(MP(a, w));
	  E[MP(a, b)] = i;
	  E[MP(b, a)] = i;
	}

      ch = 1, pos = 1;
      dfs(1);
      process(n);
      HLD(1);
      make_seg(1, n, 1);

      char str[10];
      
      while(1)
	{
	  scanf("%s", str);;
	  
	  if(strcmp(str, "DONE") == 0)
	    break;
	  
	  SI(a);
	  SI(b);
	  
	  if(str[0] == 'C')
	    {
	      basearr[position[edge_ind[a]]] = b;
	      update_seg(1, n, 1, position[edge_ind[a]], b);
	    }
	  else
	    printf("%d\n", query(a, b));
	}
    }
  
  return 0;
}
