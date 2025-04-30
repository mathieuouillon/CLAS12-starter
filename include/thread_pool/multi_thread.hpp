#pragma once

// C++ headers
#include <chrono>
#include <string>
#include <vector>

// <fmt> headers
#include <fmt/core.h>
#include <fmt/format.h>

// Project headers
#include <Core/barkeep.hpp>
#include <thread_pool/BS_thread_pool.hpp>
#include <thread_pool/BS_thread_pool_utils.hpp>

/**
 * @brief Format a value to a string with specified precision
 * @tparam T Type of the value to format
 * @param value The value to format
 * @param precision Number of decimal places (default: 2)
 * @return Formatted string
 */
template <typename T>
std::string format_string(const T& value, int precision = 2) {
    return fmt::format("{:.{}f}", value, precision);
}

/**
 * @brief Process multiple files in parallel using a reader function
 * @tparam Reader Type of the reader function
 * @param reader Function to read/process a single file
 * @param files Vector of file paths to process
 * @param num_threads Number of threads to use (default: 6)
 * @param update_interval Progress update interval in milliseconds (default: 1000ms)
 */
template <typename Reader>
void multithread_reader(
    const Reader& reader,
    const std::vector<std::string>& files,
    unsigned int num_threads = 6,
    unsigned int update_interval = 1000) {
    namespace bk = barkeep;

    num_threads = std::max(1u, num_threads); // Ensure at least one thread
    BS::thread_pool pool(num_threads); // Create thread pool with specified number of threads

    // Queue all files for processing
    for (const auto& file : files) {
        pool.detach_task([&reader, file] {
            try {
                reader(file);
            } catch (const std::exception& e) {
                fmt::print(stderr, "Error processing file '{}': {}\n", file, e.what());
            }
        });
    }

    const int total_tasks = pool.get_tasks_total();
    int completed_tasks = 0;

    auto bar = bk::ProgressBar(&completed_tasks, {.total = total_tasks});    // Create progress bar

    while (pool.get_tasks_total() > 0) {
        pool.wait_for(std::chrono::milliseconds(update_interval));
        completed_tasks = total_tasks - pool.get_tasks_total();
    }

    pool.wait(); // Ensure all tasks are completed
}