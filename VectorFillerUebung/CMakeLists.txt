cmake_minimum_required(VERSION 4.3)
project(VectorFillerUebung)

set(CMAKE_CXX_STANDARD 17)

add_executable(VectorFillerUebung main.cpp
        atlas/generator/IGenerator.h
        atlas/generator/IIntGenerator.h
        atlas/time/IStopwatch.h
        atlas/client/IClient.h
        atlas/client/impl/ClientImpl.h
        atlas/time/impl/StopwatchImpl.h
        atlas/generator/impl/random/MersenneTwisterNumberGenerator.h
        atlas/generator/impl/generic/GenericGeneratorImpl.h
        atlas/container/impl/decorator/VectorFactoryBenchmarkDecorator.h
        atlas/container/impl/builder/VectorFactoryBuilder.h
        atlas/container/impl/builder/VectorFactoryBuilder.h
        atlas/container/impl/parallel/VectorFactoryAutoImpl.h
        atlas/threadpool/thread_pool.hpp
        atlas/container/impl/parallel/VectorFactoryThreadpoolImpl.h
        atlas/container/impl/parallel/VectorFactoryThreadpoolLoopImpl.h)
