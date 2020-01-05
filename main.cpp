#include <iostream>

#include "basicHeader.h"

int main()
{
  std::cout << "Starting a card Game!" << std::endl;
  Game cardGame(2, 40, 40, 7);
  std::cout << "Game is finished! Exiting main function!" << std::endl;
  return 0; // just exiting main()...
}
