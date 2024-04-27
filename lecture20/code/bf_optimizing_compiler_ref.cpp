// Brainfuck (bf) optimizing compiler

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Hello World!
// ++++++++++[>+++++++>++++++++++>+++>+<<<<-]
// >++.>+.+++++++..+++.>++.
// <<+++++++++++++++.>.+++.------.--------.>+.>.

std::string program = R"(

// This program prints Sierpinski triangle on 80-column display.
//                                >    
//                               + +    
//                              +   +    
//                             [ < + +    
//                            +       +    
//                           + +     + +    
//                          >   -   ]   >    
//                         + + + + + + + +    
//                        [               >    
//                       + +             + +    
//                      <   -           ]   >    
//                     > + + >         > > + >    
//                    >       >       +       <    
//                   < <     < <     < <     < <    
//                  <   [   -   [   -   >   +   <    
//                 ] > [ - < + > > > . < < ] > > >    
//                [                               [    
//               - >                             + +    
//              +   +                           +   +    
//             + + [ >                         + + + +    
//            <       -                       ]       >    
//           . <     < [                     - >     + <    
//          ]   +   >   [                   -   >   +   +    
//         + + + + + + + +                 < < + > ] > . [    
//        -               ]               >               ]    
//       ] +             < <             < [             - [    
//      -   >           +   <           ]   +           >   [    
//     - < + >         > > - [         - > + <         ] + + >    
//    [       -       <       -       >       ]       <       <    
//   < ]     < <     < <     ] +     + +     + +     + +     + +    
//  +   .   +   +   +   .   [   -   ]   <   ]   +   +   +   +   +    
// * * * * * M a d e * B y : * N Y Y R I K K I * 2 0 0 2 * * * * *    

)";

std::ostream& emit(std::ostream& out, int level, std::string const& str)
{
    while (level-- >= 0)
        out << "    ";

    out << str << "\n";
    return out;
}

std::ostream& emit(
    std::ostream& out, int level, std::string const& str, int offset)
{
    while (level-- >= 0)
        out << "    ";

    out << str << offset << ";\n";
    return out;
}

template <typename Iterator>
int get_data_ptr_offset(Iterator& ptr, Iterator end)
{
    int offset = 0;
    for (/**/; ptr != end; ++ptr)
    {
        switch (*ptr)
        {
        case '>':
            ++offset;
            break;
        case '<':
            --offset;
            break;

        case '+':
        case '-':
        case '[':
        case ']':
        case ',':
        case '.':
            --ptr;
            return offset;

        default:
            break;
        }
    }
    --ptr;
    return offset;
}

template <typename Iterator>
int get_data_cell_delta(Iterator& ptr, Iterator end)
{
    int delta = 0;
    for (/**/; ptr != end; ++ptr)
    {
        switch (*ptr)
        {
        case '+':
            ++delta;
            break;
        case '-':
            --delta;
            break;

        case '>':
        case '<':
        case '[':
        case ']':
        case ',':
        case '.':
            --ptr;
            return delta;

        default:
            break;
        }
    }
    --ptr;
    return delta;
}

int main()
{
    int level = 0;

    std::ofstream out("../../code/bf_code.cpp");

    emit(out, level, R"(
#include <iostream>
#include <vector>

int const DATA_SIZE = 65535;
int main()
{
    std::vector<char> data(DATA_SIZE, 0);
    auto data_ptr = data.begin();
)");

    for (auto program_ptr = program.begin(); program_ptr != program.end();
         ++program_ptr)
    {
        switch (*program_ptr)
        {
        case '>':    // increment the data pointer
        case '<':    // decrement the data pointer
        {
            int offset = get_data_ptr_offset(program_ptr, program.end());
            emit(out, level, "data_ptr += ", offset);
        }
        break;

        case '+':    // increment the byte at the data pointer
        case '-':    // decrement the byte at the data pointer
        {
            int delta = get_data_cell_delta(program_ptr, program.end());
            emit(out, level, "*data_ptr += ", delta);
        }
        break;

        case '.':    // output the byte at the data pointer
            emit(out, level, "std::putchar(*data_ptr);");
            break;

        case ',':    // accept one byte of input, storing its value
                     // in the byte at the data pointer
            emit(out, level, "*data_ptr = std::getchar();");
            break;

        case '[':
            emit(out, level, "while (*data_ptr != 0) {");
            ++level;
            break;

        case ']':
            --level;
            emit(out, level, "}");
            break;
        }
    }

    emit(out, level, R"(
    return 0;    
}
)");

    return 0;
}
