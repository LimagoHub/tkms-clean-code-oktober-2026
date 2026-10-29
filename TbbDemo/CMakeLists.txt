cmake_minimum_required(VERSION 3.20)
project(tbb_parallel_for LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MinGW-Laufzeit statisch linken (gilt auch fuer die TBB-DLL).
# Voll statisch (-static) klappt nur mit UCRT-MinGW; bei aelteren msvcrt-Toolchains
# (z.B. in CLion gebuendelt) scheitert statisches winpthread -> Fallback.
if(MINGW)
    include(CheckCXXSourceCompiles)
    set(CMAKE_REQUIRED_LINK_OPTIONS -static)
    check_cxx_source_compiles("#include <thread>
        int main() { std::thread t([]{}); t.join(); }" MINGW_FULL_STATIC_OK)
    unset(CMAKE_REQUIRED_LINK_OPTIONS)
    if(MINGW_FULL_STATIC_OK)
        add_link_options(-static)
    else()
        message(WARNING "Voll statisches Linken nicht moeglich; libwinpthread-1.dll muss mitgeliefert werden")
        add_link_options(-static-libstdc++ -static-libgcc)
    endif()
endif()

# oneTBB liegt als Quellcode im Projekt (kein Download noetig, Firewall-tauglich)
set(TBB_TEST OFF CACHE BOOL "" FORCE)
set(TBB_STRICT OFF CACHE BOOL "" FORCE)
set(TBB_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/oneTBB EXCLUDE_FROM_ALL)

add_executable(parallel_sum src/main.cpp)
target_link_libraries(parallel_sum PRIVATE TBB::tbb)

# TBB-DLL neben die exe kopieren, damit sie unter Windows startet
add_custom_command(TARGET parallel_sum POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:TBB::tbb> $<TARGET_FILE_DIR:parallel_sum>
)
