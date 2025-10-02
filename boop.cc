#include "boop.h"
#include "game.h"
#include "space.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <cctype>

namespace main_savitch_14
{

    boop::boop()
    {
        // Initialize the board
        for (int i = 0; i < 6; ++i)
        {
            for (size_t j = 0; j < 6; j++)
            {
                board[i][j].setEmpty();
            }
        }

        rp = bp = 8;

        rd = bd = 0;

        current_player = 1;
    }

    boop::~boop() {}

    // game::who boop::play()
    // {
    //     restart();
    //     while (!boop::is_game_over())
    //     {
    //         display_status();
    //         string move = get_user_move();
    //         make_move(move);
    //     }

    //     display_status();
    //     if (current_player % 2 == 1)
    //     {
    //         return game::HUMAN;
    //     }
    //     else if (current_player % 2 == 0)
    //     {
    //         return game::COMPUTER;
    //     }
    // }

    std::string boop::get_user_move() const
    {
        std::string move;

        if (move_type == 0)
        {
            std::cout << "Enter your move (Format: *P/D* *Row* *Column*): ";
            std::getline(std::cin, move);
            return move;
        }
        else if (move_type == 1)
        {
            std::cout << "You have at least one row of three available, enter the center space of the one you wish to remove and the direction of the row (eg. 'A3H' for center space at A3, horizontal line): ";
            std::getline(std::cin, move);
            return move;
        }
        else if (move_type == 2)
        {
            std::cout << "You have no remaining pieces to play, pick one of your placed pieces to pick up (*row* *column*): ";
            std::getline(std::cin, move);
            return move;
        }
        return move;
    }

    void boop::make_move(const std::string &move)
    {

        // Check if the move is legal
        // if (!is_legal(move))
        // {
        //     std::cout << "Illegal move" << std::endl;
        //     return;
        // }

        // Update the board based on the move
        std::string input = get_location(move);

        char type;
        int a;
        int b;

        if (move_type == 0)
        {
            // Extract the row and column from the input
            type = move.at(0);
            a = input.at(1) - '0';
            b = input.at(2) - '0';

            // checks what move the user is making
            if (tolower(type) == 'p')
            {
                // makes the move depending on which player it is
                if (current_player % 2 == 0)
                {
                    board[a][b].setBP();
                    bp--;
                    boop_pieces(move);

                    if (check_for_3())
                    {
                        move_type = 1;
                        return;
                    }

                    if (bp + bd == 0)
                    {
                        move_type = 2;
                        return;
                    }

                    current_player++;
                    game::make_move(move);
                    return;
                }
                else if (current_player % 2 == 1)
                {
                    board[a][b].setRP();
                    rp--;
                    boop_pieces(move);

                    if (check_for_3())
                    {
                        move_type = 1;
                        return;
                    }

                    if (rp + rd == 0)
                    {
                        move_type = 2;
                        return;
                    }

                    current_player++;
                    game::make_move(move);
                    return;
                }
            }

            // makes the move depending on which player it is
            else if (tolower(type) == 'd')
            {
                if (current_player % 2 == 0)
                {
                    board[a][b].setBD();
                    bd--;
                    boop_pieces(move);

                    if (check_for_3())
                    {
                        move_type = 1;
                        return;
                    }

                    if (bp + bd == 0)
                    {
                        move_type = 2;
                        return;
                    }

                    current_player++;
                    game::make_move(move);
                    return;
                }
                else if (current_player % 2 != 0)
                {
                    board[a][b].setRD();
                    rd--;
                    boop_pieces(move);

                    if (check_for_3())
                    {
                        move_type = 1;
                        return;
                    }
                    if (rp + rd == 0)
                    {
                        move_type = 2;
                        return;
                    }

                    current_player++;
                    game::make_move(move);
                    return;
                }
            }
        }
        if (move_type == 1)
        {
            type = move.at(2);
            a = input.at(0) - '0';
            b = input.at(1) - '0';

            if (current_player % 2 == 1) // player 1, RED
            {
                if (type == 'h' || type == 'H')
                {
                    board[a][b].setEmpty();
                    board[a][b - 1].setEmpty();
                    board[a][b + 1].setEmpty();

                    rd += 3;

                    move_type = 0;
                    current_player++;

                    game::make_move(move);
                    return;
                }
                if (type == 'v' || type == 'V')
                {
                    board[a][b].setEmpty();
                    board[a - 1][b].setEmpty();
                    board[a + 1][b].setEmpty();

                    rd += 3;

                    move_type = 0;
                    current_player++;

                    game::make_move(move);
                    return;
                }
                if (type == 'd' || type == 'D')
                {
                    if (board[a - 1][b - 1].getStatus().at(0) == 'R' && board[a + 1][b + 1].getStatus().at(0) == 'R')
                    {
                        board[a][b].setEmpty();
                        board[a - 1][b - 1].setEmpty();
                        board[a + 1][b + 1].setEmpty();

                        rd += 3;

                        move_type = 0;
                        current_player++;

                        game::make_move(move);
                        return;
                    }
                    else if (board[a - 1][b + 1].getStatus().at(0) == 'R' && board[a + 1][b - 1].getStatus().at(0) == 'R')
                    {
                        board[a][b].setEmpty();
                        board[a - 1][b + 1].setEmpty();
                        board[a + 1][b - 1].setEmpty();

                        rd += 3;

                        move_type = 0;
                        current_player++;

                        game::make_move(move);

                        return;
                    }
                }
            }
            if (current_player % 2 == 0) // player 1, RED
            {
                if (type == 'h' || type == 'H')
                {
                    board[a][b].setEmpty();
                    board[a][b - 1].setEmpty();
                    board[a][b + 1].setEmpty();

                    bd += 3;

                    move_type = 0;
                    current_player++;

                    game::make_move(move);
                    return;
                }
                if (type == 'v' || type == 'V')
                {
                    board[a][b].setEmpty();
                    board[a - 1][b].setEmpty();
                    board[a + 1][b].setEmpty();

                    bd += 3;

                    move_type = 0;
                    current_player++;

                    game::make_move(move);
                    return;
                }
                if (type == 'd' || type == 'D')
                {
                    if (board[a - 1][b - 1].getStatus().at(0) == 'B' && board[a + 1][b + 1].getStatus().at(0) == 'B')
                    {
                        board[a][b].setEmpty();
                        board[a - 1][b - 1].setEmpty();
                        board[a + 1][b + 1].setEmpty();

                        bd += 3;

                        move_type = 0;
                        current_player++;

                        game::make_move(move);
                        return;
                    }
                    else if (board[a - 1][b + 1].getStatus().at(0) == 'B' && board[a + 1][b - 1].getStatus().at(0) == 'B')
                    {
                        board[a][b].setEmpty();
                        board[a - 1][b + 1].setEmpty();
                        board[a - 1][b + 1].setEmpty();

                        bd += 3;

                        move_type = 0;
                        current_player++;

                        game::make_move(move);
                        return;
                    }
                }
            }
        }
        if (move_type == 2)
        {
            a = input.at(0) - '0';
            b = input.at(1) - '0';

            if (a < 0 || a >= 6 || b < 0 || b >= 6) {
                std::cerr << "ERROR: Attempting to access board[" << a << "][" << b << "] which is out of bounds!" << std::endl;
                return;
            }            

            if (current_player % 2 == 1)
            {
                if (board[a][b].isRP())
                {
                    board[a][b].setEmpty();
                    rp++;

                    move_type = 0;
                    current_player++;

                    game::make_move(move);
                    return;
                }
                if (board[a][b].isRD())
                {
                    board[a][b].setEmpty();
                    rd++;

                    move_type = 0;
                    current_player++;

                    game::make_move(move);
                    return;
                }
            }
            if (current_player % 2 == 0)
            {
                if (board[a][b].isBP())
                {
                    board[a][b].setEmpty();
                    bp++;

                    move_type = 0;
                    current_player++;

                    game::make_move(move);
                    return;
                }
                if (board[a][b].isBD())
                {
                    board[a][b].setEmpty();
                    bd++;

                    move_type = 0;
                    current_player++;

                    game::make_move(move);
                    return;
                }
            }
        }
    }

