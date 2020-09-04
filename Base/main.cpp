#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

int main()
{
    while (true) {
        sleep(1);
        cout << "This is a test!!" << endl;
    }
    return 0;
}