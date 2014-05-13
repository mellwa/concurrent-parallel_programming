#ifndef __Q3QUICKSORT_H__
#define __Q3QUICKSORT_H__

template<typename T> _Task Quicksort {
private:
    T *values;// list of values
    int low, high, depth;
    int partition(int lo, int hi);//method for finding partition
    void Start(int lo, int hi);
    void main();
public:
    Quicksort( T values[], int low, int high, int depth );
    ~Quicksort();
};


#endif