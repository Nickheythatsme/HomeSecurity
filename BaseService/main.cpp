#include <iostream>
#include <unistd.h>
#include "src/networking/listener.h"

using std::cout;
using std::endl;
using namespace BASE_SERVICE::NETWORKING;

int main()
{
    Listener listener;
    listener.do_listen();
    return 0;
}