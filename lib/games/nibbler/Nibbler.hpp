/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-reza.rahemtola
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include <map>
#include "../AGameModule.hpp"

namespace arcade {
    class Nibbler : public AGameModule {
        public:
            Nibbler();

            void handleInput(common::Input in) override;
            common::Data &tick() override;

        private:
            bool canMove(common::Input wantedDirection);
            bool postSnake();
            bool postFruit();
            void increaseBody(common::Position pos);
            void move();

            std::vector<arcade::common::Sprite> fruit;
            std::vector<arcade::common::Sprite> walls;
            arcade::common::Input direction;
            common::Data data;
            bool win = false;
            int count = 0;
            int maxFruit;
            std::string map;
    };

    extern "C" Nibbler *gameEntrypoint();
}

#endif /* !NIBBLER_HPP_ */
