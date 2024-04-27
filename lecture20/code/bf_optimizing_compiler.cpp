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

int bf_compiler()
{
}

int main()
try
{
    bf_compiler();
    return 0;
}
catch (std::exception& e)
{
    std::cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    std::cerr << "Some exception\n";
    return 2;
}
