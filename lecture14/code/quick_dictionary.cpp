#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

char const* input = R"(
This lecture and the next presents the STL (the containers and
algorithms part of the C++ standard library). It is an extensible
framework dealing with data in a C++ program. First, I present
the general ideal, then the fundamental concepts, and finally
examples of containers and algorithms. The key notions of sequence
and iterator used to tie containers (data) together with algorithms
(processing) are presented. Function objects are used to
parameterize algorithms with "policies".
)";

int main()
{
    std::istringstream str(input);

    // make input iterator for stream
    std::istream_iterator<std::string> ii(str);
    // input sentinel (defaults to EOF)
    std::istream_iterator<std::string> eos;

    // make output iterator for stream append "\n" each time
    std::ostream_iterator<std::string> oo(std::cout, "\n");

    // b is a vector initialized from input
    std::vector<std::string> b(ii, eos);

    // sort the buffer
    std::sort(b.begin(), b.end());

    // copy buffer to output, discard replicated values
    std::unique_copy(b.begin(), b.end(), oo);
}