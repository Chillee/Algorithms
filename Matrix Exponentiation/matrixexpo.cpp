  struct matrix {
    vector<vector<ll>> cells;

    matrix(vector<vector<ll>> input) : cells(input) {}
    matrix(ll n, ll m, ll val) {
        cells.resize(n);
        vector<ll> row(m);
        fill(row.begin(), row.end(), val);
        fill(cells.begin(), cells.end(), row);
    }
    matrix(ll n) : matrix(n, n, 0) {
        for (ll i = 0; i < n; i++) {
            cells[i][i] = 1;
        }
    }

    matrix operator*(matrix b) {
        assert(cells[0].size() == b.cells.size());
        ll n = cells.size(), m = b.cells[0].size();
        matrix result(n, m, 0);
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                for (ll k = 0; k < b.cells.size(); k++)
                    result.cells[i][j] += cells[i][k] * b.cells[k][j];
            }
        }
        return result;
    }
};

matrix matPow(matrix base, ll exp) {
    if (exp == 0)
        return matrix(base.cells.size());
    return matPow(base * base, exp / 2) * (exp % 2 == 1 ? base : matrix(base.cells.size()));
}