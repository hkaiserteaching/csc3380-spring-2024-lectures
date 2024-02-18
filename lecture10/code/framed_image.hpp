
#include <iostream>

#include "ascii_image.hpp"

class framed_image
{
private:
    image const& base;
    int space_gap;

public:
    framed_image(image const& img, int gap = 1)
      : base(img)
      , space_gap(gap)
    {
    }

    int width() const
    {
        return base.width();
    }
    int gap() const
    {
        return space_gap;
    }

    // expose underlying iterators
    auto begin()
    {
        return base.begin();
    }
    auto begin() const
    {
        return base.begin();
    }
    auto end()
    {
        return base.end();
    }
    auto end() const
    {
        return base.end();
    }

    auto rbegin()
    {
        return base.rbegin();
    }
    auto rbegin() const
    {
        return base.rbegin();
    }
    auto rend()
    {
        return base.rend();
    }
    auto rend() const
    {
        return base.rend();
    }
};

std::ostream& operator<<(std::ostream& os, framed_image const& img)
{
    auto maxlen = img.width();    // find longest string

    // create top line and append to result
    std::string border(maxlen + 2 + 2 * img.gap(), '*');
    os << border << '\n';

    // append each line from v to result after adding '*'
    std::string spaces(img.gap(), ' ');
    for (auto const& s : img)
    {
        os << "*" + spaces + s + std::string(maxlen - s.size(), ' ') + spaces +
                "*\n";
    }

    os << border << '\n';    // 'write' the bottom border

    return os;
}
