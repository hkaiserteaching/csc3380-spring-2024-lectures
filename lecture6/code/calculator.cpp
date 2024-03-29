
#include <iostream>
#include <stdexcept>
#include <string>

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

// single global instance of the token_stream
token_stream ts;

void token_stream::putback(token t)
{
    if (full)
        throw std::runtime_error("putback() into a full buffer");
    buffer = t;
    full = true;
}

token token_stream::get()    // read a token from the token_stream
{
    // check if we already have a Token ready
    if (full)
    {
        full = false;
        return buffer;
    }

    // note that >> skips whitespace (space, newline, tab, etc.)
    char ch;
    std::cin >> ch;

    switch (ch)
    {
    case '(':
    case ')':
    case ';':
    case 'q':
    case '+':
    case '-':
    case '*':
    case '/':
        return token(ch);    // let each character represent itself
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        std::cin.putback(ch);      // put digit back into the input stream
        double val;
        std::cin >> val;           // read a floating-point number
        return token('8', val);    // let ‘8’ represent “a number”
    }
    default:
        throw std::runtime_error("Bad token");
    }
}

// declaration so that primary() can call expression()
double expression();

double primary()    // Number or ‘(‘ Expression ‘)’
{
    token t = ts.get();
    switch (t.kind)
    {
    case '(':    // handle ‘(’expression ‘)’
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
            throw std::runtime_error("')' expected");
        return d;
    }
    case '8':    // we use ‘8’ to represent the “kind” of a number
        return t.value;    // return the number’s value
    default:
        throw std::runtime_error("primary expected");
    }
}

// exactly like expression(), but for * and /
double term()
{
    double left = primary();    // get the Primary
    while (true)
    {
        token t = ts.get();     // get the next Token ...
        switch (t.kind)
        {
        case '*':
            left *= primary();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0)
                throw std::runtime_error("divide by zero");
            left /= d;
            break;
        }
        default:
            ts.putback(t);    // <<< put the unused token back
            return left;      // return the value
        }
    }
}

// read and evaluate: 1   1+2.5   1+2+3.14  etc.
// 	 return the sum (or difference)
double expression()
{
    double left = term();      // get the Term
    while (true)
    {
        token t = ts.get();    // get the next token ...
        switch (t.kind)        // ... and do the right thing with it
        {
        case '+':
            left += term();
            break;
        case '-':
            left -= term();
            break;
        default:
            ts.putback(t);    // <<< put the unused token back
            return left;      // return the value of the expression
        }
    }
}

int main()
try
{
    double val = 0;

    while (std::cin)
    {
        token t = ts.get();
        if (t.kind == 'q')
            break;    // ‘q’ for “quit”

        if (t.kind == ';')               // ‘;’ for “print now”
            std::cout << val << '\n';    // print result
        else
            ts.putback(t);
            
        val = expression();    // evaluate
    }
    return 0;
}
catch (std::runtime_error& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "exception \n";
    return 2;
}

