#include "listener.h"
#include <iostream>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <unistd.h>

namespace BASE_SERVICE {
namespace NETWORKING {

#define PORT 8000

Listener::Listener()
{
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address); 

    if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        std::cerr << "socket failed\n";
        exit(EXIT_FAILURE); 
    }

    // Attach the socket to the port
    if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(this->server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        std::cerr << "bind failed\n";
        exit(EXIT_FAILURE); 
    } 
    if (listen(this->server_fd, 3) < 0) 
    { 
        std::cerr << "listen\n";
        exit(EXIT_FAILURE); 
    } 
    std::cout << "Listening on " << PORT << '\n';
}

} // ns NETWORKING
} // ns BASE_SERVICE
