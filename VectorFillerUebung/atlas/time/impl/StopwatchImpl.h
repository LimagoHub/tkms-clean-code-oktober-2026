//
// Created by JoachimWagner on 10.04.2024.
//

#pragma once
#include "../IStopwatch.h"

namespace atlas::time {

    class StopwatchImpl : public IStopwatch {
        using TimePoint = std::chrono::high_resolution_clock::time_point;

        TimePoint start_;
        TimePoint end_;

    public:
        StopwatchImpl() = default;
        ~StopwatchImpl() override = default;

        auto start() noexcept -> void override {
            start_ = std::chrono::high_resolution_clock::now();
        }

        auto stop() noexcept -> void override {
            end_ = std::chrono::high_resolution_clock::now();
        }

        auto getDuration() const noexcept -> std::chrono::milliseconds override {
            return std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_);
        }
    };

}
