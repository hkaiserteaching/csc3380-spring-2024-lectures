#pragma once

#include <iostream>
#include <string>
#include <vector>

struct image
{
    std::vector<std::string> data;

    // make image regular
    image() = default;
    ~image() = default;

    image(image const&) = default;
    image& operator=(image const&) = default;

    friend bool operator==(image const& lhs, image const& rhs)
    {
        return lhs.data == rhs.data;
    }
    friend bool operator!=(image const& lhs, image const& rhs)
    {
        return !(lhs == rhs);
    }

    // construct an 'image' from a single line
    explicit image(std::string const& line)
      : data(1, line)
    {
    }

    // construct an 'image' from multiple lines
    explicit image(std::vector<std::string> const& lines)
      : data(lines)
    {
    }

    // construct an optionally 'space-filled' image of the given size
    image(int width, int height, char fill = ' ')
      : data(height, std::string(width, fill))
    {
    }

    // image properties
    std::string::size_type width() const
    {
        std::string::size_type maxlen = 0;
        for (auto const& s : data)
            maxlen = std::max(maxlen, s.size());
        return maxlen;
    }

    std::string::size_type height() const
    {
        return data.size();
    }

    // expose underlying iterators
    auto begin()
    {
        return data.begin();
    }
    auto begin() const
    {
        return data.begin();
    }
    auto end()
    {
        return data.end();
    }
    auto end() const
    {
        return data.end();
    }

    auto rbegin()
    {
        return data.rbegin();
    }
    auto rbegin() const
    {
        return data.rbegin();
    }
    auto rend()
    {
        return data.rend();
    }
    auto rend() const
    {
        return data.rend();
    }

    std::string const& operator[](std::size_t idx) const
    {
        return data[idx];
    }

    // append a single line to the bottom of the image
    void append(std::string const& line)
    {
        data.push_back(line);
    }

    // append (vertically concatenate) another image
    void append(image const& img)
    {
        for (auto const& s : img)
            data.push_back(s);
    }

    // print the 'image'
    friend std::ostream& operator<<(std::ostream& os, image const& img)
    {
        for (auto const& line : img)
            os << line << '\n';
        return os;
    }
};

// algorithms

// frame an image
inline image frame(image const& img, int gap = 1)
{
    image ret;
    auto maxlen = img.width();    // find longest string

    // create top line and append to result
    std::string border(maxlen + 2 + 2 * gap, '*');
    ret.append(border);

    // append each line from v to result after adding '*'
    std::string spaces(gap, ' ');
    for (auto const& s : img)
    {
        ret.append("*" + spaces + s + std::string(maxlen - s.size(), ' ') +
            spaces + "*");
    }

    ret.append(border);    // 'write' the bottom border
    return ret;
}

// vertical concatenation
inline image vcat(image const& top, image const& bottom, int gap = 0)
{
    // copy the top picture
    image ret = top;

    for (int i = 0; i < gap; ++i)
        ret.append(std::string());      // add empty line

    // copy entire bottom picture
    for (auto const& s : bottom)
        ret.append(s);

    return ret;
}

// horizontal concatenation
inline image hcat(image const& left, image const& right, int gap = 1)
{
    image ret;

    // add 1 to leave a space between pictures
    auto width1 = left.width() + gap;
    auto i = 0, j = 0;

    // continue until we've seen all rows from both pictures
    while (i != left.height() || j != right.height())
    {
        // construct new string to hold characters from both pictures
        std::string s;

        // copy a row from the left-hand side, if there is one
        if (i != left.height())
            s = left[i++];

        s += std::string(width1 - s.size(), ' ');    // pad to full width

        // copy a row from the right-hand side, if there is one
        if (j != right.height())
            s += right[j++];

        ret.append(s);    // add s to the picture
    }

    return ret;
}

// flip 'image' vertically
inline image vflip(image const& v)
{
    image ret;
    for (auto it = v.rbegin(); it != v.rend(); ++it)
        ret.append(*it);
    return ret;
}

// left-rotate an image
inline image rotate_left(image const& img)
{
    image ret;

    // take a letter from each string, starting at the end
    auto maxlen = img.width();
    for (auto i = maxlen; i != 0; --i)
    {
        std::string line;    // new line

        // for all lines in the input image
        for (auto const& current : img)
        {
            if (current.size() < i)
                line += ' ';
            else
                line += current[i - 1];
        }

        // store the new line in the result picture
        ret.append(line);
    }
    return ret;
}
