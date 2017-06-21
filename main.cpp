#include <cstdio>
#include <SFML/Graphics.hpp>
#include "chip8/chip8.h"


int main(int argc, char **argv)
{

  Chip8 emulator;

  if(emulator.okConstruct == false)
  {
    fprintf(stderr, "Bad allocation");
    exit(1);
  }


  if (argc != 2)
  {
    fprintf(stderr, "Usage: ROM file is missing\n");
    exit(1);
  }

  int whatErr = emulator.loadBinary(argv[1]);
  switch(whatErr)
  {
    case BADOPEN:
      {
        fprintf(stderr, "Bad opening");
        exit(1);
      }
    case BADALLOC:
      {
        fprintf(stderr, "Bad allocation");
        exit(1);
      }
    case BADREAD:
      {
        fprintf(stderr, "Bad reading the rom");
        exit(1);
      }
  }

  sf::RenderWindow window(sf::VideoMode(640, 320), "Chip8");

  // clear the window with black color
  window.clear(sf::Color::White);

  //window.setVerticalSyncEnabled(true);

  sf::Clock clocks;

  sf::Time time1;
  sf::Time time2;


  time1 = clocks.getElapsedTime();

  int opcode_per_second = 0;
  int limit = 10;

  // run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;


    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window

      switch(event.type)
      {
        case(sf::Event::Closed):
          window.close();
          break;

        case(sf::Event::KeyPressed):
          switch(event.key.code)
          {
              case sf::Keyboard::Num1:  emulator.keyboard.pressKey(0x1); break;
              case sf::Keyboard::Num2:  emulator.keyboard.pressKey(0x2); break;
              case sf::Keyboard::Num3:  emulator.keyboard.pressKey(0x3); break;
              case sf::Keyboard::Num4:  emulator.keyboard.pressKey(0xc); break;
              case sf::Keyboard::Q:     emulator.keyboard.pressKey(0x4); break;
              case sf::Keyboard::W:     emulator.keyboard.pressKey(0x5); break;
              case sf::Keyboard::E:     emulator.keyboard.pressKey(0x6); break;
              case sf::Keyboard::R:     emulator.keyboard.pressKey(0xd); break;
              case sf::Keyboard::A:     emulator.keyboard.pressKey(0x7); break;
              case sf::Keyboard::S:     emulator.keyboard.pressKey(0x8); break;
              case sf::Keyboard::D:     emulator.keyboard.pressKey(0x9); break;
              case sf::Keyboard::F:     emulator.keyboard.pressKey(0xe); break;
              case sf::Keyboard::Z:     emulator.keyboard.pressKey(0xa); break;
              case sf::Keyboard::X:     emulator.keyboard.pressKey(0x0); break;
              case sf::Keyboard::C:     emulator.keyboard.pressKey(0xb); break;
              case sf::Keyboard::V:     emulator.keyboard.pressKey(0xf); break;
          }
          break;

        case(sf::Event::KeyReleased):
            switch(event.key.code)
            {
              case sf::Keyboard::Num1:  emulator.keyboard.releaseKey(0x1); break;
              case sf::Keyboard::Num2:  emulator.keyboard.releaseKey(0x2); break;
              case sf::Keyboard::Num3:  emulator.keyboard.releaseKey(0x3); break;
              case sf::Keyboard::Num4:  emulator.keyboard.releaseKey(0xc); break;
              case sf::Keyboard::Q:     emulator.keyboard.releaseKey(0x4); break;
              case sf::Keyboard::W:     emulator.keyboard.releaseKey(0x5); break;
              case sf::Keyboard::E:     emulator.keyboard.releaseKey(0x6); break;
              case sf::Keyboard::R:     emulator.keyboard.releaseKey(0xd); break;
              case sf::Keyboard::A:     emulator.keyboard.releaseKey(0x7); break;
              case sf::Keyboard::S:     emulator.keyboard.releaseKey(0x8); break;
              case sf::Keyboard::D:     emulator.keyboard.releaseKey(0x9); break;
              case sf::Keyboard::F:     emulator.keyboard.releaseKey(0xe); break;
              case sf::Keyboard::Z:     emulator.keyboard.releaseKey(0xa); break;
              case sf::Keyboard::X:     emulator.keyboard.releaseKey(0x0); break;
              case sf::Keyboard::C:     emulator.keyboard.releaseKey(0xb); break;
              case sf::Keyboard::V:     emulator.keyboard.releaseKey(0xf); break;

            }
            break;
        }
    }

    if (opcode_per_second < limit)
    {
      emulator.doCycle();
      if(error != OK)
      {
        fprintf(stderr, "Some problem with executing rom. Change this.");
        exit(1);
      }
      opcode_per_second++;
    }

    time2 = clocks.getElapsedTime();


    if (time2.asMilliseconds() - time1.asMilliseconds() >=  1000/60)
    {
      
      emulator.decreaseTimers();
      
      time1 = clocks.getElapsedTime();


      sf::RectangleShape rectangle;
      rectangle.setSize(sf::Vector2f(10, 10));

      for (int i = 0; i < SCREENSIZE; i++)
      {
        rectangle.setPosition((i % 64) * 10, (i / 64) * 10);
        if (emulator.m_gfx[i] == 1)
          rectangle.setFillColor(sf::Color::Black);
        else
          rectangle.setFillColor(sf::Color::White);

        window.draw(rectangle);
      }

      opcode_per_second = 0;
      window.display();

    }
}

  return 0;

}
