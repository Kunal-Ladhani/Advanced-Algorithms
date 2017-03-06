/* Rishabh Arora
   IIIT-Hyderabad */

#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

typedef pair<int,int> II;
typedef vector<int> VI;
typedef vector<II> VII;
typedef long long int LL;
typedef unsigned long long int ULL;
typedef vector<VI> adjList;

#define mod 1000000007
#define rep(i, a, b) for(i = a; i < b; i++)
#define rev(i, b, a) for(i = b; i > a; i--)
#define REP(i, n) for(i = 1; i <= n; i++)
#define pr0(arr, n) rep(i, 0, n) cout<<arr[i]<<" "; cout<<endl;
#define pr1(arr, n) rep(i, 1, n+1) cout<<arr[i]<<" "; cout<<endl;
#define INF INT_MAX
#define gc getchar_unlocked
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SET(a,b) memset(a, b, sizeof(a))
#define gu getchar
#define pu putchar
#define SI(n) scanf("%d",&n)
#define PI(n) printf("%d\n",n)
#define SLL(n) scanf("%lld",&n)
#define PLL(n) printf("%lld\n",n)

#define TRACE

#ifdef TRACE
#define trace1(x)                cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;
#define trace5(a, b, c, d, e)    cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl;
#define trace6(a, b, c, d, e, f) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << " | " << #f << ": " << f << endl;

#else

#define trace1(x)
#define trace2(x, y)
#define trace3(x, y, z)
#define trace4(a, b, c, d)
#define trace5(a, b, c, d, e)
#define trace6(a, b, c, d, e, f)

#endif

//fast io using cin/cout
//ios::sync_with_stdio(false);	cin.tie(NULL);

bool taken[1010];
int T[1010], L[1010], P[1010][30];
adjList adj;

void dfs(int v) { 
  
  taken[v] = true;
  
  for(auto it : adj[v]) 
    if(!taken[it])
      T[it] = v, L[it] = L[v]+1, dfs(it);
  
  return;
}

void process(int N) { 
  
  int i, j;
  
  SET(P, -1);
  
  REP(i, N)
    P[i][0] = T[i];
  
  for(j = 1; (1 << j) < N; j++) 
    REP(i, N)
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
  
  //finding ancestor at the same level

  rev(i, log, -1) {
    //cout<<p<<endl;
    if(L[p] - (1 << i) >= L[q])
      p = P[p][i];
  }

  //one of the node is ancestor
  if(p == q)
    return p;
  
  // cout<<log<<endl;
  // cout<<p<<endl;

  //same level but ancestor is not found yet
  rev(i, log, -1) 
    if(P[p][i] != -1 && P[p][i] != P[q][i])
      p = P[p][i], q = P[q][i];
  
  return T[p];
}

int main() {

  int Test, t, i, N, C, x, a, b, q;
  int j;

  cin>>Test;
  
  REP(t, Test) {

    SET(taken, false);
    
    cin>>N;    
    adj.resize(N+1);
    
    REP(i, N)  {
      
      cin>>C;
      
      while(C > 0) { 
	cin>>x;
	adj[i].PB(x);
	adj[x].PB(i);
	C--;
      }
    }
    
    T[1] = -1;
    L[1] = 0;
    dfs(1);
    process(N);
    
    //  pr1(L, N);
    // REP(i, N) {
      
    //   cout<<i<<":";

    //   for(j = 0; 1 << j <= N; j++) 
    // 	cout<<j<<"->"<<P[i][j]<<" ";

    //   cout<<endl;
    // }

    cin>>q;
    VI v;

    while(q--) { 
      cin>>a>>b;
      v.PB(LCA(a, b));
    }
    
    cout<<"Case "<<t<<":"<<endl;
    
    for(auto it : v)
      cout<<it<<endl;
    
    REP(i, N)
      adj[i].clear();
  }

  return 0;
}
