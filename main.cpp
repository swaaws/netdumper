#include <iostream>
#include <cstring> 
#include <sys/socket.h> 
#include <netdb.h> 
#include <unistd.h>


int main(void)
{

#define httpgetheader "GET / HTTP/1.1\nHost: www.google.de\n\n"
#define reciveddatalenth 1005
#define hosturl "www.dropbox.de"
#define hostport "80"

int status;
struct addrinfo host_info; 
struct addrinfo *host_info_list; 

memset(&host_info, 0, sizeof host_info);

std::cout << "[INFO]              | Setting up the structs..." << std::endl;

host_info.ai_family = AF_UNSPEC; 
host_info.ai_socktype = SOCK_STREAM;
std::cout << "[getaddrinfo()]     | Connect to host... " << std::endl;

status = getaddrinfo(hosturl, hostport, &host_info, &host_info_list);
if (status != 0){
std::cout << "getaddrinfo error" << gai_strerror(status) ;

} else 
std::cout << "[INFO]              | Succsess!" << std::endl;


std::cout << "[socket()]          | Creating a socket..." << std::endl;
int socketfd ;
socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
host_info_list->ai_protocol);
if (socketfd == -1) std::cout << "Socket error " ;

std::cout << "[connect()]         | Connecting..." << std::endl;
status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
if (status == -1) std::cout << "connect error" ;

std::cout << "[send()]            | Sending message..." << std::endl;

int len;
ssize_t bytes_sent;
len = strlen(httpgetheader);
bytes_sent = send(socketfd, httpgetheader, len, 0);

std::cout << "[recv()]            | Waiting to recieve data..." << std::endl;
ssize_t bytes_recieved;
char incoming_data_buffer[reciveddatalenth];
bytes_recieved = recv(socketfd, incoming_data_buffer,reciveddatalenth, 0);

if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;
std::cout << "[INFO]              | Bytes recieved :" << bytes_recieved << std::endl ;
std::cout << "----------------------[recived-data-begin]------------------------" << std::endl;
std::cout << incoming_data_buffer << std::endl;
std::cout << "-----------------------[recived-data-end]-------------------------" << std::endl;

std::cout << "[close()]           | Receiving complete. Closing socket..." << std::endl;
freeaddrinfo(host_info_list);
close(socketfd);
std::cout << "[INFO]              | End" << std::endl;

  return 0;
}
