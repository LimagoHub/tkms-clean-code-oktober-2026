#include <memory>
#include "atlas/client/impl/ClientImpl.h"
#include "atlas/container/impl/sequential/VectorFactorySequentialImpl.h"
#include "atlas/generator/impl/generic/GenericGeneratorImpl.h"
#include "atlas/generator/impl/random/MersenneTwisterNumberGenerator.h"




int main() {
    using namespace atlas;

    auto generator = std::make_unique<generator::MersenneTwisterNumberGenerator>();
    //auto generator = std::make_unique<generator::GenericGeneratorImpl>(0, [](int value) { return value + 5; });
    auto factory = std::make_unique<container::VectorFactorySequentialImpl<int>>(std::move(generator));
    client::VectorClientImpl client{std::move(factory)};

    client.processVector();
    return 0;
}
