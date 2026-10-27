//
// Created by JoachimWagner on 20.01.2026.
//

#pragma once

#include <string>

namespace io {

    class IWriter {
    public:
        virtual ~IWriter() = default;
        virtual auto write(const std::string & message) const -> void = 0;
    };

} // io
