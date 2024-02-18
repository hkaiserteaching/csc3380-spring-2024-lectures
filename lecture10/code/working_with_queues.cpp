
#include <iostream>
#include <queue>
#include <string>

void manage_queue()
{
    std::queue<std::string> waiting_strings;    // queue of 'waiting' strings
    while (true)
    {
        std::cout << "?> ";    // ask for next line of text
        std::string response;
        std::getline(std::cin, response);

        if (response.empty())
            break;
        if (response == "next")
        {
            // try to dequeue
            if (waiting_strings.empty())
                std::cout << "No one waiting!" << std::endl;
            else
            {
                std::cout << waiting_strings.front() << std::endl;
                waiting_strings.pop();
            }
        }
        else
        {
            // enqueue the line read
            waiting_strings.push(response);
        }
    }
}

int main()
{
    manage_queue();
    return 0;
}
