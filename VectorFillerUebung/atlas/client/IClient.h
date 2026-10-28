//
// Created by JoachimWagner on 28.10.2026.
//

#pragma once

namespace atlas::client {
    class IClient {
    public:
        virtual ~IClient() = default;
        virtual auto processVector() -> void = 0;
    };
} // client