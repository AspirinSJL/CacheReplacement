int GenerateEntries(int p, int x, int q, int* entries)
{
    // just modify the production algorithm
    int cnt = 0;
    for(int i = 0; i < p; ++i)
        for(int j = 0; j < q; ++j)
        {
            for(int k = 0; k < x; ++k)
            {
                int idxA = x * i + k + 1;
                int idxB = q * k + j + 1 + p * x;
                entries[cnt++] = idxA;
                entries[cnt++] = idxB;
            }
            int idxC = q * i + j + 1 + p * x + x * q;
            entries[cnt++] = idxC;
        }

    return cnt;
}