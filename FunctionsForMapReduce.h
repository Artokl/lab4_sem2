#ifndef FUNCTIONSFORMAPREDUCE_H
#define FUNCTIONSFORMAPREDUCE_H

template <typename T>
T MapFunc(T i) {
    return i * 2;
}

bool WhereFunc(int i)
{
    if (i%2 == 0) return true;
    else return false;
}

template <typename T>
T ReduceFunc(T a, T b) {
    return a+b;
}
#endif //FUNCTIONSFORMAPREDUCE_H
