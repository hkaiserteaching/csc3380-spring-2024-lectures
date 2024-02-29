
#pragma once

#include <concepts>
#include <cstddef>
#include <vector>

template <std::semiregular T>
struct list_node
{
    T value;
    std::size_t prev = 0;
    std::size_t next = 0;
};

template <std::semiregular T>
class list_pool
{
    std::vector<list_node<T>> pool;
    std::size_t free_list = end();

    std::size_t new_node()
    {
        pool.push_back(list_node<T>());
        return pool.size();
    }

public:
    list_node<T>& node(std::size_t pos)
    {
        return pool[pos - 1];
    }
    list_node<T> const& node(std::size_t pos) const
    {
        return pool[pos - 1];
    }

    static std::size_t end()
    {
        return std::size_t(0);
    }

    static bool is_end(std::size_t x)
    {
        return x == end();
    }

    bool empty() const
    {
        return pool.size();
    }

    std::size_t size() const
    {
        return pool.size();
    }

public:
    list_pool() = default;

    T& value(std::size_t pos)
    {
        return node(pos).value;
    }

    T const& value(std::size_t pos) const
    {
        return node(pos).value;
    }

    std::size_t& next(std::size_t pos)
    {
        return node(pos).next;
    }
    std::size_t next(std::size_t pos) const
    {
        return node(pos).next;
    }

    std::size_t& prev(std::size_t pos)
    {
        return node(pos).prev;
    }
    std::size_t prev(std::size_t pos) const
    {
        return node(pos).prev;
    }

public:
    std::size_t allocate(T const& val)
    {
        std::size_t node = free_list;
        if (is_end(free_list))
        {
            node = new_node();
        }
        else
        {
            free_list = next(free_list);
        }

        value(node) = val;
        next(node) = end();
        prev(node) = end();

        return node;
    }

    std::size_t deallocate(std::size_t pos)
    {
        std::size_t nxt = next(pos);
        next(pos) = free_list;
        free_list = pos;
        return nxt;
    }

private:
    std::size_t link(std::size_t pos, std::size_t new_pos)
    {
        prev(new_pos) = pos;
        if (!is_end(pos))
        {
            next(new_pos) = next(pos);
            if (!is_end(next(pos)))
                prev(next(pos)) = new_pos;
            next(pos) = new_pos;
        }

        return new_pos;
    }

    std::size_t unlink(std::size_t pos)
    {
        if (!is_end(prev(pos)))
            next(prev(pos)) = next(pos);
        if (!is_end(next(pos)))
            prev(next(pos)) = prev(pos);

        return next(pos);
    }

public:
    std::size_t insert(T const& val, std::size_t pos)
    {
        return link(pos, allocate(val));
    }

    std::size_t erase(std::size_t pos)
    {
        std::size_t node = unlink(pos);
        deallocate(pos);
        return node;
    }
};

