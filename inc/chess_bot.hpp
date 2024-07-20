#ifndef CHESS_BOT_HPP
#define CHESS_BOT_HPP

#include "serial_port.hpp"

#include "../libs/chess-library/include/chess.hpp"

class ChessBot{
  private:
    int origin_offset[2] = {7,4}; // {x,y} // [mm]
    int board_size[2] = {263,263}; // {x,y} // [mm]

    int jiggle_magnitude = 5;
  public:
    SerialPort serial_port = SerialPort("\\\\.\\COM3"); // TODO: private
    chess::Board board = chess::Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); // TODO: private
    
    ChessBot();
    ~ChessBot();

    int apply_grbl_settings();
    int home();

    int jiggle();

    int move();

    int print_board();
    int print_active_player();
    int print_playable_moves();

    // DEBUG FUNCS
    int loop_manual_gcode();
    int loop_digital_chess_game();
};

#endif