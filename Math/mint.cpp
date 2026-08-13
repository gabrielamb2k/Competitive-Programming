struct mint {
  ll x;
  mint(ll x=0):x((x%MOD+MOD)%MOD){}
  mint& operator+=(const mint a) {if ((x += a.x) >= MOD) x -= MOD;return *this;}
  mint& operator-=(const mint a) {if ((x += MOD-a.x) >= MOD) x -= MOD;return *this;}
  mint& operator*=(const mint a) {(x *= a.x) %= MOD;return *this;}
  mint operator+(const mint a) const {mint res(*this);return res+=a;}
  mint operator-(const mint a) const {mint res(*this);return res-=a;}
  mint operator*(const mint a) const {mint res(*this);return res*=a;}
  mint pow(ll b) const {
    mint res(1), a(*this);
    while (b) {
      if (b & 1) res *= a;
      a *= a;
      b >>= 1;
    }
    return res;
  }
  // for prime MOD
  mint inv() const {return pow(MOD-2);}
  mint& operator/=(const mint a) {return (*this) *= a.inv();}
  mint operator/(const mint a) const {mint res(*this);return res/=a;}
};
ostream& operator<<(ostream& os, const mint& a) {os << a.x; return os;}

// ou
void add(int &a, int b) {
    a += b; 
    if (a >= mod) a -= MOD; 
    if (a < 0) a += MOD; 
} 
int get_sum(int a, int b) {
    add(a, b); 
    return a; 
} 

int get_mult(int a, int b) {
    return 1ll * a * b % MOD; 
} 

int get_inv(int n) {
    return n <= 1 ? n : (MOD - get_mult(MOD/n, get_inv(MOD%n)))%MOD; 
}

int div(int a, int b){
  return get_mult(a, get_inv(b));
}
