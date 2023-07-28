/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Core
*/

#pragma once

#include "common/game/IGameModule.hpp"
#include "common/display/IDisplayModule.hpp"
#include "DynamicLib.hpp"

namespace arcade {
    class Core {
        public:
            explicit Core(const std::string &initialLib);
        private:
            void parse(const std::string &initialLib);
            bool menu() noexcept;

            void nextDisplay();
            void nextGame();

            DynamicLib<arcade::common::IGameModule> game;
            DynamicLib<arcade::common::IDisplayModule> display;
            size_t gameIndex;
            size_t displayIndex;

            std::vector<std::string> availableGames;
            std::vector<std::string> availableDisplays;
    };
}
