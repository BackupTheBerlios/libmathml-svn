#ifndef STYLECHANGES
#define STYLECHANGES

#include <stack>
using std::stack;

class PrivMMLPainter;

class FuncCall {
public:
    FuncCall() {};
    FuncCall(void (PrivMMLPainter::*)()) {};
    virtual ~FuncCall() {};
    virtual void call(PrivMMLPainter *) const;
private:
    void (PrivMMLPainter::* const function)();
};
template <class T>
class FuncCall1 : public FuncCall {
public:
    FuncCall1(void (PrivMMLPainter::*)(T), const T &);
    void call(PrivMMLPainter *) const;
private:
    void (PrivMMLPainter::* const function)(T);
    const T arg;
};
template<class T>
FuncCall1<T>::FuncCall1(void (PrivMMLPainter::*f)(T), const T &a)
    : function(f), arg(a) {
}
template<class T>
void
FuncCall1<T>::call(PrivMMLPainter *r) const {
    (r->*function)(arg);
}

template <class T, class U>
class FuncCall2 : public FuncCall {
public:
    FuncCall2(void (PrivMMLPainter::*)(T, U), const T &, const U &);
    void call(PrivMMLPainter *) const;
private:
    void (PrivMMLPainter::* const function)(T, U);
    const T arg1;
    const U arg2;
};
template<class T, class U>
FuncCall2<T,U>::FuncCall2(void (PrivMMLPainter::*f)(T,U), const T &a, const U &b)
    : function(f), arg1(a), arg2(b) {
}
template<class T, class U>
void
FuncCall2<T,U>::call(PrivMMLPainter *r) const {
    (r->*function)(arg1, arg2);
}

class StyleChanges {
public:
    StyleChanges(PrivMMLPainter *);
    ~StyleChanges();
    void add(const FuncCall *);
private:
    stack<const FuncCall *> calls;
    PrivMMLPainter * const r;
};

#endif
