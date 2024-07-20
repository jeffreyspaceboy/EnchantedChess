#include "../inc/chess_bot.hpp"

#include <stdio.h>

// #define STEPS_PER_REVOLUTION 800
// #define MM_PER_REVOLUTION 39?
// #define STEPS_PER_MM 800/39

ChessBot::ChessBot() {
  char buffer[1024];
  serial_port.read(buffer, sizeof(buffer) - 1);
  std::cout << buffer << std::endl;
  // apply_grbl_settings();
  this->serial_port.write("$X\n");
  this->serial_port.write("$3=1\n"); //(dir port invert mask:00000000) // 0bZYX
  this->serial_port.write("$25=3000.000\n"); //(homing seek, mm/min)
  this->serial_port.write("$100=20.000\n"); //(x, step/mm)
  this->serial_port.write("$101=20.000\n"); //(y, step/mm)
  this->serial_port.write("$102=20.000\n"); //(z, step/mm)
  this->serial_port.write("$130=300.000\n"); //(x max travel, mm)
  this->serial_port.write("$131=300.000\n"); //(y max travel, mm)
  this->serial_port.write("$132=300.000\n"); //(z max travel, mm)
  home();
}

ChessBot::~ChessBot() {
  return;
}

int ChessBot::apply_grbl_settings() {
  this->serial_port.write("$0=10\n"); //(step pulse, usec)
  this->serial_port.write("$1=25\n"); //(step idle delay, msec)
  this->serial_port.write("$2=0\n"); //(step port invert mask:00000000)
  this->serial_port.write("$3=1\n"); //(dir port invert mask:00000000) // 0bZYX
  this->serial_port.write("$4=0\n"); //(step enable invert, bool)
  this->serial_port.write("$5=0\n"); //(limit pins invert, bool)
  this->serial_port.write("$6=0\n"); //(probe pin invert, bool)
  this->serial_port.write("$10=3\n"); //(status report mask:00000011)
  this->serial_port.write("$11=0.010\n"); //(junction deviation, mm)
  this->serial_port.write("$12=0.002\n"); //(arc tolerance, mm)
  this->serial_port.write("$13=0\n"); //(report inches, bool)
  this->serial_port.write("$20=0\n"); //(soft limits, bool)
  this->serial_port.write("$21=1\n"); //(hard limits, bool)
  this->serial_port.write("$22=1\n"); //(homing cycle, bool)
  this->serial_port.write("$23=7\n"); //(homing dir invert mask:00000111)
  this->serial_port.write("$24=250.000\n"); //(homing feed, mm/min)
  this->serial_port.write("$25=3000.000\n"); //(homing seek, mm/min)
  this->serial_port.write("$26=250\n"); //(homing debounce, msec)
  this->serial_port.write("$27=1.000\n"); //(homing pull-off, mm)
  this->serial_port.write("$100=20.000\n"); //(x, step/mm)
  this->serial_port.write("$101=20.000\n"); //(y, step/mm)
  this->serial_port.write("$102=20.000\n"); //(z, step/mm)
  this->serial_port.write("$110=100000.000\n"); //(x max rate, mm/min)
  this->serial_port.write("$111=100000.000\n"); //(y max rate, mm/min)
  this->serial_port.write("$112=100000.000\n"); //(z max rate, mm/min)
  this->serial_port.write("$120=300.000\n"); //(x accel, mm/sec^2)
  this->serial_port.write("$121=300.000\n"); //(y accel, mm/sec^2)
  this->serial_port.write("$122=300.000\n"); //(z accel, mm/sec^2)
  this->serial_port.write("$130=300.000\n"); //(x max travel, mm)
  this->serial_port.write("$131=300.000\n"); //(y max travel, mm)
  this->serial_port.write("$132=300.000\n"); //(z max travel, mm)
}

int ChessBot::home() {
  char cmd[50];

  this->serial_port.write("$X\n"); // Unlock
  this->serial_port.write("$H\n"); // Home
  this->serial_port.write("G91\n");
  sprintf(cmd, "G1 X%d Y%d Z0 F%d\n", this->origin_offset[0], this->origin_offset[1], 3000);
  this->serial_port.write(cmd);
  this->serial_port.write("G92 X0 Y0 Z0\n"); // Set home position to 0,0,0
  this->serial_port.write("G90\n"); // Use absolute position mode
  this->jiggle();
  return SUCCESS;
}

