/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-reza.rahemtola
** File description:
** Nibbler
*/

#include <algorithm>
#include "Nibbler.hpp"

static const size_t MOVING_SPEED = 1;
static const size_t MAP_X = 60;
static const size_t MAP_Y = 40;

namespace arcade {

    extern "C" Nibbler *gameEntrypoint()
    {
        return new Nibbler;
    }

    Nibbler::Nibbler()
            : AGameModule(), direction(arcade::common::Input::RIGHT),
              count(0), maxFruit(8)
    {
        float y = 0;
        float x = 0;
        std::string tmp = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
                          "xo                                                        ox\n"
                          "x xxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxx x\n"
                          "x x     x  x        o                              x     x x\n"
                          "x x     x  x xxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxx xxx x     x x\n"
                          "x x     x  x x     x x                xxxxxxxx x x x     x x\n"
                          "x xxxxxxx    x     x x                x        x x xxxxxxx x\n"
                          "x         xxxxxxxxxx xxxxxxxxxxxxxxxxxx xxxxxxxxxx         x\n"
                          "x xxxxxxx x   x   o   xx                xx   o     xxxxxxx x\n"
                          "x x     x x   x xxxxx xx xxxxxxxxxxxxxx xx xxxxxxx x     x x\n"
                          "x x     x x   x x   x xx x            x xx x     x x     x x\n"
                          "x x     x x   x x   x xx x            x xx x     x x     x x\n"
                          "x xxxxxxx xxxxx xxxxx xx xxxxxxxxxxxxxx xx xxxxxxx xxxxxxx x\n"
                          "x                                                          x\n"
                          "x xxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxx x\n"
                          "x x     x  x                  o                    x     x x\n"
                          "x x     x  x xxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxx xxx x     x x\n"
                          "x x     x  x x     x x                xxxxxxxx x x x     x x\n"
                          "x xxxxxxx    x     x x                x        x x xxxxxxx x\n"
                          "x         xxxxxxxxxx xxxxxxxxxxxxxxxxxx xxxxxxxxxx         x\n"
                          "x xxxxxxx x   x   o   xx                xx         xxxxxxx x\n"
                          "x x     x x   x xxxxx xx xxxxxxxxxxxxxx xx xxxxxxx x     x x\n"
                          "x x     x x   x x   x xx x            x xx x     x x     x x\n"
                          "x x     x x   x x   x xx x            x xx x     x x     x x\n"
                          "x xxxxxxx xxxxx xxxxx xx xxxxxxxxxxxxxx xx xxxxxxx xxxxxxx x\n"
                          "x                                            o             x\n"
                          "x xxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxx x\n"
                          "x x     x  x        o                              x     x x\n"
                          "x x     x  x xxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxx xxx x     x x\n"
                          "x x     x  x x     x x                xxxxxxxx x x x     x x\n"
                          "x xxxxxxx    x     x x                x      o x x xxxxxxx x\n"
                          "x    o    xxxxxxxxxx xxxxxxxxxxxxxxxxxx xxxxxxxxxx         x\n"
                          "x xxxxxxx xxxxx       xx                xx         xxxxxxx x\n"
                          "x x     x x   x xxxxx xx xxxxxxxxxxxxxx xx xxxxxxx x     x x\n"
                          "x x     x x   x x   x xx x            x xx x     x x     x x\n"
                          "x x     x x   x x   x xxox            x xx x     x x     x x\n"
                          "x x     x x   x x   x xx x            x xx x     x x     x x\n"
                          "x xxxxxxx xxxxx xxxxx xx xxxxxxxxxxxxxx xx xxxxxxx xxxxxxx x\n"
                          "xaaaa                                                     ox\n"
                          "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

        for (float i = 0; tmp[i] != '\0'; i++) {
            if (tmp[i] == '\n') {
                x = 0;
                y++;
            } else if (tmp[i] == 'x') {
                this->walls.push_back({{x, y}, common::SpriteType::WALL});
                x++;
            } else if (tmp[i] == 'o') {
                this->fruit.push_back({{x, y}, common::SpriteType::BONUS_A});
                this->maxFruit++;
                x++;
            } else if (tmp[i] == 'a') {
                this->player.insert(this->player.begin(), {{x, y}, common::SpriteType::BODY});
                x++;
            } else {
                x++;
            }
        }
    }

    void Nibbler::handleInput(arcade::common::Input in)
    {
        switch (in) {
            case common::Input::UP:
            case common::Input::DOWN:
            case common::Input::LEFT:
            case common::Input::RIGHT:
                if (!this->canMove(in) || (in == common::Input::UP && this->direction == common::Input::DOWN) ||
                    (in == common::Input::DOWN && this->direction == common::Input::UP) ||
                    (in == common::Input::LEFT && this->direction == common::Input::RIGHT) ||
                    (in == common::Input::RIGHT && this->direction == arcade::common::Input::LEFT)) {
                    return;
                }
                this->direction = in;
                break;
            default:
                // TODO: handle other inputs (reset, back to menu...)
                break;
        }
    }

    bool Nibbler::postSnake()
    {
        float pos_head_x = this->player.front().position.x;
        float pos_head_y = this->player.front().position.y;

        for (float i = 1; i < this->player.size(); i++) {
            if (this->player[i].position.x == pos_head_x &&
                this->player[i].position.y == pos_head_y) {
                return true;
            }
        }
        return false;
    }

