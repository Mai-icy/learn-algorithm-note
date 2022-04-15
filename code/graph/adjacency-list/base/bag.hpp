#ifndef BAG_HPP
#define BAG_HPP
#include <iostream>
#include <typeinfo>

template <typename T>
struct Node
{
    T item;
    Node *next = nullptr;
    ~Node() { delete next; };
};

template <typename T>
class Bag
{
public:
    Bag() {}
    Bag(const Bag &o_bag);

    bool isEmpty() const { return !(first); }
    void add(T item)
    {
        Node<T> *oldFirst = first;
        first = new Node<T>();
        first->item = item;
        first->next = oldFirst;
    }
    ~Bag() { delete first; }
    Bag &operator=(const Bag &o_bag);

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &os, const Bag<T1> &bag);

private:
    Node<T> *first = nullptr;

public:
    class BagIterator
    {
        friend class Bag; //声明为友元
    public:
        BagIterator() {}

        //重载相关的运算符
        bool operator==(const BagIterator &iter) const { return current == iter.current; }
        bool operator!=(const BagIterator &iter) const { return current != iter.current; }
        const T &operator*() const { return current->item; }
        BagIterator operator++(int)
        {
            BagIterator temp = *this;
            current = current->next;
            return temp;
        }

        BagIterator &operator++()
        {
            current = current->next;
            return *this;
        }

        bool atEnd() const
        {
            return current == nullptr;
        }

    protected:
        BagIterator(Node<T> *p) : current(p) {} //上面声明了友元，所以才能调用这个构造函数
        const Node<T> *current = nullptr;
    };

    BagIterator begin() const { return BagIterator(first); }
    BagIterator end() const { return BagIterator(nullptr); }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Bag<T> &bag)
{
    os << "Bag<" << typeid(T).name() << "> [";
    if (bag.isEmpty())
    {
        os << ']';
        return os;
    }
    for (auto it : bag)
    {
        os << it << ",";
    }
    os.put('\b');
    os << ']';
    return os;
}

template <typename T>
Bag<T> &Bag<T>::operator=(const Bag<T> &o_bag)
{
    if (this == &o_bag)
    {
        return *this;
    }
    delete first;
    first = nullptr;

    for (auto it : o_bag)
    {
        add(it);
    }
    return *this;
}

template <typename T>
Bag<T>::Bag(const Bag<T> &o_bag)
{
    for (auto it : o_bag)
    {
        add(it);
    }
}

#endif