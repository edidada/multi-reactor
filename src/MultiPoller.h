#pragma once

#include <vector>
#include "IPoller.h"
#include "Poller.h"

template<size_t N>
class MultiPoller : public IPoller {
public:
    static_assert(N > 1, "N must be greater than 1");
    MultiPoller() {
        for (int i = 0; i < N; ++i) {
            pollers_.emplace_back(new Poller());
        }
    }

    ~MultiPoller() {
        for (auto poller : pollers_) {
            delete poller;
        }
    }

    void AddEvent(int fd, uint32_t events, void* ptr) override {
        int index = fd % pollers_.size();
        pollers_[index]->AddEvent(fd, events, ptr);
    }
    void ModEvent(int fd, uint32_t events, void* ptr) override {
        int index = fd % pollers_.size();
        pollers_[index]->ModEvent(fd, events, ptr);
    }
    void DelEvent(int fd) override {
        int index = fd % pollers_.size();
        pollers_[index]->DelEvent(fd);
    }

    void Run() override {}

private:
    std::vector<Poller*> pollers_;
};