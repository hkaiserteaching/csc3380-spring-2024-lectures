#pragma once

#include <concepts>
#include <cstddef>

#include "list_pool.hpp"

template <std::semiregular T>
class list_iterator;

template <std::semiregular T>
class const_list_iterator;

template <std::semiregular T>
class list
{
    list_pool<T> pool;
    std::size_t front = pool.end();
    std::size_t back = pool.end();

public:
    using iterator_type = list_iterator<T>;
    using const_iterator_type = const_list_iterator<T>;

    list() = default;

    void push_front(T const& val)
    {
        front = pool.insert(val, front);
        if (pool.is_end(back))
        {
            back = front;
        }
    }

    void push_back(T const& val)
    {
        back = pool.insert(val, back);
        if (pool.is_end(front))
        {
            front = back;
        }
    }

    list_iterator<T> erase(list_iterator<T> it);

    list_iterator<T> begin();
    list_iterator<T> end();

    const_list_iterator<T> begin() const;
    const_list_iterator<T> end() const;
};

template <std::semiregular T>
class list_iterator
{
    list_pool<T>& pool;
    std::size_t pos;

    friend class list<T>;
    friend class const_list_iterator<T>;

public:
    list_iterator(list_pool<T>& pool, std::size_t pos)
      : pool(pool)
      , pos(pos)
    {
    }

    T& operator*()
    {
        return pool.value(pos);
    }

    list_iterator& operator++()    // prefix++
    {
        pos = pool.next(pos);
        return *this;
    }
    list_iterator operator++(int)    // postfix++
    {
        auto prev_pos = pos;
        pos = pool.next(pos);
        return list_iterator(pool, prev_pos);
    }

    list_iterator& operator--()    // prefix--
    {
        pos = pool.prev(pos);
        return *this;
    }
    list_iterator operator--(int)    // postfix--
    {
        auto prev_pos = pos;
        pos = pool.prev(pos);
        return list_iterator(pool, prev_pos);
    }

    friend bool operator==(list_iterator const& lhs, list_iterator const& rhs)
    {
        return lhs.pos == rhs.pos;
    }
    friend bool operator!=(list_iterator const& lhs, list_iterator const& rhs)
    {
        return !(lhs == rhs);
    }
};

template <std::semiregular T>
class const_list_iterator
{
    list_pool<T> const& pool;
    std::size_t pos;

    friend class list<T>;

public:
    const_list_iterator(list_pool<T> const& pool, std::size_t pos)
      : pool(pool)
      , pos(pos)
    {
    }

    // allow constructing a const iterator from a non-const iterator
    const_list_iterator(list_iterator<T> const& it)
      : pool(it.pool)
      , pos(it.pos)
    {
    }

    T const& operator*() const
    {
        return pool.value(pos);
    }

    const_list_iterator& operator++()    // prefix++
    {
        pos = pool.next(pos);
        return *this;
    }
    const_list_iterator operator++(int)    // postfix++
    {
        auto prev_pos = pos;
        pos = pool.next(pos);
        return const_list_iterator(pool, prev_pos);
    }

    const_list_iterator& operator--()    // prefix--
    {
        pos = pool.prev(pos);
        return *this;
    }
    const_list_iterator operator--(int)    // postfix--
    {
        auto prev_pos = pos;
        pos = pool.prev(pos);
        return const_list_iterator(pool, prev_pos);
    }

    friend bool operator==(
        const_list_iterator const& lhs, const_list_iterator const& rhs)
    {
        return lhs.pos == rhs.pos;
    }
    friend bool operator!=(
        const_list_iterator const& lhs, const_list_iterator const& rhs)
    {
        return !(lhs == rhs);
    }
};

template <std::semiregular T>
list_iterator<T> list<T>::erase(list_iterator<T> it)
{
    std::size_t node = pool.erase(it.pos);
    if (it.pos == front)
    {
        front = node;
    }
    if (it.pos == back)
    {
        back = node;
    }
    return list_iterator<T>(pool, node);
}

template <std::semiregular T>
list_iterator<T> list<T>::begin()
{
    return list_iterator<T>(pool, front);
}

template <std::semiregular T>
list_iterator<T> list<T>::end()
{
    return list_iterator<T>(pool, 0);
}

template <std::semiregular T>
const_list_iterator<T> list<T>::begin() const
{
    return const_list_iterator<T>(pool, front);
}

template <std::semiregular T>
const_list_iterator<T> list<T>::end() const
{
    return const_list_iterator<T>(pool, 0);
}
