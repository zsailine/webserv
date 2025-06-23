# Webserv

## 1. FUNCTIONS 

#### :pig: ``` const char *gai_strerror( int errcode ) ```

In the library **<ins>netdb.h</ins>**

This function returns a string describing an error value for the ``` getaddrinfo() ``` and ``` getnameinfo() ```


#### :pig: ``` int socketpair( int domain, int type, int protocol, int sv[2] ) ```

In the library **<ins>sys/socket.h</ins>**

This function creates a pari of connected, unnamed sockets and can be used for inter-process communication (IPC), like pipes.
- **<ins>domain</ins> :** Sockets operates within address domains, ```AF_UNIX``` for local communication and ```AF_INET``` for network communication
- **<ins>type</ins> :** Two primary socket type exists ```SOCK_STREAM``` (stream sockets : TCP => for reliable, connection-oriented communication) and ```SOCK_DGRAM``` (datagram sockets : UDP => for connectionless, unreliable communication)
- **<ins>protocol</ins> :** Generally set to 0 so that the operating system choose the most common type of socket within the given address family.
- **<ins>sv</ins> :** The descriptors used to refer to the obtained sockets.

 **<ins>Exemple</ins> :**
	```
	domain = AF_INET;
	type = SOCK_STREAM;
	protocol = TCP;
	```

#### :pig: ``` uint32_t htonl( uint32_t hostlong ) ```
#### :pig: ``` uint16_t htons( uint16_t hostshort ) ```
#### :pig: ``` uint32_t ntohl( uint32_t netlong ) ```
#### :pig: ``` uint16_t ntohs( uint16_t netshort ) ```

In the library **<ins>arpa/inet.h</ins>**

*Host Byte order* is the order in which the bytes are arranged in memory (big or little endian) within a particular computer's achitecture and *Network Byte Order* is the standardized big endian used for transmetting data over networks, ensuring compatibility across different computer architectures.

- **<ins>htonl</ins> :** unsigned integer host byte order to network byte order
- **<ins>htons</ins> :** unsigned short integer host byte order to network byte order
- **<ins>ntohl</ins> :** unsigned integer network byte ordre to host byte order
- **<ins>ntohs</ins> :** unsigned short integer network byte order to host byte order

#### :pig: ``` int select( int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout ) ```

In the library **<ins>sys/time.h</ins>**

This function take a file descriptor first to be tesets and indicates which of the specified file desciptors or ```fd_set``` is ready for reading, for writing or has an error condition pending. If all are false, he blocks until ```timeout``` interval.

- **<ins>nfds</ins> :** the range of file descriptor to be tested (0 to -1)
- **<ins>readfds</ins> :** if not NULL, on input specifies the file descriptors to be checked for being ready to read, and on output indicates which file descriptors are ready to read.
- **<ins>writefds</ins> :** if not NULL, on input specifies the file descriptors to be checked for being ready to write, and on output indicates which file descriptors are ready to write.
- **<ins>errorfds</ins> :** if not NULL, on input specifies the file descriptors to be checked for error conditions pending, and on output indicates which file descriptors have error conditions pending.
- **<ins>timeout</ins> :** if not NULL, specifies a maximum interval to wait for the selection to complete. If the timeout argument points to an object of type struct timeval whose members are 0, ```select()``` does not block. If the timeout argument is a null pointer, ```select()``` blocks until an event causes one of the masks to be returned with a valid (non-zero) value. If the time limit expires before any event occurs that would cause one of the masks to be set to a non-zero value, ```select()``` completes successfully and returns 0.

#### :pig: ``` int poll( struct pollfd fds[], nfds_t nfds, int timeout ) ```

In the library **<ins>poll.h</ins>**

Similar to ```select()```, it waits for one of a set of file descriptors ro become ready to perform for I/O operations (reading or writing).

- **<ins>fds</ins> :** defines the file descriptor to be monitored with three members. ```int fd``` (the file descriptor to monitor) ; ```short events``` (the events the program is interested in like POLLIN) ; ```short revents``` (the events that actually occured).
- **<ins>nfds</ins> :** unsigned integer type that represents the number of file descriptors monitored by ```poll()```.
- **<ins>timeout</ins> :** the amount of time, in milliseconds, to wait for an event to occur.
If none of the defined events have occurred on any selected descriptor, poll() waits at least timeout milliseconds for an event to occur on any of the selected descriptors. If the value of timeout is 0, poll() returns immediately. If the value of timeout is -1, poll() blocks until a requested event occurs or until the call is interrupted.

#### :pig: ``` int epoll_create( iont size ) ```
#### :pig: ``` int epoll_ctl( int epfd, int op, int fd, struct epoll_event *event ) ```
#### :pig: ``` int epoll_wait( int epfd, struct epoll_event events[.maxevents], int maxevents, int timeout ) ```

In the library **<ins>sys/epoll.h</ins>**

- **<ins>epoll_create</ins> :** returns a file descriptor referring to the new epoll instance.

