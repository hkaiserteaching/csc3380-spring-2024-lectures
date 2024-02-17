#include <algorithm>

#include "instrumented.hpp"

double instrumented_base::counts[] = {0.0};
const char* instrumented_base::counter_names[number_ops] = {"n", "copy", "assign", "destruct", "default", "equal", "less", "construct"};

void instrumented_base::initialize(std::size_t m)
{
    std::fill(counts, counts + number_ops, 0.0);
    counts[n] = double(m);
}
