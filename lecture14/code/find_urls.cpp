
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool not_url_char(char c)
{
    // characters, in addition to alpha-numerics, that can
    // appear in a URL
    static std::string const url_ch = "~;/?:@=&$-_.+!*'(),";

    // see whether c can appear in a URL and return the negative
    return !(std::isalnum(c) ||
        std::find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

std::string::const_iterator url_beg(
    std::string::const_iterator b, std::string::const_iterator e)
{
    static std::string const sep = "://";

    auto i = b;    // i marks where the separator was found
    while ((i = std::search(i, e, sep.begin(), sep.end())) != e)
    {
        // make sure the separator isn't at the beginning or end of the line
        if (i != b && i + sep.size() != e)
        {
            // beg marks the beginning of the protocol-name
            auto beg = i;
            while (beg != b && std::isalpha(beg[-1]))
                --beg;

            // is there at least one appropriate character before and after the separator?
            if (beg != i && !not_url_char(i[sep.size()]))
                return beg;
        }

        // the separator we found wasn't part of a URL, advance i past this separator
        i += sep.size();
    }
    return e;
}

std::string::const_iterator url_end(
    std::string::const_iterator b, std::string::const_iterator e)
{
    return std::find_if(b, e, not_url_char);
}

std::vector<std::string> find_urls(std::string const& s)
{
    std::vector<std::string> ret;

    // look through the entire input
    auto b = s.begin(), e = s.end();
    while (b != e)
    {
        // look for one or more letters followed by ://
        b = url_beg(b, e);

        // if we found it
        if (b != e)
        {
            auto after = url_end(b, e);              // get the rest of the URL
            ret.push_back(std::string(b, after));    // remember the URL
            b = after;    // advance b and check for more URLs on this line
        }
    }
    return ret;
}

std::string read_all_of_file(std::ifstream& in)
{
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

int main()
{
    std::ifstream duckduckgo("duckduckgo.html");

    std::string html = read_all_of_file(duckduckgo);
    std::vector<std::string> urls = find_urls(html);

    for (auto const& url : urls)
        std::cout << url << "\n";

    return 0;
}