    void boop::boop_pieces(const std::string &move)
    {
        if (move_type != 0)
        {
            return;
        }

        std::string input = get_location(move);

        char type = input.at(0);
        int row = input.at(1) - '0';
        int column = input.at(2) - '0';

        if (!(row - 1 < 0))
        {
            if (board[row - 1][column].isEmpty() != true)
            {
                if (row - 2 < 0)
                {
                    if (type == 'p' || type == 'P')
                    {
                        if (board[row - 1][column].getStatus() == "RP")
                        {
                            board[row - 1][column].setEmpty();
                            rp++;
                        }
                        else if (board[row - 1][column].getStatus() == "BP")
                        {
                            board[row - 1][column].setEmpty();
                            bp++;
                        }
                    }
                    else if (type == 'd' || type == 'D')
                    {
                        if (board[row - 1][column].getStatus() == "RP")
                        {
                            board[row - 1][column].setEmpty();
                            rp++;
                        }
                        else if (board[row - 1][column].getStatus() == "BP")
                        {
                            board[row - 1][column].setEmpty();
                            bp++;
                        }
                        else if (board[row - 1][column].getStatus() == "RD")
                        {
                            board[row - 1][column].setEmpty();
                            rd++;
                        }
                        else if (board[row - 1][column].getStatus() == "BD")
                        {
                            board[row - 1][column].setEmpty();
                            bd++;
                        }
                    }
                }
                else if (type == 'p' || type == 'P')
                {
                    if (board[row - 1][column].getStatus() == "RP" || board[row - 1][column].getStatus() == "BP")
                    {
                        if (board[row - 2][column].isEmpty() == true)
                        {
                            board[row - 2][column] = board[row - 1][column];
                            board[row - 1][column].setEmpty();
                        }
                    }
                }
                else if (type == 'd' || type == 'D')
                {
                    if (board[row - 2][column].isEmpty() == true)
                    {
                        board[row - 2][column] = board[row - 1][column];
                        board[row - 1][column].setEmpty();
                    }
                }
            }
        }
        if (!(row - 1 < 0) && !(column + 1 > 5))
        {
            if (board[row - 1][column + 1].isEmpty() != true)
            {
                if (row - 2 < 0 || column + 2 > 5)
                {
                    if (type == 'p' || type == 'P')
                    {
                        if (board[row - 1][column + 1].getStatus() == "RP")
                        {
                            board[row - 1][column + 1].setEmpty();
                            rp++;
                        }
                        else if (board[row - 1][column + 1].getStatus() == "BP")
                        {
                            board[row - 1][column + 1].setEmpty();
                            bp++;
                        }
                    }
                    else if (type == 'd' || type == 'D')
                    {
                        if (board[row - 1][column + 1].getStatus() == "RP")
                        {
                            board[row - 1][column + 1].setEmpty();
                            rp++;
                        }
                        else if (board[row - 1][column + 1].getStatus() == "BP")
                        {
                            board[row - 1][column + 1].setEmpty();
                            bp++;
                        }
                        else if (board[row - 1][column + 1].getStatus() == "RD")
                        {
                            board[row - 1][column + 1].setEmpty();
                            rd++;
                        }
                        else if (board[row - 1][column + 1].getStatus() == "BD")
                        {
                            board[row - 1][column + 1].setEmpty();
                            bd++;
                        }
                    }
                }
                else if (type == 'p' || type == 'P')
                {
                    if (board[row - 1][column + 1].getStatus() == "RP" || board[row - 1][column + 1].getStatus() == "BP")
                    {
                        if (board[row - 2][column + 2].isEmpty() == true)
                        {
                            board[row - 2][column + 2] = board[row - 1][column + 1];
                            board[row - 1][column + 1].setEmpty();
                        }
                    }
                }
                else if (type == 'd' || type == 'D')
                {
                    if (board[row - 2][column + 2].isEmpty() == true)
                    {
                        board[row - 2][column + 2] = board[row - 1][column + 1];
                        board[row - 1][column + 1].setEmpty();
                    }
                }
            }
        }
        if (!(column + 1 > 5))
        {
            if (board[row][column + 1].isEmpty() != true)
            {
                if (row < 0 || column + 2 > 5)
                {
                    if (type == 'p' || type == 'P')
                    {
                        if (board[row][column + 1].getStatus() == "RP")
                        {
                            board[row][column + 1].setEmpty();
                            rp++;
                        }
                        else if (board[row][column + 1].getStatus() == "BP")
                        {
                            board[row][column + 1].setEmpty();
                            bp++;
                        }
                    }
                    else if (type == 'd' || type == 'D')
                    {
                        if (board[row][column + 1].getStatus() == "RP")
                        {
                            board[row][column + 1].setEmpty();
                            rp++;
                        }
                        else if (board[row][column + 1].getStatus() == "BP")
                        {
                            board[row][column + 1].setEmpty();
                            bp++;
                        }
                        else if (board[row][column + 1].getStatus() == "RD")
                        {
                            board[row][column + 1].setEmpty();
                            rd++;
                        }
                        else if (board[row][column + 1].getStatus() == "BD")
                        {
                            board[row][column + 1].setEmpty();
                            bd++;
                        }
                    }
                }
                else if (type == 'p' || type == 'P')
                {
                    if (board[row][column + 1].getStatus() == "RP" || board[row][column + 1].getStatus() == "BP")
                    {
                        if (board[row][column + 2].isEmpty() == true)
                        {
                            board[row][column + 2] = board[row][column + 1];
                            board[row][column + 1].setEmpty();
                        }
                    }
                }
                else if (type == 'd' || type == 'D')
                {
                    if (board[row][column + 2].isEmpty() == true)
                    {
                        board[row][column + 2] = board[row][column + 1];
                        board[row][column + 1].setEmpty();
                    }
                }
            }
        }
        if (!(column + 1 > 5) && !(row + 1 < 0))
        {
            if (board[row + 1][column + 1].isEmpty() != true)
            {
                if (row + 2 > 5 || column + 2 > 5)
                {
                    if (type == 'p' || type == 'P')
                    {
                        if (board[row + 1][column + 1].getStatus() == "RP")
                        {
                            board[row + 1][column + 1].setEmpty();
                            rp++;
                        }
                        else if (board[row + 1][column + 1].getStatus() == "BP")
                        {
                            board[row + 1][column + 1].setEmpty();
                            bp++;
                        }
                    }
                    else if (type == 'd' || type == 'D')
                    {
                        if (board[row + 1][column + 1].getStatus() == "RP")
                        {
                            board[row + 1][column + 1].setEmpty();
                            rp++;
                        }
                        else if (board[row + 1][column + 1].getStatus() == "BP")
                        {
                            board[row + 1][column + 1].setEmpty();
                            bp++;
                        }
                        else if (board[row + 1][column + 1].getStatus() == "RD")
                        {
                            board[row + 1][column + 1].setEmpty();
                            rd++;
                        }
                        else if (board[row + 1][column + 1].getStatus() == "BD")
                        {
                            board[row + 1][column + 1].setEmpty();
                            bd++;
                        }
                    }
                }
                else if (type == 'p' || type == 'P')
                {
                    if (board[row + 1][column + 1].getStatus() == "RP" || board[row + 1][column + 1].getStatus() == "BP")
                    {
                        if (board[row + 2][column + 2].isEmpty() == true)
                        {
                            board[row + 2][column + 2] = board[row + 1][column + 1];
                            board[row + 1][column + 1].setEmpty();
                        }
                    }
                }
                else if (type == 'd' || type == 'D')
                {
                    if (board[row + 2][column + 2].isEmpty() == true)
                    {
                        board[row + 2][column + 2] = board[row + 1][column + 1];
                        board[row + 1][column + 1].setEmpty();
                    }
                }
            }
        }
        if (!(row + 1 > 5))
        {
            if (board[row + 1][column].isEmpty() != true)
            {
                if (row + 2 > 5)
                {
                    if (type == 'p' || type == 'P')
                    {
                        if (board[row + 1][column].getStatus() == "RP")
                        {
                            board[row + 1][column].setEmpty();
                            rp++;
                        }
                        else if (board[row + 1][column].getStatus() == "BP")
                        {
                            board[row + 1][column].setEmpty();
                            bp++;
                        }
                    }
                    else if (type == 'd' || type == 'D')
                    {
                        if (board[row + 1][column].getStatus() == "RP")
                        {
                            board[row + 1][column].setEmpty();
                            rp++;
                        }
                        else if (board[row + 1][column].getStatus() == "BP")
                        {
                            board[row + 1][column].setEmpty();
                            bp++;
                        }
                        else if (board[row + 1][column].getStatus() == "RD")
                        {
                            board[row + 1][column].setEmpty();
                            rd++;
                        }
                        else if (board[row + 1][column].getStatus() == "BD")
                        {
                            board[row + 1][column].setEmpty();
                            bd++;
                        }
                    }
                }
                else if (type == 'p' || type == 'P')
                {
                    if (board[row + 1][column].getStatus() == "RP" || board[row + 1][column].getStatus() == "BP")
                    {
                        if (board[row + 2][column].isEmpty() == true)
                        {
                            board[row + 2][column] = board[row + 1][column];
                            board[row + 1][column].setEmpty();
                        }
                    }
                }
                else if (type == 'd' || type == 'D')
                {
                    if (board[row + 2][column].isEmpty() == true)
                    {
                        board[row + 2][column] = board[row + 1][column];
                        board[row + 1][column].setEmpty();
                    }
                }
            }
        }
        if (!(row + 1 < 0) && !(column - 1 < 0))
        {
            if (board[row + 1][column - 1].isEmpty() != true)
            {
                if (row + 2 > 5 || column - 2 < 0)
                {
                    if (type == 'p' || type == 'P')
                    {
                        if (board[row + 1][column - 1].getStatus() == "RP")
                        {
                            board[row + 1][column - 1].setEmpty();
                            rp++;
                        }
                        else if (board[row + 1][column - 1].getStatus() == "BP")
                        {
                            board[row + 1][column - 1].setEmpty();
                            bp++;
                        }
                    }
                    else if (type == 'd' || type == 'D')
                    {
                        if (board[row + 1][column - 1].getStatus() == "RP")
                        {
                            board[row + 1][column - 1].setEmpty();
                            rp++;
                        }
                        else if (board[row + 1][column - 1].getStatus() == "BP")
                        {
                            board[row + 1][column - 1].setEmpty();
                            bp++;
                        }
                        else if (board[row + 1][column - 1].getStatus() == "RD")
                        {
                            board[row + 1][column - 1].setEmpty();
                            rd++;
                        }
                        else if (board[row + 1][column - 1].getStatus() == "BD")
                        {
                            board[row + 1][column - 1].setEmpty();
                            bd++;
                        }
                    }
                }
                else if (type == 'p' || type == 'P')
                {
                    if (board[row + 1][column - 1].getStatus() == "RP" || board[row + 1][column - 1].getStatus() == "BP")
                    {
                        if (board[row + 2][column - 2].isEmpty() == true)
                        {
                            board[row + 2][column - 2] = board[row + 1][column - 1];
                            board[row + 1][column - 1].setEmpty();
                        }
                    }
                }
                else if (type == 'd' || type == 'D')
                {
                    if (board[row + 2][column - 2].isEmpty() == true)
                    {
                        board[row + 2][column - 2] = board[row + 1][column - 1];
                        board[row + 1][column - 1].setEmpty();
                    }
                }
            }
        }
        if (!(column - 1 < 0))
        {
            if (board[row][column - 1].isEmpty() != true)
            {
                if (column - 2 < 0)
                {
                    if (type == 'p' || type == 'P')
                    {
                        if (board[row][column - 1].getStatus() == "RP")
                        {
                            board[row][column - 1].setEmpty();
                            rp++;
                        }
                        else if (board[row][column - 1].getStatus() == "BP")
                        {
                            board[row][column - 1].setEmpty();
                            bp++;
                        }
                    }
                    else if (type == 'd' || type == 'D')
                    {
                        if (board[row][column - 1].getStatus() == "RP")
                        {
                            board[row][column - 1].setEmpty();
                            rp++;
                        }
                        else if (board[row][column - 1].getStatus() == "BP")
                        {
                            board[row][column - 1].setEmpty();
                            bp++;
                        }
                        else if (board[row][column - 1].getStatus() == "RD")
                        {
                            board[row][column - 1].setEmpty();
                            rd++;
                        }
                        else if (board[row][column - 1].getStatus() == "BD")
                        {
                            board[row][column - 1].setEmpty();
                            bd++;
                        }
                    }
                }
                else if (type == 'p' || type == 'P')
                {
                    if (board[row][column - 1].getStatus() == "RP" || board[row][column - 1].getStatus() == "BP")
                    {
                        if (board[row][column - 2].isEmpty() == true)
                        {
                            board[row][column - 2] = board[row][column - 1];
                            board[row][column - 1].setEmpty();
                        }
                    }
                }
                else if (type == 'd' || type == 'D')
                {
                    if (board[row][column - 2].isEmpty() == true)
                    {
                        board[row][column - 2] = board[row][column - 1];
                        board[row][column - 1].setEmpty();
                    }
                }
            }
        }
        if (!(column - 1 < 0) && !(row - 1 < 0))
        {
            if (board[row - 1][column - 1].isEmpty() != true)
            {
                if (column - 2 < 0 || row - 2 < 0)
                {
                    if (type == 'p' || type == 'P')
                    {
                        if (board[row - 1][column - 1].getStatus() == "RP")
                        {
                            board[row - 1][column - 1].setEmpty();
                            rp++;
                        }
                        else if (board[row - 1][column - 1].getStatus() == "BP")
                        {
                            board[row - 1][column - 1].setEmpty();
                            bp++;
                        }
                    }
                    else if (type == 'd' || type == 'D')
                    {
                        if (board[row - 1][column - 1].getStatus() == "RP")
                        {
                            board[row - 1][column - 1].setEmpty();
                            rp++;
                        }
                        else if (board[row - 1][column - 1].getStatus() == "BP")
                        {
                            board[row - 1][column - 1].setEmpty();
                            bp++;
                        }
                        else if (board[row - 1][column - 1].getStatus() == "RD")
                        {
                            board[row - 1][column - 1].setEmpty();
                            rd++;
                        }
                        else if (board[row - 1][column - 1].getStatus() == "BD")
                        {
                            board[row - 1][column - 1].setEmpty();
                            bd++;
                        }
                    }
                }
                else if (type == 'p' || type == 'P')
                {
                    if (board[row - 1][column - 1].getStatus() == "RP" || board[row - 1][column - 1].getStatus() == "BP")
                    {
                        if (board[row - 2][column - 2].isEmpty() == true)
                        {
                            board[row - 2][column - 2] = board[row - 1][column - 1];
                            board[row - 1][column - 1].setEmpty();
                        }
                    }
                }
                else if (type == 'd' || type == 'D')
                {
                    if (board[row - 2][column - 2].isEmpty() == true)
                    {
                        board[row - 2][column - 2] = board[row - 1][column - 1];
                        board[row - 1][column - 1].setEmpty();
                    }
                }
            }
        }

        // checks the 8 surrounding spaces around the original, starting from top and goes counter clockwise
    }

