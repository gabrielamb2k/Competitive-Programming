const int N = 2e5+5;
vi adj[N];
int F[N], H[N];
int ans[N];
 
void dfs1(int u, int p){
    for(auto v : adj[u]) if(v!=p){
        dfs1(v,u);
        if(F[v]+1 > F[u]){
            H[u] = F[u];
            F[u] = F[v]+1;
        }else if(F[v]+1 > H[u]) H[u] = F[v]+1;
    }
}
 
void dfs2(int u, int p, int to_p){
    ans[u] = max(F[u], to_p);
    for(auto v : adj[u]) if(v!=p){
        if(F[u]==F[v]+1) {
            dfs2(v, u , max(H[u],to_p)+1);
        }
        else dfs2(v,u,max(to_p,F[u])+1);
    }
}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int n; cin >> n;
  for(int i=0;i<n-1;i++){
      int u,v; cin >> u >> v;
      adj[u].pb(v);
      adj[v].pb(u);
  }
  dfs1(1,0);
  dfs2(1,0,0);
 
  for(int i=1;i<=n;i++) cout << ans[i] << " ";
  cout << endl;
 
  return 0;
}
