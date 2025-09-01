#pragma once

#include "EventLoop.h"
#include "IPoller.h"
#include <thread>
#include <mutex>

class Poller : public IPoller {
public:
    Poller() : eventLoop_(), thread_(&Poller::Run, this) {}

    ~Poller() {
        if (thread_.joinable()) {
            thread_.join();
        }
    }

    void Run() override {
        eventLoop_.Run();
    }

    void AddEvent(int fd, uint32_t events, void* ptr) override {
        eventLoop_.AddEvent(fd, events, ptr);
    }

    void ModEvent(int fd, uint32_t events, void* ptr) override {
        eventLoop_.ModEvent(fd, events, ptr);
    }

    void DelEvent(int fd) override {
        eventLoop_.DelEvent(fd);
    }

    std::mutex& GetMutex() {
        return mutex_;
    }

private:
    EventLoop eventLoop_;
    std::thread thread_;
    std::mutex mutex_;
};