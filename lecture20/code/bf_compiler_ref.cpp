// Brainfuck (bf) compiler

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Hello World!
// ++++++++++[>+++++++>++++++++++>+++>+<<<<-] 
// >++.>+.+++++++..+++.>++.
// <<+++++++++++++++.>.+++.------.--------.>+.>.

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

std::string program = R"(

)";

std::ostream& emit(std::ostream& out, int level, std::string const& str)
{
    while (level-- >= 0)
        out << "    "; 

    out << str << "\n";
    return out;
}

int main()
{
    int level = 0;

    emit(std::cout, level, R"(
#include <iostream>
#include <vector>

int const DATA_SIZE = 65535;
int main()
{
    std::vector<char> data(DATA_SIZE, 0);
    auto data_ptr = data.begin();
)");

    for (auto program_ptr = program.begin(); 
         program_ptr != program.end(); 
         ++program_ptr) 
    {
        switch(*program_ptr)
        {
        case '>':       // increment the data pointer 
            emit(std::cout, level, "++data_ptr;");
            break;

        case '<':       // decrement the data pointer 
            emit(std::cout, level, "--data_ptr;");
            break;

        case '+':       // increment the byte at the data pointer 
            emit(std::cout, level, "++*data_ptr;");
            break;

        case '-':       // decrement the byte at the data pointer 
            emit(std::cout, level, "--*data_ptr;");
            break;

        case '.':       // output the byte at the data pointer
            emit(std::cout, level, "std::putchar(*data_ptr);");
            break;

        case ',':       // accept one byte of input, storing its value 
                        // in the byte at the data pointer
            emit(std::cout, level, "*data_ptr = std::getchar();");
            break;

        case '[':
            emit(std::cout, level, "while (*data_ptr != 0) {");
            ++level;
            break;

        case ']':
            --level;
            emit(std::cout, level, "}");
            break;
        }
    }

    emit(std::cout, level, R"(
    return 0;    
}
)");

    return 0;
}
