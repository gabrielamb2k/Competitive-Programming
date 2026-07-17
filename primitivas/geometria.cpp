typedef double ld;
const ld DINF = 1e18;
const ld pi = acos(-1.0);
const ld eps = 1e-9;

#define sq(x) ((x)*(x))

bool eq(ld a, ld b) {
	return abs(a - b) <= eps;
}

struct pt { // ponto
	ld x, y;
	pt(ld x_ = 0, ld y_ = 0) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (!eq(x, p.x)) return x < p.x;
		if (!eq(y, p.y)) return y < p.y;
		return 0;
	}
	bool operator == (const pt p) const {
		return eq(x, p.x) and eq(y, p.y);
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const ld c) const { return pt(x*c  , y*c  ); }
	pt operator / (const ld c) const { return pt(x/c  , y/c  ); }
	ld operator * (const pt p) const { return x*p.x + y*p.y; }
	ld operator ^ (const pt p) const { return x*p.y - y*p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};

// Distancia
ld dist(pt p, pt q){
  return hypot(p.y - q.y, p.x - q.x);
}

// Quadrado da distancia
ld dist2(pt p, pt q){
  return sq(p.x-q.x) + sq(p.y-q.y);
}

// Se p,q e r sao colineares
bool col(pt p, pt q, pt r){
  return eq(sarea(p,q,r),0);
}

// Produto vetorial
ld cross_product(pt p, pt q, pt r){
  return ((q-p) ^ (r-q));
}

// Area com sinal
ld sarea(pt p, pt q, pt r){
  return ((q-p)^(r-q))/2;
}

// Setindo anti-horario
bool ccw(pt p, pt q, pt r){
  return sarea(p,q,r) > eps;
}


// Para radial swep
bool half(pt p){
  if(p.y > 0) return 0;
  if(p.y == 0 and p.x > 0) return 0;
  return 1;
}

bool compare(pt p, pt q){
  if(half(p) != half(q)) return half(p) < half(p);
  return (p^q) > 0;
}

// Distancia de manhattan entre pontos em O(n)


// Convex hull
vector<pt> convex_hull(vector<pt> pts){
  sort(all(pts));
  // Verificar se todos pontos sao unicos: pts.erase(unique(all(pts)),pts.end());
  // Condicao se o vetor tiver apenas um ponto retornar ele mesmo if(pts.size() <= 1) return 1
  vector<pt> inf, sup;
  for(int i=0;i<(int)pts.size();i++){
    while(inf.size() > 1 and !ccw(inf.end()[-2], inf.end()[-1], pts[i]))
        inf.pop_back();
    inf.pb(pts[i]);
  }

  for(int i=pts.size()-1;i>=0;i--){
    while(sup.size() > 1 and !ccw(sup.end()[-2], sup.end()[-1], pts[i]))
        sup.pop_back();
    sup.pb(pts[i]);
  }
  inf.pop_back();
  sup.pop_back();
  for(auto p : sup) inf.pb(p);
  return inf;
}
