#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2e5 + 10;

// ============================================================================
// 1. LAZY SEGMENT TREE (Configurada para SOMA)
// ============================================================================
struct LazySegTree {
    int tree[4 * N], lazy[4 * N];

    LazySegTree() {
        memset(tree, 0, sizeof(tree));
        memset(lazy, 0, sizeof(lazy));
    }

    void push(int node, int l, int r) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node] * (r - l + 1); // Aplica a soma no nó atual
            if (l != r) { // Se não for folha, passa a preguiça pros filhos
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int l, int r, int ql, int qr, int val) {
        push(node, l, r);
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            push(node, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        update(2 * node, l, mid, ql, qr, val);
        update(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (ql > r || qr < l) return 0; // Neutro da soma
        if (ql <= l && r <= qr) return tree[node];
        
        int mid = l + (r - l) / 2;
        return query(2 * node, l, mid, ql, qr) + 
               query(2 * node + 1, mid + 1, r, ql, qr);
    }
} seg;

// ============================================================================
// 2. HEAVY-LIGHT DECOMPOSITION (HLD)
// ============================================================================
vector<int> adj[N];
int sz[N], par[N], depth[N];
int head[N], in[N], out[N]; // out[] é a novidade para Subtrees!
int timer_hld = 0;
int n_nodes; // Guarda o tamanho da árvore globalmente para a SegTree

// Prepara os tamanhos, pais, profundidades e o Filho Pesado
void dfs_sz(int u, int p = 0) {
    sz[u] = 1;
    par[u] = p;
    depth[u] = depth[p] + 1;
    
    for (int &v : adj[u]) {
        if (v == p) continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
        
        // Coloca o filho mais pesado sempre na posição 0
        if (adj[u][0] == p || sz[v] > sz[adj[u][0]]) {
            swap(v, adj[u][0]);
        }
    }
}

// Monta as cadeias (chains) e define in/out
void dfs_hld(int u, int p = 0, int h = 1) {
    head[u] = h;
    in[u] = ++timer_hld;
    
    for (int v : adj[u]) {
        if (v == p) continue;
        // Se for o 1º filho (pesado), continua a chain (h). Senão, vira uma nova chain (v)
        dfs_hld(v, u, (v == adj[u][0] ? h : v)); 
    }
    
    out[u] = timer_hld; // Tempo exato em que terminamos de visitar a subárvore
}

// ============================================================================
// 3. FUNÇÕES DE INTERFACE (As ferramentas que você chama na main)
// ============================================================================

// A) Alterar/Adicionar valor em um ÚNICO nó
void modify_node(int u, int val) {
    seg.update(1, 1, n_nodes, in[u], in[u], val);
}

// B) Alterar/Adicionar valor em uma SUBÁRVORE inteira
void modify_subtree(int u, int val) {
    // A subárvore é perfeitamente o intervalo do tempo de entrada ao de saída!
    seg.update(1, 1, n_nodes, in[u], out[u], val);
}

// C) Consultar a soma de um CAMINHO entre dois nós (u até v)
int query_path(int u, int v) {
    int ans = 0;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        
        ans += seg.query(1, 1, n_nodes, in[head[u]], in[u]);
        u = par[head[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    ans += seg.query(1, 1, n_nodes, in[u], in[v]);
    
    return ans;
}

// D) Consultar a soma de uma SUBÁRVORE inteira (Bônus!)
int query_subtree(int u) {
    return seg.query(1, 1, n_nodes, in[u], out[u]);
}

// ============================================================================
// MAIN (Como inicializar)
// ============================================================================
signed main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    
    int q;
    cin >> n_nodes >> q;
    
    // 1. Ler os valores iniciais, se houver (opcional)
    vector<int> val(n_nodes + 1);
    for (int i = 1; i <= n_nodes; i++) cin >> val[i];
    
    // 2. Ler as arestas
    for (int i = 0; i < n_nodes - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // 3. Inicializar HLD
    dfs_sz(1);
    dfs_hld(1);
    
    // 4. Preencher a SegTree usando o in-time
    for (int i = 1; i <= n_nodes; i++) {
        modify_node(i, val[i]); // Jeito preguiçoso e seguro de dar o build inicial
    }
    
    // 5. Tratar as queries aqui...
    
    return 0;
}
