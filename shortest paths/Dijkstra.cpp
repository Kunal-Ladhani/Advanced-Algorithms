#include<bits/stdc++.h>
#include<limits.h>
using namespace std;

#define mod 1000000007
#define si(x) scanf("%d", &x)
#define sll(x) scanf("%lld", &x)
#define pi(x) printf("%d\n", x)
#define pll(x) printf("%lld\n", x)
#define LL long long int
#define ii pair<int, int>
#define vii vector<pair<int, int> >
#define vi vector<int>
#define adjList vector<vector<int> >
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define rep(i, z, q) for(i = z; i < q; i++)
#define rev(i, z, q) for(i = z; i > q; i--)
#define INF 1061109567

#define gc getchar_unlocked
int read_int() {
  char c = gc();
  while(c<'0' || c>'9') c = gc();
  int ret = 0;
  while(c>='0' && c<='9') {
    ret = 10 * ret + c - 48;
    c = gc();
  }
  return ret;
}

LL d1[10010], d2[10010];
int i, n, k, m, s, t, x, y, w;

void shortest_path(LL dis[], int source, vector<vii> adj) {
  
  priority_queue <ii, vii, greater<ii > > p;
  int d, u;
  dis[source] = 0;
  p.push(ii(0, source));
  
  while(!p.empty()) {
    
    ii temp = p.top();
    p.pop();
    d = temp.fi;
    u = temp.se;
    
    if(d > dis[u]) continue;
    
    for(vii::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
      if((LL)(d + (*it).fi) < dis[(*it).se]) {
	dis[(*it).se] = (LL)(d + (*it).fi);
	p.push(ii(dis[(*it).se], (*it).se));
      }
    }
  }
  
  return;
}

int main() {

  int T;

  T = read_int();
  
  while(T--) {

    vector<vii> adj1, adj2;
    
    n = read_int();
    m = read_int();
    k = read_int();
    s = read_int();
    t = read_int();
  
    rep(i, 1, n+1) 
      d1[i] = d2[i] = INF;
    
    adj1.resize(n+1);
    adj2.resize(n+1);
    
    rep(i, 1, m+1) {

      x = read_int();
      y = read_int();
      w = read_int();
  
      adj1[x].pb(ii(w, y));
      adj2[y].pb(ii(w, x));
    }
    
    shortest_path(d1, s, adj1);
    
    LL ans = d1[t];
    
    shortest_path(d2, t, adj2);
    
    while(k--) {

      x = read_int();
      y = read_int();
      w = read_int();
      
      ans = min(ans, min(d1[x] + d2[y] + w, d1[y] + d2[x] + w));
    }
    
    if(ans == INF)
      cout<<"-1"<<endl;
    else 
      cout<<ans<<endl;  
  }
  
  return 0;
}


