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
    // Bag(const Bag &o_bag);

    void add(T item)
    {
        Node<T> *oldFirst = first;
        first = new Node<T>();
        first->item = item;
        first->next = oldFirst;
    }
    ~Bag() { delete first; }
    Bag &operator=(const Bag &o_bag);

    friend std::ostream &operator<<(std::ostream &os, const Bag<T> &bag);

private:
    Node<T> *first = nullptr;

public:
    class BagIterator
    {
        friend class Bag; //声明为友元
    public:
        BagIterator() {}

        //重载相关的运算符
        bool operator==(const BagIterator &iter) const
        {
            return current == iter.current;
        }

        bool operator!=(const BagIterator &iter) const
        {
            return current != iter.current;
        }

        T &operator*() const
        {
            return current->item;
        }

        BagIterator operator++(int) const
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
        Node<T> *current = nullptr;
    };
    BagIterator begin()
    {
        return BagIterator(first);
    }
    BagIterator end()
    {
        return BagIterator(nullptr);
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Bag<T> &bag)
{
    os << "Bag<" << typeid(T).name() << "> [";
    for(auto item: bag){
        os << item << ",";
    }
    os << ']';
    return os;
}

// template <typename T>
// Bag<T>::Bag(const Bag<T> &o_bag)
// {
//     for (auto item : o_bag)
//     {
//         add(item);
//     }
// }
#endif