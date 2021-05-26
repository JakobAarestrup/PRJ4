#include <string>

class BossBoundary
{
private:
    int server_fd, new_socket, valread;
    char buffer[1024] = {0};
public:
    BossBoundary(/* args */);
    ~BossBoundary();
    std::string receive();
    void deliveryFinnished();
    std::string tableNo;
};