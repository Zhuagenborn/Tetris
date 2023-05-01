/**
 * @file args.h
 * @brief A command line argument handler.
 *
 * @author Zhenshuo Chen (chenzs108@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-05-01
 */

#pragma once

#include <memory>

/**
 * @brief A command line argument handler.
 *
 * @details
 * The arguments are:
 *
 * ```bash
 * -x=<width>
 * -y=<height>
 * ```
 */
class CmdArgs {
public:
    CmdArgs() noexcept;

    void Parse(const char* const* argv) noexcept;

    std::size_t GetWidth() const noexcept;

    std::size_t GetHeight() const noexcept;

    ~CmdArgs() noexcept;

private:
    class Impl;

    std::unique_ptr<Impl> impl_;
};