- **<ins>epoll_ctl</ins> :** a control interface for managing an epoll file descriptor. It's used to add, modify, or remove file descriptors from an epoll instance's interest list
	- *epfd* is an integer representing the epoll file descriptor obtained from a previous call to ```epoll_create()```
	- *op* is an integer indicating the operation to perform on the epoll file descriptor. It can be one of the following values ```EPOLL_CTL_ADD``` or ```EPOLL_CTL_MOD``` or ```EPOLL_CTL_DEL```
	- *fd* is an integer representing the file descriptor on which the operation will be performed
	- *event* is a pointer to an epoll_event structure. This structure contains ```events``` that is a bitmask of event types to be monitored on the file descriptor (EPOLLIN, etc) and ```data``` that is a union that can hold either a pointer (ptr), a file descriptor (fd), or a 32/64-bit number (u32/u64). This is used to associate arbitrary data with the file descriptor.

- **<ins>epoll_wait</ins> :** waits for events on the epoll instance referred to by the file descriptor epfd.

#### :pig: ``` int kqueue( void ) ```
#### :pig: ``` int kevent( int kq, const struct	kevent *changelist, int nchanges, struct kevent *eventlist, int nevents, const struct timespec *timeout ) ```

In the library **<ins>sys/event.h</ins>**

- **<ins>kqueue</ins> :** provides a generic method of notifying the user when an event happens or a condition holds, based on  the  results of  small pieces	of kernel code termed filters.
- **<ins>kevent</ins> :** system call	is used	to register events with	the queue, and return  any  pending  events to the user.

#### :pig: ``` int socket( int domain, int type, int protocol ) ```

In the library **<ins>sys/socket.h</ins>**

This function creates an endpoint communicaton and return a file descriptor.

#### :pig: ``` int accept( int socket, struct sockaddr *address, socklen_t *address_len ) ```

In the library **<ins>sys/socket.h</ins>**

This function extract the first connection on the queue of pending connections, create a new socket with the same socket type protocol and address family as the specified socket, and allocate a new file descriptor for that socket.

- **<ins>socket</ins> :** specifies a socket that was created with ```socket()```
- **<ins>address</ins> :** a pointer to a sockaddr structure where the address of the connecting socket shall be returned.
- **<ins>address_len</ins> :** on input specifies the length of the supplied sockaddr structure, and on output specifies the length of the stored address.

#### :pig: ``` int listen( int socket, int backlog ) ```

In the library **<ins>sys/socket.h</ins>**

This function marks a connection-mode ```socket```, specified by the socket argument, as accepting connections. The ```backlog``` parameter defines the maximum number of pending connections that can be queued.

#### :pig: ``` ssize_t send( int socket, const void *buffer, size_t length, int flags ) ```

In the library **<ins>sys/socket.h</ins>**

This function initiate transmission of a message from the specified socket to its peer. The ```flags``` specifies the type of message transmission : ```MSG_EOR``` and ```MSG_OOB```.

#### :pig: ``` ssize_t recv( int socket, const void *buffer, size_t length, int flags ) ```

In the library **<ins>sys/socket.h</ins>**

This function receives a message from a connection-mode or connectionless-mode socket. It is normally used with connected sockets because it does not permit the application to retrieve the source address of received data.

#### :pig: ``` int bind( int socket, const struct sockaddr *address, socklen_t address_len ) ```

In the library **<ins>sys/socket.h</ins>**

This functions assigns a local socket address address to a socket identified by descriptor socket that has no local socket address assigned. Sockets created with the ```socket()``` function are initially unnamed; they are identified only by their address family.

#### :pig: ``` int connect( int socket, const struct sockaddr *address, socklen_t address_len ) ```

In the library **<ins>sys/socket.h</ins>**

This function attempts to make a connection on a socket. The function takes the following arguments ```address``` which points to a sockaddr structure containing the peer address. The length and format of the address depend on the address family of the socket and ```address_len``` which specifies the length of the sockaddr structure pointed to by the address argument.

#### :pig: ``` int getaddrinfo( const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res ) ```

In the library **<ins>sys/types.h</ins>** ou **<ins>sys/socket.h</ins>** ou **<ins>netdb.h</ins>**

This function is used for translating human-readable hostnames or IP addresses into socket addresses. It provides a protocol-independent way to obtain address information, supporting both IPv4 and IPv6.

#### :pig: ``` void freeaddrinfo( struct addrinfo *ai ) ```

In the library **<ins>sys/socket.h</ins>** ou **<ins>netdb.h</ins>**

This functions frees one or more addrinfo structures returned by ```getaddrinfo()```, along with any additional storage associated with those structures. If the ai_next field of the structure is not null, the entire list of structures shall be freed. The ```freeaddrinfo()``` function shall support the freeing of arbitrary sublists of an addrinfo list originally returned by ```getaddrinfo()```

#### :pig: ``` int setsockopt( int sockfd, int level, int optname, const void *optval, socklen_t optlen ) ```

In the library **<ins>sys/socket.h</ins>**

This functions sets the option specified by the ```optname``` argument, at the protocol level specified by the ```level``` argument, to the value pointed to by the ```optval``` argument for the socket associated with the file descriptor specified by the socket argument.

#### :pig: ``` int getsockname( int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen ) ```

In the library **<ins>sys/socket.h</ins>**

This functions returns the current address to which the socket ```sockfd``` is bound, in the buffer pointed to by ```addr```.  The ```addrlen``` argument should be initialized to indicate the amount of space (in bytes) pointed to by ```addr```. On return it contains the actual size of the socket address.

#### :pig: ``` struct protoent *getprotobyname( const char *name ) ```

In the library **<ins>netdb.h</ins>**

This function searches the /etc/protocol or tcpip.ETC.PROTO data set for the specified protocol name, ```name``` is the name of the protocol.
