    
#include <iostream>
#include <vector>

int const DATA_SIZE = 65535;
int main()
{
    std::vector<char> data(DATA_SIZE, 0);
    auto data_ptr = data.begin();

    *data_ptr += -1;
    std::putchar(*data_ptr);
    data_ptr += 1;
    *data_ptr += 4;
    while (*data_ptr != 0) {
        data_ptr += -1;
        *data_ptr += 8;
        data_ptr += 1;
        *data_ptr += -1;
    }
    data_ptr += 1;
    *data_ptr += 8;
    while (*data_ptr != 0) {
        data_ptr += 1;
        *data_ptr += 4;
        data_ptr += -1;
        *data_ptr += -1;
    }
    data_ptr += 2;
    *data_ptr += 2;
    data_ptr += 3;
    *data_ptr += 1;
    data_ptr += 3;
    *data_ptr += 1;
    data_ptr += -10;
    while (*data_ptr != 0) {
        *data_ptr += -1;
        while (*data_ptr != 0) {
            *data_ptr += -1;
            data_ptr += 1;
            *data_ptr += 1;
            data_ptr += -1;
        }
        data_ptr += 1;
        while (*data_ptr != 0) {
            *data_ptr += -1;
            data_ptr += -1;
            *data_ptr += 1;
            data_ptr += 3;
            std::putchar(*data_ptr);
            data_ptr += -2;
        }
        data_ptr += 3;
        while (*data_ptr != 0) {
            while (*data_ptr != 0) {
                *data_ptr += -1;
                data_ptr += 1;
                *data_ptr += 8;
                while (*data_ptr != 0) {
                    data_ptr += 1;
                    *data_ptr += 4;
                    data_ptr += -1;
                    *data_ptr += -1;
                }
                data_ptr += 1;
                std::putchar(*data_ptr);
                data_ptr += -2;
                while (*data_ptr != 0) {
                    *data_ptr += -1;
                    data_ptr += 1;
                    *data_ptr += 1;
                    data_ptr += -1;
                }
                *data_ptr += 1;
                data_ptr += 1;
                while (*data_ptr != 0) {
                    *data_ptr += -1;
                    data_ptr += 1;
                    *data_ptr += 10;
                    data_ptr += -2;
                    *data_ptr += 1;
                    data_ptr += 1;
                }
                data_ptr += 1;
                std::putchar(*data_ptr);
                while (*data_ptr != 0) {
                    *data_ptr += -1;
                }
                data_ptr += 1;
            }
        }
        *data_ptr += 1;
        data_ptr += -3;
        while (*data_ptr != 0) {
            *data_ptr += -1;
            while (*data_ptr != 0) {
                *data_ptr += -1;
                data_ptr += 1;
                *data_ptr += 1;
                data_ptr += -1;
            }
            *data_ptr += 1;
            data_ptr += 1;
            while (*data_ptr != 0) {
                *data_ptr += -1;
                data_ptr += -1;
                *data_ptr += 1;
                data_ptr += 3;
                *data_ptr += -1;
                while (*data_ptr != 0) {
                    *data_ptr += -1;
                    data_ptr += 1;
                    *data_ptr += 1;
                    data_ptr += -1;
                }
                *data_ptr += 2;
                data_ptr += 1;
                while (*data_ptr != 0) {
                    *data_ptr += -1;
                    data_ptr += -1;
                    *data_ptr += -1;
                    data_ptr += 1;
                }
                data_ptr += -3;
            }
            data_ptr += -4;
        }
        *data_ptr += 10;
        std::putchar(*data_ptr);
        *data_ptr += 3;
        std::putchar(*data_ptr);
        while (*data_ptr != 0) {
            *data_ptr += -1;
        }
        data_ptr += -1;
    }
    *data_ptr += 5;
    
    return 0;    
}

