#include "colors.h"
#include "game.h"
#include "space.h"

namespace main_savitch_14
{
    class boop : public game
    {
        public:
            boop();

            ~boop();

            //who play();

            std::string get_user_move() const;

            void make_move(const std::string &move);

            void restart();

            game *clone() const;

            void compute_moves(std::queue<std::string> &moves) const;

            void display_status() const;

            int evaluate() const;

            bool is_game_over() const;

            bool is_legal(const std::string &move) const;

            std::string get_location(const std::string &move) const;

            void display_message(const std::string& message) const;

            void boop_pieces(const std::string&move);
            
            bool check_for_3();

        private:
            space board[6][6];

            int rp, rd, bp, bd;

            int current_player; // if current player is odd, means player 1 RED, if its even, means player 2 BLUE

            int move_type; //move type 0 means place new piece, move type 1 means removing three pieces, move type 2 means remove 1 piece


    };
}