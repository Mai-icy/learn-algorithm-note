#ifndef BAG_HPP
#define BAG_HPP

template <class T>
struct Node
{
    T item;
    Node *next = nullptr;
    ~Node() { delete next; };
};

template <class T>
class Bag
{
public:
    Bag() {}
    Bag(const Bag &o_bag);
    
    void add(T item)
    {
        Node<T> *oldFirst = first;
        first = new Node<T>();
        first->item = item;
        first->next = oldFirst;
    }
    ~Bag() { delete first; }
    Bag &operator=(const Bag &o_bag);

private:
    Node<T> *first = nullptr;

public:
    //定义迭代器
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

    //定义相关的迭代器用法
    BagIterator begin()
    {
        return BagIterator(first);
    }

    BagIterator end()
    {
        return BagIterator(nullptr);
    }
};

#endif