#include "policies.h"

#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

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
