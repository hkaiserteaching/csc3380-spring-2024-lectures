// WRITE A FUNCTION vector<string> align_right(vector<string> const& v); THAT
// TREATS THE STRINGS STORED IN ITS ARGUMENT ‘V’ AS A ‘PICTURE’, I.E.
// EACH STRING FORMS A LINE (OR ROW) OF SOME PIECE OF ASCII ART. THE
// FUNCTION SHOULD RETURN THE RIGHT ALIGNED PICTURE.

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::vector<std::string> align_right(std::vector<std::string> const& v)
{
    std::vector<std::string> result;

    auto maxlen = std::accumulate(v.begin(), v.end(), 0,
        [](std::string::size_type sum, std::string const& curr) {
            return std::max(sum, curr.size());
        });

    for (auto const& s : v)
    {
        result.push_back(std::string(maxlen - s.size(), ' ') + s);
    }

    return result;
}

int main()
{
    std::vector<std::string> example = {"This", "is", "a", "small", "Picture"};

    for (auto const& s : align_right(example))
    {
        std::cout << s << "\n";
    }

    return 0;
}