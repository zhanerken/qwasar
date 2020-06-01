#include "my_ls.h"

void _qsort(void* v, int size, int left, int right,
            int (*comp)(void*, void*))
{
    void *vt, *v3;
    int i, last, mid = (left + right) / 2;
    if (left >= right)
        return;

    void* vl = (char*)(v + (left * size));
    void* vr = (char*)(v + (mid * size));
    swap(vl, vr, size);
    last = left;
    for (i = left + 1; i <= right; i++) {
        vt = (char*)(v + (i * size));
        if ((*comp)(vl, vt) > 0) {
            ++last;
            v3 = (char*)(v + (last * size));
            swap(vt, v3, size);
        }
    }
    v3 = (char*)(v + (last * size));
    swap(vl, v3, size);
    _qsort(v, size, left, last - 1, comp);
    _qsort(v, size, last + 1, right, comp);
}

int cmpstr(const void* v1,const void* v2)
{
    char *a1 = (char*) v1;
    char *a2 = (char*) v2;
    return my_strcmp(a1, a2);
}

int cmpstruct(const void* v1,const void* v2)
{
    fileinfo_t *a1 = (fileinfo_t*) v1;
    fileinfo_t *a2 = (fileinfo_t*) v2;
    return my_strcmp(a1->name, a2->name);
}

int cmpstruct_time(const void* v1,const void* v2)
{
    fileinfo_t *a1 = (fileinfo_t*) v1;
    fileinfo_t *a2 = (fileinfo_t*) v2;
    int d = (a1->time == a2->time);
    if(d == 0) return (a1->time<a2->time);
    else return my_strcmp(a1->name, a2->name);
}

void swap(void* v1, void* v2, int size)
{
    char buffer[size];
    my_memcpy(buffer, v1, size);
    my_memcpy(v1, v2, size);
    my_memcpy(v2, buffer, size);
}




