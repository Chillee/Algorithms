map<int, int> comp, decomp;
int A[];
// insert everything into map;
for (int i=0; i<N; i++)
    comp[A[i]]=0;
int idx=0;
for (auto &i: comp) 
    i.second = i++, decomp[i.second] = i.first;
for (int i=0; i<N; i++)
    A[i] = comp[A[i]];