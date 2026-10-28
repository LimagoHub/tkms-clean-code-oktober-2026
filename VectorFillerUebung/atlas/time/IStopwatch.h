//
// Created by JoachimWagner on 21.01.2026.
//

#pragma once
#include <chrono>
namespace atlas::time {

    class IStopwatch {
    public:
        virtual ~IStopwatch() = default;

        /**
         * @throws StopwatchException
         */
        virtual auto start() noexcept -> void = 0;
        virtual auto stop() noexcept -> void = 0;

        [[nodiscard]] virtual auto getDuration() const noexcept -> std::chrono::milliseconds = 0;
    };

} // time
