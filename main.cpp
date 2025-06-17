
#include <sys/stat.h>

#define PORT 8080
#define BUF_SIZE 4096
#define MAX_EVENTS 2

#include "ServerSocket.hpp"
int main()
{
	ServerSocket socket1(8080);
	std::cout << "socket is at " << socket1.getSocket() << std::endl;
	return (0);
}