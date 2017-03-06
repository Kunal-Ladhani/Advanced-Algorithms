/* Rishabh Arora
   IIIT-Hyderabad */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> II;
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


const int N = 1e5+10;
const int mod = 1e9+7;
const int LOGN = 20;

int n, m;
int R[N], M[N], depth[N], par[N], P[N][LOGN];
II a[N];
vector<VI> g;

struct node {
	int count;
	node *left, *right;
	node() {}
	node(int count, node * left, node * right) :
		count(count), left(left), right(right) {}
	node *insert(int l, int r, int w);
};  
		
node *root[N];
node *null = new node(0, NULL, NULL);

node* node::insert(int low, int high, int w) {
	if(low == high && low == w) {
		return new node(this->count+1, null, null);
	}
	else if( (high < w) || (low > w) ) {
		return this;
	}
	int mid  = (low + high) >> 1;
	return new node(this->count+1, this->left->insert(low, mid, w), this->right->insert(mid+1, high, w)); 
}

void dfs(int v, int p) {
	par[v] = p;
	depth[v] = (p == -1 ? 0 : depth[p] + 1);
	root[v] = (p == -1 ? null : root[p])->insert(1, n, M[v]);
	for(int i = 0; i <(int)g[v].size(); i++) {
		int u = g[v][i];
		if(u != p) {
			dfs(u, v);
		}   
	}
	return;    
}

int query(node *a, node *b, node *c, node *d, int low, int high, int K) {
	if(low == high) { 
		return low;
	}
	int sum = (a->left)->count + (b->left)->count - (c->left)->count - (d->left)->count;
	int mid = (low + high) >> 1;
	if(sum >= K) {
		return query(a->left, b->left, c->left, d->left, low, mid, K);
	}
	return query(a->right, b->right, c->right, d->right, mid + 1, high, K-sum);
}

void preprocess(int n) {
	int i, j;
	SET(P, -1);
	rep(i, 1, n+1) {
		P[i][0] = par[i];
	}
	for(j = 1; 1 << j < n; j++) {
		rep(i, 1, n+1) {
			if(P[i][j-1] != -1) {
				P[i][j] = P[P[i][j-1]][j-1];
			} 
		}
	}
}
int lca(int p, int q) { 
	int i;
	if(depth[p] < depth[q])
	swap(p, q);
	int log;
	for(log = 1; (1 << log) <= depth[p]; log++);
	log--;
	rev(i, log, -1) {
		if(depth[p] - (1 << i) >= depth[q])
		p = P[p][i];
	}
	if(p == q)
		return p;
	rev(i, log, -1) 
		if(P[p][i] != -1 && P[p][i] != P[q][i])
			p = P[p][i], q = P[q][i];
	return par[p];
}

int main() {

	ios::sync_with_stdio(false);	
	cin.tie(NULL);
	  
	  int i;
	  cin >> n >> m;
	  g.resize(n+1);
	  rep(i, 1, n+1) {
			cin >> a[i].F ;
			a[i].S = i;
	  }    

	  sort(a + 1,  a + n + 1);
	  
	  rep(i, 1, n+1) { 
	  	M[a[i].S] = i;
	  	R[i] = a[i].F;
	  }

	 int a, b;
	 rep(i, 1, n) {
			cin >> a >> b;
			g[a].PB(b);
			g[b].PB(a);
	  }
	  null->left=null->right=null;
	  dfs(1, -1);
	  preprocess(n);

	  root[0] = null;

	  while(m--) {
			int u, v, k;
			cin >> u >> v >> k;
			int l = lca(u, v);
			int p = par[l];
			if (p == -1) p = 0;
			cout << R[query(root[u], root[v], root[l], root[p], 1, n, k)] << '\n';
	  }
	  return 0;
	}
