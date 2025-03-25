#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <Core/barkeep.hpp>
#include <thread_pool/BS_thread_pool.hpp>
#include <thread_pool/BS_thread_pool_utils.hpp>

template <typename T>
auto format_string(const T a, int precision = 2) -> std::string {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << a;
    return stream.str();
}

template <class Reader>
auto multithread_reader(Reader& reader, const std::vector<std::string>& files, const int cores = 6) -> void {
    namespace bk = barkeep;
    BS::thread_pool pool(cores);
    for (auto& file : files)
        pool.detach_task([&reader, &file] { reader(file); });

    int total = pool.get_tasks_total();
    int progress = 0;

    auto bar = bk::ProgressBar(&progress, {.total = total});
    while (true) {
        pool.wait_for(std::chrono::seconds(1));
        progress = (total - static_cast<double>(pool.get_tasks_total()));
        if (pool.get_tasks_total() == 0) break;
    }

    pool.wait();

}