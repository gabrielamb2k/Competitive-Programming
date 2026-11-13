const int MAXN = 2e5+5;
const int B = 450;
const int LG = 20;

vector<int> g[MAXN];
int par[MAXN][LG + 1], dep[MAXN], sz[MAXN], A[MAXN], IN[MAXN], OUT[MAXN], ID[MAXN];
int tem=0;

struct Query{
    int l,r,lca,id;
    bool operator<(const Query &q) const{
        int a = l/B, b = q.l/B;
        if(a!=b) return a < b;
        return (a&1) ? r > q.r : r < q.r;
    }
};

void dfs(int u, int p = 0) {
  par[u][0] = p;
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  IN[u]=++tem;
  ID[tem]=u;
  for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
  for (auto v: g[u]) if (v != p) {
    dfs(v, u);
    sz[u] += sz[v];
  }
  OUT[u]=++tem;
  ID[tem]=u;
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N,Q; cin >> N >> Q;
    vi vals;
    for(int i=1;i<=N;i++){
        cin >>A[i];
        vals.pb(A[i]);
    }

    sort(all(vals));
    vals.erase(unique(all(vals)),vals.end());
    for(auto &x : A){
        x = lower_bound(all(vals),x)-vals.begin();
    }

    for(int i=0;i<N-1;i++){
        int u,v; cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }
    dfs(1);

    vector<Query> q;
    for(int i=0;i<Q;i++){
        int l, r; cin >> l >> r;
        if(IN[l]>IN[r]) swap(l,r);
        int lc = lca(l,r);
        if(l==lc){
            q.pb({IN[l], IN[r], -1, i});
        }else{
            q.pb({OUT[l],IN[r],lc,i});
        }
    }

    int ans=0;
    vi cnt(len(vals)+1);
    vi vis(N+1);
    sort(all(q));
    auto toogle =[&](int id){
        if(!vis[id]){
            cnt[A[id]]++;
            if(cnt[A[id]]==1) ans++;
        }else{
            cnt[A[id]]--;
            if(cnt[A[id]]==0) ans--;
        }
        vis[id] ^=1;
    };

    int L=1,R=0;
    vi res(Q);
    for(auto [l,r,lc,id] : q){
        bug(l,r,lc,id);
        while(L>l) toogle(ID[--L]);
        while(R<r) toogle(ID[++R]);
        while(L<l) toogle(ID[L++]);
        while(R>r) toogle(ID[R--]);

        if(lc!=-1){
            toogle(lc);
        }
        res[id]=ans;
        if(lc!=-1){
            toogle(lc);
        }
    }

    for(auto x : res){
        cout<<x<<'\n';
    }

    return 0;
}

