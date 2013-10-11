#ifndef __POLICIES_H__
#define __POLICIES_H__

extern int FIFO(int, int, int, bool*, int*);
extern int LIFO(int, int, int, bool*, int*);
extern int LRU(int, int, int, bool*, int*);
extern int OPT(int, int, int, bool*, int*);

#endif // __POLICIES_H__
