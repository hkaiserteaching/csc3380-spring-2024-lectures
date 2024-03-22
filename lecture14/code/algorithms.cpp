template <typename In, typename T>
T accumulate(In first, In last, T init)
{
    while (first != last)
    {
        init = init + *first;
        ++first;
    }
    return init;
}

int sum = accumulate(v.begin(), v.end(), 0);    // sum becomes 10

void f(std::vector<double>& vd, int* p, int n)
{
    double sum = accumulate(vd.begin(), vd.end(), 0.0);    // add the elements
                                                           // of vd
    // note: the type of the 3rd argument, the initializer, determines
    // the precision used

    int si = accumulate(p, p + n, 0);    // sum the ints in an int (danger of
                                         // overflow)  p+n means (roughly) &p[n]

    long sl = accumulate(p, p + n, long(0));    // sum the ints in a long
    double s2 = accumulate(p, p + n, 0.0);      // sum the ints in a double

    // popular idiom, use the variable you want the result in as the initializer:
    double ss = 0;
    ss = accumulate(vd.begin(), vd.end(), ss);    // do remember the assignment
}

// we don’t need to use only +, we can use any binary operation (e.g., *)
// any function that “updates the init value” can be used:

template <typename In, typename T, typename BinOp>
    requires(std::input_iterator<In>)
T accumulate(In first, In last, T init, BinOp op)
{
    while (first != last)
    {
        init = op(init, *first);    // means “init op *first”
        ++first;
    }
    return init;
}

// often, we need multiplication rather than addition:

#include <numeric>

void f(std::list<double> const& ld)
{
    double product =
        accumulate(ld.begin(), ld.end(), 1.0, std::multiplies<double>());
    // ...
}

// multiplies is a standard library function object for multiplying

struct produce
{
    int units;    // number of units sold
    double unit_price;
    // ...
};

// let the “update the init value” function extract data from a Record
// element:
double price(double v, produce const& r)
{
    return v + r.unit_price * r.units;
}

void f(std::vector<produce> const& vr)
{
    double total = accumulate(vr.begin(), vr.end(), 0.0, price);
    // ...
}

template <typename In, typename Out>
Out copy(In first, In last, Out res)
{
    while (first != last)
        *res++ = *first++;
    // conventional shorthand  for:
    //  *res = *first; ++res; ++first
    return res;
}

void f(vector<double>& vd, list<int>& li)
{
    if (vd.size() < li.size())
        error("target container too small");
    copy(
        li.begin(), li.end(), vd.begin());    // note: different container types
                                              // and different element types
                                              // (vd better have enough
    // elements to hold copies of li’s
    // elements)
    sort(vd.begin(), vd.end());
    // …
}

// we can provide iterators for output streams
void f{}
{
    std::ostream_iterator<std::string> oo(cout);    // assigning to *oo is to
                                                    // write to cout

    *oo = "Hello, ";     // meaning cout << "Hello, "
    ++oo;                // “get ready for next output operation”
    *oo = "world!\n";    // meaning cout << "world!\n"

    // we can provide iterators for input streams:

    std::istream_iterator<std::string> ii(cin);    // reading *ii is to read a
                                                   // string from cin

    std::string s1 = *ii;    // meaning cin >> s1
    ++ii;                    // “get ready for the next input operation”
    std::string s2 = *ii;    // meaning cin >> s2
}

int main()
{
    std::string from, to;
    std::cin >> from >> to;    // get source and target file names

    std::ifstream is(from);    // open input stream
    std::ofstream os(to);      // open output stream

    std::istream_iterator<std::string> ii(
        is);                                   // make input iterator for stream
    std::istream_iterator<std::string> eos;    // input sentinel (defaults to
                                               // EOF)
    std::ostream_iterator<std::string> oo(     // make output iterator for
        os, "\n");                             // stream

    // append "\n" each time
    std::vector<std::string> b(ii, eos);         // b is a vector initialized
                                                 // from input
    std::sort(b.begin(), b.end());               // sort the buffer
    std::unique_copy(b.begin(), b.end(), oo);    // copy buffer to output,
                                                 // discard replicated values
}