    bool Nibbler::canMove(common::Input wantedDirection)
    {
        float x = this->player.front().position.x;
        float y = this->player.front().position.y;
        common::Position front{};
        common::Position left{};
        common::Position right{};

        switch (wantedDirection) {
            case common::Input::UP:
                front = {x, y - 1};
                left = {x - 1, y};
                right = {x + 1, y};
                break;
            case common::Input::DOWN:
                front = {x, y + 1};
                left = {x + 1, y};
                right = {x - 1, y};
                break;
            case common::Input::LEFT:
                front = {x - 1, y};
                left = {x, y + 1};
                right = {x, y - 1};
                break;
            case common::Input::RIGHT:
                front = {x + 1, y};
                left = {x, y - 1};
                right = {x, y + 1};
                break;
            default:
                front = {0, 0};
                break;
        }

        auto front_it = std::find_if(this->walls.begin(), this->walls.end(),
                                     [&front](const arcade::common::Sprite &sprite) {
                                         return (sprite.position.x) == front.x && (sprite.position.y) == (front.y);
                                     });
        auto left_it = std::find_if(this->walls.begin(), this->walls.end(),
                                    [&left](const arcade::common::Sprite &sprite) {
                                        return (sprite.position.x) == left.x && (sprite.position.y) == (left.y);
                                    });
        auto right_it = std::find_if(this->walls.begin(), this->walls.end(),
                                     [&right](const arcade::common::Sprite &sprite) {
                                         return (sprite.position.x) == right.x && (sprite.position.y) == (right.y);
                                     });

        if (this->direction != wantedDirection) {
            // call from handleInput
            return front_it == this->walls.end();
        }
        if (front_it == this->walls.end()) {
            return true; // no wall in front, we can move
        }
        if (left_it != this->walls.end() && right_it == this->walls.end()) {
            switch (this->direction) {
                case common::Input::UP:
                    this->direction = common::Input::RIGHT;
                    break;
                case common::Input::DOWN:
                    this->direction = common::Input::LEFT;
                    break;
                case common::Input::LEFT:
                    this->direction = common::Input::UP;
                    break;
                case common::Input::RIGHT:
                    this->direction = common::Input::DOWN;
                    break;
                default:
                    break;
            }
            return true;
        } else if (left_it == this->walls.end() && right_it != this->walls.end()) {
            switch (this->direction) {
                case common::Input::UP:
                    this->direction = common::Input::LEFT;
                    break;
                case common::Input::DOWN:
                    this->direction = common::Input::LEFT;
                    break;
                case common::Input::LEFT:
                    this->direction = common::Input::DOWN;
                    break;
                case common::Input::RIGHT:
                    this->direction = common::Input::UP;
                    break;
                default:
                    break;
            }
            return true;
        }
        return false;
    }

    bool Nibbler::postFruit()
    {
        float pos_head_x = this->player.front().position.x;
        float pos_head_y = this->player.front().position.y;

        for (auto &sprite: this->fruit) {
            if (sprite.position.x == pos_head_x && sprite.position.y == pos_head_y) {
                sprite.position.x = -1;
                sprite.position.y = -1;
                count++;
            }
        }
        return (this->count == this->maxFruit);
    }

    void Nibbler::increaseBody(common::Position pos)
    {
        arcade::common::Sprite body = {pos, common::SpriteType::BODY};

        this->player.push_back(body);
    }

    void Nibbler::move()
    {
        const float MOVEMENT = MOVING_SPEED;
        common::Position old = this->player[0].position;
        common::Position current{};
        int tmp_count = this->count;

        if (this->canMove(this->direction)) {
            for (float i = 1; i < this->player.size(); i++) {
                current = this->player[i].position;
                this->player[i].position = old;
                old = current;
            }
            switch (this->direction) {
                case arcade::common::Input::UP:
                    this->player[0].position.y -= MOVEMENT;
                    break;
                case arcade::common::Input::DOWN:
                    this->player[0].position.y += MOVEMENT;
                    break;
                case arcade::common::Input::LEFT:
                    this->player[0].position.x -= MOVEMENT;
                    break;
                case arcade::common::Input::RIGHT:
                    this->player[0].position.x += MOVEMENT;
                    break;
                default:
                    break;
            }
        }

        if (this->postSnake()) {
            this->isGameOver();
            //this->setupSound("GameOver");
            return;
        }
        if (this->postFruit()) {
            //this->setupSound("Win");
            this->win = true;
        }
        if (tmp_count != this->count) {
            this->increaseBody(old);
        }
    }

    common::Data &Nibbler::tick()
    {
        this->move();
        data.sprites.clear();
        data.score = this->score;
        if (this->gameOver) {
            data.texts.push_back({{MAP_X / 2, MAP_Y / 2}, "GameOver", 30});
        } else if (this->win) {
            data.texts.push_back({{MAP_X / 2, MAP_Y / 2}, "Win", 30});
        } else {
            for (auto sprite: this->player) {
                data.sprites.push_back(sprite);
            }
            for (auto sprite: this->fruit) {
                data.sprites.push_back(sprite);
            }
            for (auto sprite: this->walls) {
                data.sprites.push_back(sprite);
            }
        }
        data.mapHeight = MAP_Y;
        data.mapWith = MAP_X;
        return data;
    }
}
