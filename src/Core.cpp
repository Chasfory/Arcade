/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Core
*/

#include "Core.hpp"
#include <chrono>
#include <thread>

arcade::Core::Core(const std::string &initialLib) : gameIndex(0), displayIndex(0)
{
    this->parse(initialLib);
    this->display.load(initialLib);
    this->game.load(this->availableGames[this->gameIndex]);

    //if (!this->menu())
    //    return;

    while (true) {
        auto input = this->display.get()->getInput();

        switch (*input) {
            case common::Input::NEXT_GAME:
                this->nextGame();
                break;
            case common::Input::NEXT_LIBRARY:
                this->nextDisplay();
                break;
            case common::Input::RESTART:
                break;
            case common::Input::EXIT:
                return;
                //case common::Input::BACK_MENU:
                //    if (!this->menu())
                //        return;
            case common::Input::UP:
            case common::Input::DOWN:
            case common::Input::RIGHT:
            case common::Input::LEFT:
            case common::Input::ACTION_1:
            case common::Input::ACTION_2:
            case common::Input::SPECIAL_1:
            case common::Input::SPECIAL_2:
                this->game.get()->handleInput(*input);
                break;
            default:
                // TODO: pass window dimensions
                auto data = this->game.get()->tick();
                this->display.get()->display(data);
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

bool arcade::Core::menu() noexcept
{
    while (true) {
        auto input = this->display.get()->getInput();

        switch (*input) {
            // TODO: handle other cases
            case common::Input::EXIT:
                return false;
            case common::Input::RESTART:
                // TODO: tmp for CLion, to remove
                return true;
            default:
                // TODO: pass window dimensions
                // auto data = this->game.get()->tick(TODO);
                // this->display.get()->display(data, TODO);
                break;
        }
    }
}

void arcade::Core::nextDisplay()
{
    this->displayIndex++;
    size_t len = this->availableDisplays.size();

    if (this->displayIndex == len) {
        this->displayIndex = 0;
    }
    this->display.load(this->availableDisplays[this->displayIndex]);
}

void arcade::Core::nextGame()
{
    this->gameIndex++;
    size_t len = this->availableGames.size();

    if (this->gameIndex == len) {
        this->gameIndex = 0;
    }
    this->game.load(this->availableGames[this->gameIndex]);
}
