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


int n, i, m, R[N], M[N];
II a[N];

struct node { 
	int count;
	node *left, *right;

	node(int count, node *left, node *right) : count(count), left(left), right(right) {}
	node *insert(int low, int high, int val);
};

node *null = new node (0, NULL, NULL);
node *root[N];

node* node::insert(int low, int high, int val) {
	if(low == high && low == val) {
		return new node(this->count+1, null, null);
	}
	else if( (low > val) || (high < val	)) {
		return this;
	}
	int mid = (low + high) >> 1;
	return new node(this->count + 1, (this->left)->insert(low, mid, val), (this->right)->insert(mid+1, high, val));
}

int query(node* a, node* b, int low, int high, int k) {
	if(low == high) { 
		return low;
	}
	int sum = (b->left)->count - (a->left)->count;
	int mid = (low + high ) >> 1;
	if(sum >= k) {
		return query(a->left, b->left, low, mid, k);
	}
	return query(a->right, b->right, mid+1, high, k-sum);
}

int main () { 

	cin >> n >> m;

	rep(i, 1, n+1) {
		cin >> a[i].F;
		a[i].S = i;
	}

	sort(a+1, a+1+n);

	rep(i, 1, n+1) {
		M[a[i].S] = i;
		R[i] = a[i].F;
	}

	null->left = null;
	null->right = null;
	root[0] = null;

	rep(i, 1, n+1) { 
	  root[i] = root[i-1]->insert(1, n, M[i]);
	}

	while(m--) { 
		int u, v, k;
		cin >> u >> v >> k;
		cout << R[query(root[u-1], root[v], 1, n, k)] << '\n';
	}
	return 0;
}	