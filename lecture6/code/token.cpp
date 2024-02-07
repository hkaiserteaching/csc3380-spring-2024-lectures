
#include <iostream>
#include <stdexcept>

// Token stuff
struct token
{
    char kind;       // what kind of token
    double value;    // for numbers: a value

    // constructors
    token(char ch)
      : kind(ch)
      , value(0)
    {
    }
    token(char ch, double val)
      : kind(ch)
      , value(val)
    {
    }
};

class token_stream
{
    // representation: not directly accessible to users:
    bool full;       // is there a token in the buffer?
    token buffer;    // here is where we keep a Token put back using
                     // putback()
public:
    // user interface:
    token get();            // get a token
    void putback(token);    // put a token back into the token_stream

    // constructor: make a token_stream, the buffer starts empty
    token_stream()
      : full(false)
      , buffer(0)
    {
    }
};

void token_stream::putback(token t)
{
    if (full)
        throw std::runtime_error("putback() into a full buffer");
    buffer = t;
    full = true;
}

token token_stream::get()    // read a token from the token_stream
{
    if (full)
    {
        full = false;
        return buffer;
    }    // check if we already have a Token ready

    char ch;
    std::cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch)
    {
    case '(': case ')': case ';': case 'q':
    case '+': case '-': case '*': case '/':
        return token(ch);    // let each character represent itself
    case '.': case '0': case '1': case '2': case '3':
    case '4': case '5': case '6': case '7': case '8':
    case '9':
    {
        std::cin.putback(ch);    // put digit back into the input stream
        double val;
        std::cin >> val;                // read a floating-point number
        return token('8', val);    // let ‘8’ represent “a number”
    }
    default:
        throw std::runtime_error("Bad token");
    }
}

int main()
{
    // work with tokens
    token t('8', 2.3);    // (use '8' to mean “number”)

    token u = t;    // a token behaves much like a built-in type, such as int
                    // so u becomes a copy of t
    std::cout << u.value << "\n";    // will print 2.3

    // simple use of token_stream
    token_stream ts;
    ts.putback(u);

    std::cout << ts.get().value << "\n";    // will print 2.3

    return 0;
}
