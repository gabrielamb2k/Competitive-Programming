int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int n,m; cin >> n >> m;
  vvi g(n,vi(m));
  for(int i=0;i<n;i++){
    string s; cin >> s;
    for(int j=0;j<m;j++){
        g[i][j]=(s[j]=='.');
    }
  }
 
  vvi h(n+1, vi(m+1));
  vvi v(n+1, vi(m+1));
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
        v[i][j]=v[i-1][j]+v[i][j-1]-v[i-1][j-1];
        if(i<n and g[i-1][j-1] and g[i][j-1]){
            v[i][j]++;
        }
        h[i][j]=h[i-1][j]+h[i][j-1]-h[i-1][j-1];
        if(j<m and g[i-1][j-1] and g[i-1][j]){
            h[i][j]++;
        }
    }
  }
 
  int q; cin >> q;
  while(q--){
    int r1,c1,r2,c2; cin >>r1 >>c1>>r2>>c2;
    int ans = h[r2][c2-1] - h[r1-1][c2-1] - h[r2][c1-1] + h[r1-1][c1-1];
    ans+= v[r2-1][c2] - v[r2-1][c1-1] - v[r1-1][c2] + v[r1-1][c1-1];
    cout<<ans<<endl;
  }
 
  return 0;
}
