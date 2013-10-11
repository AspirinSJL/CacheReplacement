/*
 * NAME: Shen Juanli
 * NO: A0118400X
 */

#include <fstream>
#include <iostream>
#include <cstdio>
#include <iomanip> //
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <cstring> //
#include <cmath>
#include <limits>
#include <algorithm> //
#include <sstream>
#include <utility>
#include <cstdlib>

using namespace std;

typedef unsigned long long int ulli;

const int INF = ~0U >> 2;
const double eps = 1e-6; // END ///////////////////////////////

typedef int Entry;
typedef int* Row;
typedef int** Matrix;

int FIFO(int, int, int, bool*, int*);
int LIFO(int, int, int, bool*, int*);
int LRU(int, int, int, bool*, int*);
int OPT(int, int, int, bool*, int*);

int GenerateEntriesByPartition(int, int, int, int, int*);

Matrix NewMatrix(int, int);
void DeleteMatrix(int, int, Matrix);
void ReadMatrix(int, int, Matrix);
void WriteMatrix(int, int, Matrix);
void MatrixPartirionMultiply(int, int, int, int, Matrix, Matrix, Matrix);

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("LIFO.txt", "w", stdout);

    int tc;
    cin >> tc;

    while(tc--)
    {
//        cout << "tc = " << 10 - tc << endl;
        int s, p, x, q;
        cin >> s >> p >> x >> q;
//
//        Matrix A = NewMatrix(p, x);
//        Matrix B = NewMatrix(x, q);
//        Matrix C = NewMatrix(p, q);
//
//        ReadMatrix(p, x, A);
//        ReadMatrix(x, q, B);
//
//        MatrixPartirionMultiply(s, p, x, q, A, B, C);
//
//        WriteMatrix(p, q, C);
//
//        DeleteMatrix(p, x, A);
//        DeleteMatrix(x, q, B);
//        DeleteMatrix(p, q, C);

        /*******************************************/

        // num of entries
        int n = p * x + x * q + p * q;
        // num of access (a little more than needed)
        int m = (x * 3) * p * q;

        int* entries = new int[m];
        int cnt = GenerateEntriesByPartition(s, p, x, q, entries);

        bool* cached = new bool[n + 1];

//        cout << FIFO(s, n, cnt, cached, entries) << " ";
        cout << LIFO(s, n, cnt, cached, entries) << " ";
//        cout << LRU(s, n, cnt, cached, entries) << " ";
//        cout << OPT(s, n, cnt, cached, entries) << endl;

        delete[] entries;
        delete[] cached;
    }

    return 0;
}

int FIFO(int s, int n, int m, bool* cached, int* entries)
{
    // cold down the cache
    for(int i = 1; i < n + 1; ++i)
        cached[i] = false;

    queue<int> cache;
    int miss = 0;
    int entry;

    for(int i = 0; i < m; ++i)
    {
        entry = entries[i];

        if(cached[entry])
            continue;

        // fall down here if not hit before
        miss++;
        // cache it
        cache.push(entry);
        cached[entry] = true;

        // replacement
        if(cache.size() > s)
        {
            // front is the victim
            cached[cache.front()] = false;
            cache.pop();
        }
    }

    return miss;
}

int LIFO(int s, int n, int m, bool* cached, int* entries)
{
    // cold down the cache
    for(int i = 1; i < n + 1; ++i)
        cached[i] = false;

    stack<int> cache;
    int miss = 0;
    int entry;

    for(int i = 0; i < m; ++i)
    {
        entry = entries[i];

        if(cached[entry])
            continue;

        // fall down here if not hit before
        miss++;

        // replacement
        if(cache.size() == s)
        {
            // top is the victim
            cached[cache.top()] = false;
            cache.pop();
        }

        // cache it
        cache.push(entry);
        cached[entry] = true;
    }

    return miss;
}

int LRU(int s, int n, int m, bool* cached, int* entries)
{
    // cold down the cache
    for(int i = 1; i < n + 1; ++i)
        cached[i] = false;

    list<int> cache;
    int miss = 0;
    int entry;

    for(int i = 0; i < m; ++i)
    {
        entry = entries[i];

        if(cached[entry])
        {
            // the most recent used entry is changed to the end
            list<int>::iterator recent = find(cache.begin(), cache.end(), entry);
            cache.splice(cache.end(), cache, recent);

            continue;
        }

        // fall down here if not hit before
        miss++;

        // replacement
        if(cache.size() == s)
        {
            // begin is the victim
            cached[*cache.begin()] = false;
            cache.erase(cache.begin());
        }

        // cache it
        cache.insert(cache.end(), entry);
        cached[entry] = true;
    }

    return miss;
}

int OPT(int s, int n, int m, bool* cached, int* entries)
{
    // cold down the cache
    for(int i = 1; i < n + 1; ++i)
        cached[i] = false;

    set<int> cache;
    int miss = 0;
    int entry;

    for(int i = 0; i < m; ++i)
    {
        entry = entries[i];

        if(cached[entry])
            continue;

        // fall down here if not hit before
        miss++;
        // cache it
        cache.insert(entry);
        cached[entry] = true;

        // replacement
        if(cache.size() > s)
        {
            // farest one to used is the victim
            set<int> victim(cache);

            for(int k = i + 1; k < m; ++k)
            {
                // usage leads to pardon
                victim.erase(entries[k]);

                if(victim.size() == 1)
                    break;
            }

            // choose one as the final victim
            int _victim = *victim.begin();
            cache.erase(_victim);
            cached[_victim] = false;
        }
    }

    return miss;
}

