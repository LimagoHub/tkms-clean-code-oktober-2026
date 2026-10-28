//
// Created by JoachimWagner on 22.10.2025.
//

#pragma once

namespace atlas::generator {
    template<class T>
    class IGenerator {
    public:
        virtual ~IGenerator() = default;
        [[nodiscard]]virtual auto next() noexcept -> T = 0;
    };
}
