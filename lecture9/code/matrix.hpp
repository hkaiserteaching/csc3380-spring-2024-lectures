#pragma once

template <typename T>
struct matrix
{
    T x11, x12;
    T x21, x22;

    T determinant() const
    {
        return x11 * x22 - x12 * x21;
    }

    friend bool operator==(matrix const& lhs, matrix const& rhs)
    {
        return lhs.x11 == rhs.x11 && lhs.x12 == rhs.x12 && lhs.x21 == rhs.x21 &&
            lhs.x22 == rhs.x22;
    }

    friend bool operator!=(matrix const& lhs, matrix const& rhs)
    {
        return !(lhs == rhs);
    }

    friend bool operator<(matrix const& lhs, matrix const& rhs)
    {
        return lhs.determinant() < rhs.determinant();
    }
    friend bool operator>(matrix const& x, matrix const& y)
    {
        return y < x;
    }
    friend bool operator<=(matrix const& x, matrix const& y)
    {
        return !(y < x);
    }
    friend bool operator>=(matrix const& x, matrix const& y)
    {
        return !(x < y);
    }

    friend matrix operator*(matrix const& lhs, matrix const& rhs)
    {
        return matrix{lhs.x11 * rhs.x11 + lhs.x12 * rhs.x21,
            lhs.x11 * rhs.x12 + lhs.x12 * rhs.x22,
            lhs.x21 * rhs.x11 + lhs.x22 * rhs.x21,
            lhs.x21 * rhs.x12 + lhs.x22 * rhs.x22};
    }
};

