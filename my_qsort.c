// v is an array of elements to sort.
// size is the number of elements in array
// left and right is start and end of array
//(*comp)(void*, void*) is a pointer to a function
// which accepts two void* as its parameter
void _qsort(void* v, int size, int left, int right,
            int (*comp)(void*, void*))
{
    void *vt, *v3;
    int i, last, mid = (left + right) / 2;
    if (left >= right)
        return;

    // casting void* to char* so that operations
    // can be done.
    void* vl = (char*)(v + (left * size));
    void* vr = (char*)(v + (mid * size));
    swap(vl, vr, size);
    last = left;
    for (i = left + 1; i <= right; i++) {

        // vl and vt will have the starting address
        // of the elements which will be passed to
        // comp function.
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
    return strcmp(a1, a2);
}

int cmpstruct(const void* v1,const void* v2)
{
    fileinfo_t *a1 = (fileinfo_t*) v1;
    fileinfo_t *a2 = (fileinfo_t*) v2;
    return strcmp(a1->name, a2->name);
}

int cmpstruct_time(const void* v1,const void* v2)
{
    fileinfo_t *a1 = (fileinfo_t*) v1;
    fileinfo_t *a2 = (fileinfo_t*) v2;
    int d = (a1->time == a2->time);
    if(d == 0) return (a1->time<a2->time);
    else return strcmp(a1->name, a2->name);
}


/* you can also write compare function for floats,
    chars, double similarly as integer. */
// function for swap two elements
void swap(void* v1, void* v2, int size)
{
    // buffer is array of characters which will
    // store element byte by byte
    char buffer[size];

    // memcpy will copy the contents from starting
    // address of v1 to length of size in buffer
    // byte by byte.
    memcpy(buffer, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, buffer, size);
}




