#include "inc/chess_bot.hpp"

int main () {
    ChessBot chessBot = ChessBot();

    // chessBot.loop_manual_gcode();
    // return SUCCESS;

    chessBot.loop_digital_chess_game();
    return SUCCESS;
}