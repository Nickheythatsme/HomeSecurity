#include <sys/types.h>
#include <sys/socket.h>
#include <memory>

#ifndef BASE_SERVICE_LISTENER_
#define BASE_SERVICE_LISTENER_
namespace BASE_SERVICE {
namespace NETWORKING {

class Listener {
    public:
        Listener();
        ~Listener();
    private:
        int server_fd;
};

} // ns NETWORKING
} // ns BASE_SERVICE

#endif //BASE_SERVICE_LISTENER_
