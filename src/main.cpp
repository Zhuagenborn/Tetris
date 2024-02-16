/**
 * @file main.cpp
 * @brief The game loop.
 *
 * @author Chen Zhenshuo (chenzs108@outlook.com)
 * @author Liu Guowen (liu.guowen@outlook.com)
 * @par GitHub
 * https://github.com/Zhuagenborn
 * @version 1.0
 * @date 2023-04-29
 */

#include "args.h"
#include "controller.h"
#include "game.h"

#include <algorithm>


int main(int, char* argv[]) {
    try {
        const Controller::Initializer gui_initer;

        CmdArgs args;
        args.Parse(argv);

        constexpr std::size_t min_width {10}, min_height {15};
        const auto width {std::max(args.GetWidth(), min_width)};
        const auto height {std::max(args.GetHeight(), min_height)};

        GameSettings settings;
        settings.SetDescendTime(std::chrono::seconds {1});
        auto game {std::make_unique<Game>(std::make_unique<Grid>(width, height),
                                          std::move(settings))};
        game->Start();
        Controller controller {std::move(game)};
        while (!controller.IsOver()) {
            controller.Input();
            controller.Update();
            controller.Refresh();
        }

        return EXIT_SUCCESS;
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    }
}