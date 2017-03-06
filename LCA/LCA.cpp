bool vis[N];
int T[N], L[N], P[N][LOGN];

void dfs(int v) { 
  vis[v] = true;
  for(auto u : g[v]) { 
    if(!vis[u]) {
      T[it] = v, L[it] = L[v]+1, dfs(it);
    }
  }
  return;
}

void process(int n) { 
  int i, j;
  SET(P, -1);
  rep(i, 1, n+1) {
    P[i][0] = T[i];
  }
  for(j = 1; (1 << j) < N; j++) { 
    rep(i, 1, n+1) {
      if(P[i][j-1] != -1) {
	       P[i][j] = P[P[i][j-1]][j-1];
       }
     }
   }
  return;
}

int LCA(int p, int q) { 
  int i;
  if(L[p] < L[q])
    swap(p, q);
  int log;
  for(log = 1; (1 << log) <= L[p]; log++);
  log--;
  rev(i, log, -1) {
    if(L[p] - (1 << i) >= L[q])
      p = P[p][i];        //ancestor at the same level
  }
  if(p == q)
    return p;
  rev(i, log, -1) 
    if(P[p][i] != -1 && P[p][i] != P[q][i])
      p = P[p][i], q = P[q][i];
  return T[p];
}