Matrix NewMatrix(int a, int b)
{
    Matrix M = new Row[a];

    for (int i = 0; i < a; ++i)
    {
        M[i] = new Entry[b];
    }

    return M;
}

void DeleteMatrix(int a, int b, Matrix M)
{
    for(int i = 0; i < a; ++i)
    {
        delete[] M[i];
    }

    delete[] M;
}

void ReadMatrix(int a, int b, Matrix M)
{
    for(int i = 0; i < a; ++i)
        for(int j = 0; j < b; ++j)
    {
        cin >> M[i][j];
    }
}

void WriteMatrix(int a, int b, Matrix M)
{
    for(int i = 0; i < a; ++i)
    {
        for(int j = 0; j < b; ++j)
        {
            cout << M[i][j] << ' ';
        }
    }
    cout << endl;
}

void MatrixPartirionMultiply(int s, int p, int x, int q, Matrix A, Matrix B, Matrix C)
{
    // initialize C
    for(int i = 0; i < p; ++i)
        for(int j = 0; j < q; ++j)
        {
            C[i][j] = 0;
        }

    // partition size
    int pttSize = floor(sqrt(s) - 1.0);

//    // number of partitions along p
//    int numPttP = p / pttSize + 1;
//    // size of last partition along p
//    int lastPttP = p % pttSize;

    // number of partitions along x
    int numPttX = x / pttSize + 1;
    // size of last partition along x
    int lastPttX = x % pttSize;
    // number of partitions along q
    int numPttQ = q / pttSize + 1;
    // size of last partition along q
    int lastPttQ = q % pttSize;


//    for(int I = 0; I < numPttP; ++I)
//    {
//        // decide p of submatrix by its position
//        int pttP = (I == numPttP - 1 ? lastPttP : pttSize);

    // don't broke p
    int pttP = p;

    // outter loop is for blockwise and inner for submatrices
    for(int J = 0; J < numPttQ; ++J)
    {
        // decide q of submatrix by its position
        int pttQ = (J == numPttQ - 1 ? lastPttQ : pttSize);

        for(int K = 0; K < numPttX; ++K)
        {
            // decide x of submatrix by its position
            int pttX = (K == numPttX - 1 ? lastPttX : pttSize);

            for(int i = 0; i < pttP; ++i)
            {
                for(int j = 0; j < pttQ; ++j)
                {
                    int temp = 0;

                    for(int k = 0; k < pttX; ++k)
                    {
//                            temp += A[i + pttSize * I][k + pttSize * K] * B[k + pttSize * K][j + pttSize * J];
                        temp += A[i][k + pttSize * K] * B[k + pttSize * K][j + pttSize * J];
                    }
//                        C[i + pttSize * I][j + pttSize * J] += temp;
                    C[i][j + pttSize * J] += temp;
                }
            }
        }
    }
//    }
}

int GenerateEntriesByPartition(int s, int p, int x, int q, int* entries)
{
    int cnt = 0;

    // partition size
    int pttSize = floor(sqrt(s) - 1.0);

//    // number of partitions along p
//    int numPttP = p / pttSize + 1;
//    // size of last partition along p
//    int lastPttP = p % pttSize;

    // number of partitions along x
    int numPttX = x / pttSize + 1;
    // size of last partition along x
    int lastPttX = x % pttSize;
    // number of partitions along q
    int numPttQ = q / pttSize + 1;
    // size of last partition along q
    int lastPttQ = q % pttSize;


//    for(int I = 0; I < numPttP; ++I)
//    {
//        // decide p of submatrix by its position
//        int pttP = (I == numPttP - 1 ? lastPttP : pttSize);

    // don't broke p
    int pttP = p;

    // outter loop is for blockwise and inner for submatrices
    for(int J = 0; J < numPttQ; ++J)
    {
        // decide q of submatrix by its position
        int pttQ = (J == numPttQ - 1 ? lastPttQ : pttSize);

        for(int K = 0; K < numPttX; ++K)
        {
            // decide x of submatrix by its position
            int pttX = (K == numPttX - 1 ? lastPttX : pttSize);

            for(int i = 0; i < pttP; ++i)
            {
                for(int j = 0; j < pttQ; ++j)
                {
                    for(int k = 0; k < pttX; ++k)
                    {
//                            int idxA = x * (i + pttSize * I) + (k + pttSize * K) + 1;
                        int idxA = x * (i) + (k + pttSize * K) + 1;
                        int idxB = q * (k + pttSize * K) + (j + pttSize * J) + 1 + p * x;
                        entries[cnt++] = idxA;
                        entries[cnt++] = idxB;
                    }
//                        int idxC = q * (i + pttSize * I) + (j + pttSize * J) + 1 + p * x + x * q;
                    int idxC = q * (i) + (j + pttSize * J) + 1 + p * x + x * q;
                    entries[cnt++] = idxC;
                }
            }
        }
    }
//    }

    return cnt;
}
