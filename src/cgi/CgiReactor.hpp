

#pragma once
#include <map>
#include "CgiJob.hpp"
#include "lib.hpp"
#include "class.hpp"

class Request; // forward

class CgiReactor {
public:
    static CgiReactor& instance();

    void registerJob(int epfd, CgiJob* job);
    bool isCgiFd(int fd) const;
    void handleIoEvent(int epfd, int fd, uint32_t events, Request& req);
    void forgetJob(CgiJob* job);
    void debugPrintJobs();

private:
    CgiReactor() {}
    CgiReactor(const CgiReactor&);
    CgiReactor& operator=(const CgiReactor&);
    std::map<int, CgiJob*> _byFd;
    static void setNonBlocking_(int fd);
    static void setCloExec_(int fd);
    static void parseCgiHeaders_(CgiJob* job);
    static bool childIsDone_(pid_t pid);
    void finalize_(int epfd, CgiJob* job, Request& req);
};
