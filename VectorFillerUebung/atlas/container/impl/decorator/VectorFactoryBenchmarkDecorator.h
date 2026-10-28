//
// Created by JoachimWagner on 28.10.2026.
//

#pragma once
#include "../../IVectorFactory.h"


namespace atlas::container {
    template<typename T>
    class VectorFactoryBenchmarkDecorator : public IVectorFactory<T> {
    };
}
