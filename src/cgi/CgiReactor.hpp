/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiReactor.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranaivo <aranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:34:55 by zsailine          #+#    #+#             */
/*   Updated: 2025/09/10 08:49:15 by aranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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

private:
    CgiReactor() {}
    CgiReactor(const CgiReactor&);
    CgiReactor& operator=(const CgiReactor&);
    std::map<int, CgiJob*> _byFd;
    static void parseCgiHeaders_(CgiJob* job);
    static bool childIsDone_(pid_t pid);
    void finalize_(int epfd, CgiJob* job, Request& req);
};
