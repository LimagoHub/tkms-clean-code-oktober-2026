//
// Created by JoachimWagner on 10.04.2024.
//

//
// Created by JoachimWagner on 10.04.2024.
//

#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <iostream>
#include "../IClient.h"
#include "../../container/IVectorFactory.h"

namespace atlas::client {

    class VectorClientImpl : public IClient {
        using FactoryPtr = std::unique_ptr<atlas::container::IVectorFactory<int>>;

        FactoryPtr factory_;



    public:
        explicit VectorClientImpl(FactoryPtr factory) : factory_{std::move(factory)} {}
        ~VectorClientImpl() override = default;

        auto processVector() -> void override {
            auto v = factory_->createAndFillVector(INT32_MAX / 4);
            for (int i = 0; i < 3; ++i) {
                std::cout << v->at(i) << std::endl;
            }
        }
    };

}