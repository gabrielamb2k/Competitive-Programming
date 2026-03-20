#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n, l, timer;
    vector<int> tin, tout;
    vector<vector<int>> up;

    // Construtor: recebe o número de vértices, a raiz e a lista de adjacência
    LCA(int n, int root, const vector<vector<int>>& adj) {
        this->n = n;
        tin.resize(n);
        tout.resize(n);
        timer = 0;
        l = ceil(log2(n));
        if (l == 0) l = 1; // Previne erro se n = 1
        up.assign(n, vector<int>(l + 1));
        
        dfs(root, root, adj);
    }

    // Pré-processamento com DFS
    void dfs(int v, int p, const vector<vector<int>>& adj) {
        tin[v] = ++timer;
        up[v][0] = p; // O ancestral 2^0 de v é o próprio pai p
        
        // Preenche a tabela de saltos (Binary Lifting)
        for (int i = 1; i <= l; ++i) {
            up[v][i] = up[up[v][i-1]][i-1];
        }
        
        for (int u : adj[v]) {
            if (u != p) {
                dfs(u, v, adj);
            }
        }
        tout[v] = ++timer;
    }

    // Verifica se 'u' é ancestral de 'v' em O(1)
    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    // Retorna o Menor Ancestral Comum entre 'u' e 'v' em O(log N)
    int query(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        
        // Sobe com 'u' até o nó mais alto que NÃO seja ancestral de 'v'
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v)) {
                u = up[u][i];
            }
        }
        // O LCA será o pai direto desse nó
        return up[u][0];
    }
};

/* COMO USAR NA MAIN:
 * int n = 5; // Número de vértices (0-indexado)
 * vector<vector<int>> adj(n);
 * adj[0].push_back(1); adj[1].push_back(0); // Exemplo de aresta 0-1
 * adj[0].push_back(2); adj[2].push_back(0); // Exemplo de aresta 0-2
 * * LCA lca(n, 0, adj); // Instancia passando n, a raiz (0) e o grafo
 * int ans = lca.query(1, 2); // Retorna 0
 */
