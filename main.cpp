#include "policies.h"

#include <iostream>
#include <fstream>
#include <cstdlib>


extern int GenerateEntries(int, int, int, int*);

using namespace std;

int test1()
{
    cout << "test1" << endl;

    int tc;
    cin >> tc;

    while(tc--)
    {
        int s, n, m;
        cin >> s >> n >> m;

        int entries[m];
        for(int i = 0; i < m; ++i)
            cin >> entries[i];

        bool cached[n + 1];

        cout << FIFO(s, n, m, cached, entries) << " ";
        cout << LIFO(s, n, m, cached, entries) << " ";
        cout << LRU(s, n, m, cached, entries) << " ";
        cout << OPT(s, n, m, cached, entries) << endl;
    }

    return 0;
}

int test2()
{
    cout << "test2" << endl;

    int tc;
    cin >> tc;

    while(tc--)
    {
        int s, p, x, q;
        cin >> s >> p >> x >> q;

        // num of entries
        int n = p * x + x * q + p * q;
        // num of access
        int m = (x * 2 + 1) * p * q;

        int entries[m];
        GenerateEntries(p, x, q, entries);

        bool cached[n + 1];

 //       cout << FIFO(s, n, m, cached, entries) << " ";
        cout << LIFO(s, n, m, cached, entries) << " ";
 //       cout << LRU(s, n, m, cached, entries) << " ";
 //       cout << OPT(s, n, m, cached, entries) << endl;
    }

    return 0;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    test1();
    test2();

    system("PAUSE");
    return 0;
}