int ChessBot::jiggle() {
  this->serial_port.write("G91\n");
  this->serial_port.write( "G1 X3 Y0 Z0 F50000\n");
  this->serial_port.write( "G1 X0 Y3 Z0 F50000\n");
  this->serial_port.write( "G1 X-3 Y0 Z0 F50000\n");
  this->serial_port.write( "G1 X0 Y-3 Z0 F50000\n");
  this->serial_port.write( "G1 X3 Y0 Z0 F50000\n");
  this->serial_port.write( "G1 X0 Y3 Z0 F50000\n");
  this->serial_port.write( "G1 X-3 Y0 Z0 F50000\n");
  this->serial_port.write( "G1 X0 Y-3 Z0 F50000\n");
  this->serial_port.write( "G1 X3 Y0 Z0 F50000\n");
  this->serial_port.write( "G1 X0 Y3 Z0 F50000\n");
  this->serial_port.write( "G1 X-3 Y0 Z0 F50000\n");
  this->serial_port.write( "G1 X0 Y-3 Z0 F50000\n");
  this->serial_port.write( "G1 X3 Y0 Z0 F50000\n");
  this->serial_port.write( "G1 X0 Y3 Z0 F50000\n");
  this->serial_port.write( "G1 X-3 Y0 Z0 F50000\n");
  this->serial_port.write( "G1 X0 Y-3 Z0 F50000\n");
  this->serial_port.write( "G1 X0 Y0 Z0 F50000\n");
  this->serial_port.write("G90\n"); // Use absolute position mode
  return SUCCESS;
}

int ChessBot::move() {
  return SUCCESS;
}

int ChessBot::print_board() {
  std::cout << this->board << std::endl;
}

int ChessBot::print_active_player() {
  if (board.sideToMove() == chess::Color::WHITE) {
    std::cout << "PLAYER: ORANGE" << std::endl;
  } else if (board.sideToMove() == chess::Color::BLACK) {
    std::cout << "PLAYER: GREY" << std::endl;
  } 
}

int ChessBot::print_playable_moves() {
  chess::Movelist moves;
  chess::movegen::legalmoves(moves, this->board, 63);
  std::cout << "Possible Moves: [";
  for (const auto &move : moves) {
      std::cout << " " << chess::uci::moveToUci(move);
  }
  std::cout << "]" << std::endl;
}

int ChessBot::loop_manual_gcode() {
  char buffer[1024];
  int done = 0;
  while (done == 0) {
    this->serial_port.read(buffer, sizeof(buffer) - 1);
    printf("Received: %s\r\n", buffer);

    printf("Send: ");
    char str[128];
    fgets(str, 128, stdin);
    if (str[0] == 'q') { 
      done = 1;
      break;
    }
    this->serial_port.write(str);
    this->jiggle();
  }
  return SUCCESS;
}

int ChessBot::loop_digital_chess_game(){
  chess::Movelist moves;

  bool running = true;
  while (running) {
      this->print_board();
      this->print_active_player();
      this->print_playable_moves();

      std::string user_piece;
      std::string user_location;
      std::cout << "Select piece: ";
      std::cin >> user_piece;
      std::cout << "Select end location: ";
      std::cin >> user_location;
      chess::Move user_move = chess::Move::make(chess::Square(user_piece), chess::Square(user_location));

      this->board.makeMove(user_move);
      std::cout << chess::uci::moveToUci(user_move) << std::endl;
  }
  return SUCCESS;
}

// X: 10,57,105,153,202,251,297,347
// Y: 03,53,099,149,197,245,295,335

// Received: $0=10 (step pulse, usec)
// $1=25 (step idle delay, msec)
// $2=0 (step port invert mask:00000000)
// $3=0 (dir port invert mask:00000000)
// $4=0 (step enable invert, bool)
// $5=0 (limit pins invert, bool)
// $6=0 (probe pin invert, bool)
// $10=3 (status report mask:00000011)
// $11=0.010 (junction deviation, mm)
// $12=0.002 (arc tolerance, mm)
// $13=0 (report inches, bool)
// $20=0 (soft limits, bool)
// $21=1 (hard limits, bool)
// $22=1 (homing cycle, bool)
// $23=7 (homing dir invert mask:00000111)
// $24=250.000 (homing feed, mm/min)
// $25=2500.000 (homing seek, mm/min)
// $26=250 (homing debounce, msec)
// $27=1.000 (homing pull-off, mm)
// $100=15.625 (x, step/mm)
// $101=15.625 (y, step/mm)
// $102=250.000 (z, step/mm)
// $110=100000.000 (x max rate, mm/min)
// $111=100000.000 (y max rate, mm/min)
// $112=3000.000 (z max rate, mm/min)
// $120=150.000 (x accel, mm/sec^2)
// $121=150.000 (y accel, mm/sec^2)
// $122=10.000 (z accel, mm/sec^2)
// $130=350.000 (x max travel, mm)
// $131=350.000 (y max travel, mm)
// $132=350.000 (z max travel, mm)