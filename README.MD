# Webserv - HTTP Server in C++98

## Description

**Webserv** is a functional HTTP/1.1 server written from scratch in C++ 98. The goal of this project is to understand the internal mechanisms of the HTTP protocol, socket programming, and non-blocking I/O operations.

Unlike modern servers that use complex libraries, Webserv relies on the standard C++ 98 library and low-level system calls to handle networking. It mimics the behavior of NGINX, capable of handling multiple clients simultaneously without blocking, serving static files, and executing CGI scripts.

### Key Features
- **Non-blocking I/O:** Uses `epoll` to handle multiple connections within a single thread.
- **HTTP Methods:** Supports `GET`, `POST`, and `DELETE` requests.
- **Static Website Hosting:** Serves HTML, CSS, JS, and images.
- **CGI Support:** Executes external scripts (e.g., Python, PHP) to handle dynamic content.
- **File Upload:** Allows clients to upload files to the server.
- **Configuration:** Fully configurable via a file (ports, routes, error pages, body size limits).
- **Resilience:** Designed to never crash, ensuring high availability.

---

## Instructions

### specificites
- **OS:** Linux / MacOS
- **Compiler:** `c++` (clang++ or g++)
- **Standard:** C++ 98

### Compilation
To compile the project, navigate to the root directory and run:

```bash
make
```
### Contributors
<a href="https://github.com/zsailine">
	<img width=100 style="border-radius: 50px;" src="https://avatars.githubusercontent.com/u/149358747?v=4" >
</a>
<a href="https://github.com/mitiarenx">
	<img width=100 style="border-radius: 50px;margin-left: 25px" src="https://avatars.githubusercontent.com/u/169781187?v=4" >
</a>
<a href="https://github.com/tabasco39">
	<img width=100 style="border-radius: 50px;margin-left: 25px" src="https://avatars.githubusercontent.com/u/72312790?v=4" >
</a>