#include <iostream>
#include <memory>
#include "client/Client.h"
#include "math/CalculatorBuilder.h"


int main() {

    std::unique_ptr<math::Calculator> calculator = math::CalculatorBuilder()
        .withLogger()
        .withSecure()
        .build();


    client::Client client_{std::move(calculator)};

    client_.go();
    return 0;
}
