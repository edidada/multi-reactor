
#pragma once
#include <cstdint>
#include <sys/epoll.h>

// #define EVENT_READ EPOLLIN
// #define EVENT_WRITE EPOLLOUT
// #define EVENT_ERROR EPOLLERR
// #define EVENT_HUP EPOLLHUP
// #define EVENT_RDHUP EPOLLRDHUP

class IPoller {
public:
    virtual ~IPoller() = default;

    virtual void AddEvent(int fd, uint32_t events, void* ptr) = 0;
    virtual void ModEvent(int fd, uint32_t events, void* ptr) = 0;
    virtual void DelEvent(int fd) = 0;
    virtual void Run() = 0;
};