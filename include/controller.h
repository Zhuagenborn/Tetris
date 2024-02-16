/**
 * @file controller.h
 * @brief The game controller and user interface.
 *
 * @author Chen Zhenshuo (chenzs108@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-29
 */

#pragma once

#include "game.h"

#include <memory>


class Controller {
public:
    class Initializer {
    public:
        //! Initialize a controller environment.
        Initializer() noexcept;

        //! Release the controller environment.
        ~Initializer() noexcept;
    };

    Controller(std::unique_ptr<Game>) noexcept;

    //! Get a user's input.
    void Input() noexcept;

    //! Update the game.
    void Update() noexcept;

    //! Refresh graphics.
    void Refresh() noexcept;

    bool IsOver() const noexcept;

    ~Controller() noexcept;

private:
    class Impl;

    std::unique_ptr<Impl> impl_;
};