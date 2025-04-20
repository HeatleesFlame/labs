int triangulate(double** A, int* L,  int m, int n){
    int r = 0;
    for(int i = 0; i < min(m, n); i++) {
        int v = i, u = i;
        for(int j = i; j < m; j++) {
            for(int k = i; k < n; k++) {
                if(fabs(A[j][k]) > fabs(A[v][u])) {
                    v = j;
                    u = k;
                }
            }
        }

        if(fabs(A[v][u]) < eps) {
            r = i;
            break;
        }

        if(v != i) {
            swap(A[i], A[v]);
        }

        if(u != i) {
            for(int k = 0; k < m; k++) {
                swap(A[k][i], A[k][u]);
            }
            swap(L[i], L[u]);
        }

        double div = A[i][i];
        for(int j = i; j <= n; j++) {
            A[i][j] /= div;
        }

        for(int k = 0; k < m; k++) {
            if(k != i) {
                double factor = A[k][i];
                for(int j = i; j <= n; j++) {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }
        r = i + 1;

    }
    return r;
}