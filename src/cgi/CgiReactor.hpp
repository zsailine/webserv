

#pragma once
#include <map>
#include "CgiJob.hpp"
#include "lib.hpp"
#include "class.hpp"

class Request; // forward

class CgiReactor {
public:
    static CgiReactor& instance();

    // Après fork + préparation du job, on enregistre ses fds dans epoll
    void registerJob(int epfd, CgiJob* job);

    // Pour Run::run() → savoir si fd appartient à un CGI
    bool isCgiFd(int fd) const;

    // Dispatcher IO CGI (appelé depuis Run::run)
    void handleIoEvent(int epfd, int fd, uint32_t events, Request& req);

    // Nettoyage forcé (optionnel)
    void forgetJob(CgiJob* job);
    void debugPrintJobs();

private:
    CgiReactor() {}
    CgiReactor(const CgiReactor&);
    CgiReactor& operator=(const CgiReactor&);

    // Map: n'importe quel fd (cgi_in ou cgi_out) -> même pointeur Job
    std::map<int, CgiJob*> _byFd;

    // ---- internes ----
    static void setNonBlocking_(int fd);
    static void setCloExec_(int fd);
    static void parseCgiHeaders_(CgiJob* job);
    static bool childIsDone_(pid_t pid);
    void finalize_(int epfd, CgiJob* job, Request& req);
};