    bool boop::check_for_3()
    {
        for (size_t i = 1; i < 5; i++)
        {
            for (size_t j = 1; j < 5; j++)
            {
                if (current_player % 2 == 1) // if player 1, RED
                {
                    if (board[i][j].getStatus().at(0) == 'r' || board[i][j].getStatus().at(0) == 'R')
                    {
                        if ((board[i - 1][j - 1].getStatus().at(0) == 'r' || board[i - 1][j - 1].getStatus().at(0) == 'R') && (board[i + 1][j + 1].getStatus().at(0) == 'r' || board[i + 1][j + 1].getStatus().at(0) == 'R'))
                        {
                            return true;
                        }
                        if ((board[i - 1][j].getStatus().at(0) == 'r' || board[i - 1][j].getStatus().at(0) == 'R') && (board[i + 1][j].getStatus().at(0) == 'r' || board[i + 1][j].getStatus().at(0) == 'R'))
                        {
                            return true;
                        }
                        if ((board[i - 1][j + 1].getStatus().at(0) == 'r' || board[i - 1][j + 1].getStatus().at(0) == 'R') && (board[i + 1][j - 1].getStatus().at(0) == 'r' || board[i + 1][j - 1].getStatus().at(0) == 'R'))
                        {
                            return true;
                        }
                        if ((board[i][j - 1].getStatus().at(0) == 'r' || board[i][j - 1].getStatus().at(0) == 'R') && (board[i][j + 1].getStatus().at(0) == 'r' || board[i][j + 1].getStatus().at(0) == 'R'))
                        {
                            return true;
                        }
                    }
                }
                else if (current_player % 2 == 0) // if player 2, BLUE
                {
                    if (board[i][j].getStatus().at(0) == 'b' || board[i][j].getStatus().at(0) == 'B')
                    {
                        if ((board[i - 1][j - 1].getStatus().at(0) == 'b' || board[i - 1][j - 1].getStatus().at(0) == 'B') && (board[i + 1][j + 1].getStatus().at(0) == 'b' || board[i + 1][j + 1].getStatus().at(0) == 'B'))
                        {
                            return true;
                        }
                        if ((board[i - 1][j].getStatus().at(0) == 'b' || board[i - 1][j - 1].getStatus().at(0) == 'B') && (board[i + 1][j].getStatus().at(0) == 'b' || board[i + 1][j].getStatus().at(0) == 'B'))
                        {
                            return true;
                        }
                        if ((board[i - 1][j + 1].getStatus().at(0) == 'b' || board[i - 1][j + 1].getStatus().at(0) == 'B') && (board[i + 1][j - 1].getStatus().at(0) == 'b' || board[i + 1][j - 1].getStatus().at(0) == 'B'))
                        {
                            return true;
                        }
                        if ((board[i][j - 1].getStatus().at(0) == 'b' || board[i][j - 1].getStatus().at(0) == 'B') && (board[i][j + 1].getStatus().at(0) == 'b' || board[i][j + 1].getStatus().at(0) == 'B'))
                        {
                            return true;
                        }
                    }
                }
            }
        }

        for (size_t i = 1; i < 5; i++)
        {
            if (current_player % 2 == 1)
            {
                if (board[0][i].getStatus().at(0) == 'r' || board[0][i].getStatus().at(0) == 'R')
                {
                    if ((board[0][i - 1].getStatus().at(0) == 'r' || board[0][i - 1].getStatus().at(0) == 'R') && (board[0][i + 1].getStatus().at(0) == 'r' || board[0][i + 1].getStatus().at(0) == 'R'))
                    {
                        return true;
                    }
                }
                if (board[5][i].getStatus().at(0) == 'r' || board[5][i].getStatus().at(0) == 'R')
                {
                    if ((board[5][i - 1].getStatus().at(0) == 'r' || board[5][i - 1].getStatus().at(0) == 'R') && (board[5][i + 1].getStatus().at(0) == 'r' || board[5][i + 1].getStatus().at(0) == 'R'))
                    {
                        return true;
                    }
                }
            }
            if (current_player % 2 == 0)
            {
                if (board[0][i].getStatus().at(0) == 'b' || board[0][i].getStatus().at(0) == 'B')
                {
                    if ((board[0][i - 1].getStatus().at(0) == 'b' || board[0][i - 1].getStatus().at(0) == 'B') && (board[0][i + 1].getStatus().at(0) == 'b' || board[0][i + 1].getStatus().at(0) == 'B'))
                    {
                        return true;
                    }
                }
                if (board[5][i].getStatus().at(0) == 'b' || board[5][i].getStatus().at(0) == 'B')
                {
                    if ((board[5][i - 1].getStatus().at(0) == 'b' || board[5][i - 1].getStatus().at(0) == 'B') && (board[5][i + 1].getStatus().at(0) == 'b' || board[5][i + 1].getStatus().at(0) == 'B'))
                    {
                        return true;
                    }
                }
            }
            if (current_player % 2 == 1)
            {
                if (board[i][0].getStatus().at(0) == 'r' || board[i][0].getStatus().at(0) == 'R')
                {
                    if ((board[i - 1][0].getStatus().at(0) == 'r' || board[i - 1][0].getStatus().at(0) == 'R') && (board[i + 1][0].getStatus().at(0) == 'r' || board[i + 1][0].getStatus().at(0) == 'R'))
                    {
                        return true;
                    }
                }
                if (board[i][5].getStatus().at(0) == 'r' || board[i][5].getStatus().at(0) == 'R')
                {
                    if ((board[i - 1][5].getStatus().at(0) == 'r' || board[i - 1][5].getStatus().at(0) == 'R') && (board[i + 1][5].getStatus().at(0) == 'r' || board[i + 1][5].getStatus().at(0) == 'R'))
                    {
                        return true;
                    }
                }
            }
            if (current_player % 2 == 0)
            {
                if (board[i][0].getStatus().at(0) == 'b' || board[i][0].getStatus().at(0) == 'B')
                {
                    if ((board[i - 1][0].getStatus().at(0) == 'b' || board[i - 1][0].getStatus().at(0) == 'B') && (board[i + 1][0].getStatus().at(0) == 'b' || board[i + 1][0].getStatus().at(0) == 'B'))
                    {
                        return true;
                    }
                }
                if (board[i][5].getStatus().at(0) == 'b' || board[i][5].getStatus().at(0) == 'B')
                {
                    if ((board[i - 1][5].getStatus().at(0) == 'b' || board[i - 1][5].getStatus().at(0) == 'B') && (board[i + 1][5].getStatus().at(0) == 'b' || board[i + 1][5].getStatus().at(0) == 'B'))
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    void boop::restart()
    {
        // resets the board
        for (int i = 0; i < 6; ++i)
        {
            for (int j = 0; j < 6; j++)
            {
                board[i][j].setEmpty();
            }
        }

        // resets the pieces
        rp = bp = 8;
        rd = bd = 0;

        current_player = 1; // if current player is odd, means player 1 RED, if its even, means player 2 BLUE

        move_type = 0;

        game::restart();
    }

    game *boop::clone() const {}

    void boop::compute_moves(std::queue<std::string> &moves) const {}

    void boop::display_status() const
    {
        // all the different pieces of the display to be used
        int line_count = 0;
        std::string horizontal_border = "        -------------------------------------------------------------";
        std::string empty_space = "         |";

        std::string dog_line1 = " /)---(\\ ";
        std::string dog_line2 = "(/ . . \\)";
        std::string dog_line3 = "  \\(*)/  ";

        std::string puppy_line1 = " |\\___/| ";
        std::string puppy_line2 = " | o o | ";
        std::string puppy_line3 = "  \\_^_/  ";

        std::cout << "             1         2         3         4         5         6" << std::endl;
        std::cout << horizontal_border << std::endl;

        for (size_t i = 0; i < 6; i++)
        {
            for (size_t j = 1; j < 4; j++)
            {
                // prints the vertical lines on the very left of the board as well as the letters marking the rows
                if (j != 2)
                {
                    std::cout << "        |";
                }
                else if (j == 2)
                {
                    switch (i)
                    {
                    case 0:
                        std::cout << "     A  |";
                        break;
                    case 1:
                        std::cout << "     B  |";
                        break;
                    case 2:
                        std::cout << "     C  |";
                        break;
                    case 3:
                        std::cout << "     D  |";
                        break;
                    case 4:
                        std::cout << "     E  |";
                        break;
                    case 5:
                        std::cout << "     F  |";
                        break;

                    default:
                        break;
                    }
                }

                // prints the contents of the spaces depending on what is in them
                // if the space is empty, it prints an empty space
                for (size_t t = 0; t < 6; t++)
                {
                    std::string status = board[i][t].getStatus();
                    if (board[i][t].isEmpty())
                    {
                        std::cout << empty_space;
                    }

                    if (board[i][t].isRP())
                    {
                        if (j == 1)
                        {
                            std::cout << RED << puppy_line1 << RESET << "|";
                        }
                        else if (j == 2)
                        {
                            std::cout << RED << puppy_line2 << RESET << "|";
                        }
                        else if (j == 3)
                        {
                            std::cout << RED << puppy_line3 << RESET << "|";
                        }
                    }
                    else if (board[i][t].isRD())
                    {
                        if (j == 1)
                        {
                            std::cout << RED << dog_line1 << RESET << "|";
                        }
                        else if (j == 2)
                        {
                            std::cout << RED << dog_line2 << RESET << "|";
                        }
                        else if (j == 3)
                        {
                            std::cout << RED << dog_line3 << RESET << "|";
                        }
                    }
                    else if (board[i][t].isBP())
                    {
                        if (j == 1)
                        {
                            std::cout << BLUE << puppy_line1 << RESET << "|";
                        }
                        else if (j == 2)
                        {
                            std::cout << BLUE << puppy_line2 << RESET << "|";
                        }
                        else if (j == 3)
                        {
                            std::cout << BLUE << puppy_line3 << RESET << "|";
                        }
                    }
                    else if (board[i][t].isBD())
                    {
                        if (j == 1)
                        {
                            std::cout << BLUE << dog_line1 << RESET << "|";
                        }
                        else if (j == 2)
                        {
                            std::cout << BLUE << dog_line2 << RESET << "|";
                        }
                        else if (j == 3)
                        {
                            std::cout << BLUE << dog_line3 << RESET << "|";
                        }
                    }
                }
                std::cout << std::endl;
                line_count++;
            }
            std::cout << horizontal_border << std::endl;
        }

        std::cout << RED << "          Player 1 Puppies: " << rp << "      Player 1 Dogs: " << rd << RESET << std::endl;
        std::cout << BLUE << "          Player 2 Puppies: " << bp << "      Player 2 Dogs: " << bd << RESET << std::endl;
        std::cout << "Current Player: " << current_player % 2 << std::endl;
    }

    int boop::evaluate() const 
    {
        int rd_count = 0;
        int rp_count = 0;
        int bd_count = 0;
        int bp_count = 0;

        rd_count += rd;
        rp_count += rp;
        bd_count += bd;
        bp_count += bp;

        for (size_t i = 0; i < 6; i++)
        {
            for (size_t j = 0; j < 6; j++)
            {
                if (board[i][j].isRD() == true)
                {
                    rd_count++;
                }
                if (board[i][j].isBD() == true)
                {
                    bd_count++;
                }
                if (board[i][j].isRP() == true)
                {
                    rp_count++;
                }
                if (board[i][j].isBP() == true)
                {
                    bp_count++;
                }
                
            }
            
        }

        int red_score;
        int blue_score;

        red_score = rp_count + (rd_count * 2);
        blue_score = bp_count + (bd_count * 2);

        if (red_score > blue_score)
        {
            return -1;
        }
        else
        return 1;
    }

    bool boop::is_game_over() const

    {
        for (size_t i = 1; i < 5; i++)
        {
            for (size_t j = 1; j < 5; j++)
            {
                if (current_player % 2 == 1) // if player 1, RED
                {
                    if (board[i][j].isRD())
                    {
                        if ((board[i - 1][j - 1].isRD()) && (board[i + 1][j + 1].isRD()))
                        {
                            return true;
                        }
                        if ((board[i][j - 1].isRD()) && (board[i][j + 1].isRD()))
                        {
                            return true;
                        }
                        if ((board[i - 1][j].isRD()) && (board[i + 1][j].isRD()))
                        {
                            return true;
                        }
                        if ((board[i + 1][j - 1].isRD()) && (board[i - 1][j + 1].isRD()))
                        {
                            return true;
                        }
                    }
                }
                else if (current_player % 2 == 0) // if player 2, BLUE
                {
                    if (board[i][j].isBD())
                    {
                        if ((board[i - 1][j - 1].isBD()) && (board[i + 1][j + 1].isBD()))
                        {
                            return true;
                        }
                        if (board[i][j - 1].isBD() && board[i][j + 1].isBD())
                        {
                            return true;
                        }
                        if ((board[i - 1][j].isBD()) && (board[i + 1][j].isBD()))
                        {
                            return true;
                        }
                        if ((board[i + 1][j - 1].isBD()) && (board[i - 1][j + 1].isBD()))
                        {
                            return true;
                        }
                    }
                }
            }
        }

        for (size_t i = 1; i < 5; i++)
        {
            if (current_player % 2 == 1)
            {
                if (board[0][i].isRD())
                {
                    if (board[0][i - 1].isRD() && board[0][i + 1].isRD())
                    {
                        return true;
                    }
                }
                if (board[5][i].isRD())
                {
                    if (board[5][i - 1].isRD() && board[5][i + 1].isRD())
                    {
                        return true;
                    }
                }
            }
            if (current_player % 2 == 0)
            {
                if (board[0][i].isBD())
                {
                    if (board[5][i - 1].isBD() && board[5][i + 1].isBD())
                    {
                        return true;
                    }
                }
                if (board[5][i].isBD())
                {
                    if (board[5][i - 1].isBD() && board[5][i + 1].isBD())
                    {
                        return true;
                    }
                }
            }
            if (current_player % 2 == 1)
            {
                if (board[i][0].isRD())
                {
                    if (board[i - 1][0].isRD() && board[i + 1][0].isRD())
                    {
                        return true;
                    }
                }
                if (board[i][5].isRD())
                {
                    if (board[i - 1][5].isRD() && board[i + 1][5].isRD())
                    {
                        return true;
                    }
                }
            }
            if (current_player % 2 == 0)
            {
                if (board[i][0].isBD())
                {
                    if (board[i - 1][0].isBD() && board[i + 1][0].isBD())
                    {
                        return true;
                    }
                }
                if (board[i][5].isBD())
                {
                    if (board[i - 1][5].isBD() && board[i + 1][5].isBD())
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
   
    bool boop::is_legal(const std::string &move) const
    {
        if (move.length() != 3 && (move_type == 0 || move_type == 1))
        {
            return false;
        }
        else if (move.length() != 2 && move_type == 2)
        {
            return false;
        }
        
        std::string input = get_location(move);

        if (move_type == 0 && move.length() == 3) // logic if move type is placing a new piece
        {
            // check in the inputted move is the correct length
            if (move.length() != 3)
            {
                return false;
            }

            // converts the letter in the move string into the correct row number

            char a = input.at(1);
            char b = input.at(2);
            char c = input.at(0);

            if (c != 'p' && c != 'P' && c != 'd' && c != 'D')
            {
                return false;
            }

            // check if the row and column are valid digits
            if (!std::isdigit(a) || !std::isdigit(b))
            {
                return false;
            }

            int row = a - '0';
            int column = b - '0';

            // check if the row and column are within the bounds of the board
            if (!(row >= 0 && row <= 5) || !(column >= 0 && column <= 5))
            {
                return false;
            }

            // check if the move is using a piece the player has access to
            if (move.at(0) == 'p' || move.at(0) == 'P')
            {
                if (current_player % 2 == 0)
                {
                    if (bp < 1)
                    {
                        return false;
                    }
                }
                else if (current_player % 2 != 0)
                {
                    if (rp < 1)
                    {
                        return false;
                    }
                }
            }

            else if (move.at(0) == 'd' || move.at(0) == 'D')
            {
                if (current_player % 2 == 0)
                {
                    if (bd < 1)
                    {
                        return false;
                    }
                }
                else if (current_player % 2 != 0)
                {
                    if (rd < 1)
                    {
                        return false;
                    }
                }
            }

            // checks if the space is empty
            if (board[row][column].isEmpty() == false)
            {
                return false;
            }

            // if move is valid return true
            return true;
        }

        if (move_type == 1 && move.length() == 3) // logic if move type is 1, which is removing a group of three
        {
            char a = input.at(0);
            char b = input.at(1);

            // check if the row and column are valid digits
            if (!std::isdigit(a) || !std::isdigit(b))
            {

                return false;
            }

            int row = a - '0';
            int column = b - '0';

            char direction = move.at(2);

            if (direction != 'h' && direction != 'H' && direction != 'v' && direction != 'V' && direction != 'd' && direction != 'D')
            {
                return false;
            }

            if (current_player % 2 == 1) // player 1, RED
            {
                if (board[row][column].getStatus().at(0) != 'R')
                {
                    cout << "Check" << endl;
                    return false;
                }
                if (direction == 'v' || direction == 'V')
                {
                    if (board[row - 1][column].getStatus().at(0) != 'R' || board[row + 1][column].getStatus().at(0) != 'R')
                    {
                        cout << "Check1" << endl;
                        return false;
                    }
                    return true;
                }
                if (direction == 'h' || direction == 'H')
                {
                    if (board[row][column - 1].getStatus().at(0) != 'R' || board[row][column + 1].getStatus().at(0) != 'R')
                    {
                        cout << "Check2" << endl;

                        return false;
                    }
                    return true;
                }
                if (direction == 'd' || direction == 'D')
                {
                    if ((board[row - 1][column - 1].getStatus().at(0) != 'R' || board[row + 1][column + 1].getStatus().at(0) != 'R') && (board[row - 1][column + 1].getStatus().at(0) != 'R' || board[row + 1][column - 1].getStatus().at(0) != 'R'))
                    {
                        cout << "Check3" << endl;

                        return false;
                    }
                    return true;
                }
            }
            if (current_player % 2 == 0) // player 1, RED
            {
                if (board[row][column].getStatus().at(0) != 'B')
                {
                    cout << "Check" << endl;
                    return false;
                }
                if (direction == 'v' || direction == 'V')
                {
                    if (board[row - 1][column].getStatus().at(0) != 'B' || board[row + 1][column].getStatus().at(0) != 'B')
                    {
                        cout << "Check1" << endl;
                        return false;
                    }
                    return true;
                }
                if (direction == 'h' || direction == 'H')
                {
                    if (board[row][column - 1].getStatus().at(0) != 'B' || board[row][column + 1].getStatus().at(0) != 'B')
                    {
                        cout << "Check2" << endl;

                        return false;
                    }
                    return true;
                }
                if (direction == 'd' || direction == 'D')
                {
                    if ((board[row - 1][column - 1].getStatus().at(0) != 'B' || board[row + 1][column + 1].getStatus().at(0) != 'B') && (board[row - 1][column + 1].getStatus().at(0) != 'B' || board[row + 1][column - 1].getStatus().at(0) != 'B'))
                    {
                        cout << "Check3" << endl;

                        return false;
                    }
                    return true;
                }
            }
        }

        if (move_type == 2 && move.length() == 2) // logic if move type is 2, which is removing a single piece
        {
            if (current_player % 2 != 0 && (rp + rd) != 0)
            {
                return false;
            }
            else if (current_player % 2 == 0 && (bp + bd) != 0)
            {
                return false;
            }

            char a = input.at(0);
            char b = input.at(1);

            // check if the row and column are valid digits
            if (!std::isdigit(a) || !std::isdigit(b))
            {
                return false;
            }

            int row = a - '0';
            int column = b - '0';

            if (column < 0 || column > 5 || row < 0 || row > 5)
            {
                return false;
            }
            

            if (current_player % 2 != 0) // Player 1, RED
            {
                if (board[row][column].isRD() == false && board[row][column].isRP() == false)
                {
                    return false;
                }
                return true;
            }
            else if (current_player % 2 == 0) // Player 2, BLUE
            {
                if (board[row][column].isBD() == false && board[row][column].isBP() == false)
                {
                    return false;
                }
                return true;
            }
        }
        return false;
    }

    std::string boop::get_location(const std::string &move) const
    {
        int row;
        int column;
        char x;

        if (move.length() == 3 && move_type == 0)
        {
            // grabs the individual characters from the move given by the player
            char type = move.at(0);
            type = tolower(type);

            x = move.at(1);

            // converts the letter in the move string into the correct row number
            switch (tolower(x))
            {
            case 'a':
                row = 0;
                break;
            case 'b':
                row = 1;
                break;
            case 'c':
                row = 2;
                break;
            case 'd':
                row = 3;
                break;
            case 'e':
                row = 4;
                break;
            case 'f':
                row = 5;
                break;
            default:
                row = -1;
                break;
            }

            // because the user inputs the row and column as 1-6, we need to subtract 1 from the row number to make sure it
            // correctly matches the arrays which are 0-5
            column = (move.at(2) - '0') - 1;

            // combines the three characters into a string to be returned
            std::string new_move = std::string(1, type) + to_string(row) + to_string(column);

            return new_move;
        }
        else if (move.length() == 3 && move_type == 1)
        {
            x = move.at(0);

            // converts the letter in the move string into the correct row number
            switch (tolower(x))
            {
            case 'a':
                row = 0;
                break;
            case 'b':
                row = 1;
                break;
            case 'c':
                row = 2;
                break;
            case 'd':
                row = 3;
                break;
            case 'e':
                row = 4;
                break;
            case 'f':
                row = 5;
                break;
            default:
                row = -1;
                break;
            }

            // because the user inputs the row and column as 1-6, we need to subtract 1 from the row number to make sure it
            // correctly matches the arrays which are 0-5
            column = (move.at(1) - '0') - 1;

            char direction = move.at(2);

            // combines the three characters into a string to be returned
            std::string new_move = to_string(row) + to_string(column) + to_string(direction);

            return new_move;
        }

        else if (move.length() == 2 && move_type == 2)
        {
            x = move.at(0);

            // converts the letter in the move string into the correct row number
            switch (tolower(x))
            {
            case 'a':
                row = 0;
                break;
            case 'b':
                row = 1;
                break;
            case 'c':
                row = 2;
                break;
            case 'd':
                row = 3;
                break;
            case 'e':
                row = 4;
                break;
            case 'f':
                row = 5;
                break;
            default:
                row = -1;
                break;
            }

            // because the user inputs the row and column as 1-6, we need to subtract 1 from the row number to make sure it
            // correctly matches the arrays which are 0-5
            column = (move.at(1) - '0') - 1;

            // combines the two characters into a string to be returned
            std::string new_move = to_string(row) + to_string(column);

            return new_move;
        }
        return move;
    }

    void boop::display_message(const std::string &message) const
    {
        cout << message;
    }
}
