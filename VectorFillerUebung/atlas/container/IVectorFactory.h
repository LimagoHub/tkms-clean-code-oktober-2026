//
// Created by JoachimWagner on 21.01.2026.
//

#pragma once
#include <vector>
#include <memory>

namespace atlas::container {

    template<class T>
    class IVectorFactory {
        using VectorPtr = std::unique_ptr<std::vector<T>>;
    public:
        virtual ~IVectorFactory() = default;
        [[nodiscard]] virtual auto createAndFillVector(const size_t size) -> VectorPtr = 0;

    };

} // namespace atlas::container
