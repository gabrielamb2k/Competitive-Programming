template<typename T>
struct SegTree {
    int n;
    vector<T> tree;
    T neutro = 0; // Elemento neutro (0 para soma, INF para mínimo, etc.)

    // Construtor
    SegTree(int n) : n(n) {
        tree.assign(4 * n, neutro);
    }

    T combina(T a, T b) {
        return a + b;
    }

    // Update interno (Recursivo)
    void update(int node, int l, int r, int pos, T val) {
        if (l == r) {
            tree[node] += val; // Altere para '=' se for substituição em vez de soma
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update(2 * node, l, mid, pos, val);
        else update(2 * node + 1, mid + 1, r, pos, val);
        
        tree[node] = combina(tree[2 * node], tree[2 * node + 1]);
    }

    // Query interna (Recursiva)
    T query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return neutro;
        if (ql <= l && r <= qr) return tree[node];
        
        int mid = (l + r) / 2;
        return combina(query(2 * node, l, mid, ql, qr),
                       query(2 * node + 1, mid + 1, r, ql, qr));
    }

    // --- FUNÇÕES PARA USAR NA MAIN ---
    void update(int pos, T val) { 
        update(1, 0, n - 1, pos, val); 
    }
    
    T query(int l, int r) { 
        return query(1, 0, n - 1, l, r); 
    }
};

/* COMO USAR NA MAIN:
 * SegTree<int> st(10);
 * st.update(3, 5);      // Adiciona 5 na posição 3
 * int ans = st.query(1, 5); // Soma do intervalo [1, 5]
 */
