//////////////////////////
/// Game of Life       ///
/// Made by replaceits ///
/// 12-30-13           ///
//////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <iostream>

bool GetInt ( unsigned int* );

int main ( void )
{
    srand( time( NULL ) );
    unsigned int x = 0;
    unsigned int y = 0;
    bool NoWalls = true;
    unsigned int xs, ys;
    std::cout << ".---------------------.\n|Conway's Game of Life|\n|   By:  replaceits   |\n'---------------------'\n";
    do
    {
        std::cout << "X Window: ";
    }while(!GetInt(&xs));
    do
    {
        std::cout << "Y Window: ";
    }while(!GetInt(&ys));
    do
    {
        std::cout << "X Cells: ";
    }while(!GetInt(&x));
    do
    {
        std::cout << "Y Cells: ";
    }while(!GetInt(&y));
    do
    {
         std::cout << "Walls: ";
         std::string inp = "";
         std::getline(std::cin,inp);
         if( inp == "Yes" || inp == "yes" || inp == "y" || inp == "Y" || inp == "1" || inp == "True" || inp == "true" )
         {
             NoWalls = false;
             break;
         }
         else if( inp == "No" || inp == "no" || inp == "n" || inp == "N" || inp == "0" || inp == "false" || inp == "False")
         {
             NoWalls = true;
             break;
         }
    }while(1);
    bool TileMap[x][y];
    std::vector<sf::Vector2u> AliveMap;
    for( unsigned short int ix = 0; ix < x; ++ix )
    {
        for( unsigned short int iy = 0; iy < y; ++iy )
        {
            if(static_cast<bool>(rand()%2))
            {
                TileMap[ix][iy] = true;
                AliveMap.push_back(sf::Vector2u(ix,iy));
            }
            else
            {
                TileMap[ix][iy] = false;
            }
        }
    }
    sf::RenderWindow App(sf::VideoMode(xs,ys),"Life");
    sf::Event AppEvent;
    sf::RectangleShape tile;
    tile.setFillColor( sf::Color(89,147,189) );
    tile.setSize( sf::Vector2f( App.getDefaultView().getSize().x / x, App.getDefaultView().getSize().y / y ) );
    sf::Clock Timer;
    unsigned short int T = 100;
    sf::Clock KeyTimer;
    while(App.isOpen())
    {
        while(App.pollEvent(AppEvent))
        {
            switch(AppEvent.type)
            {
            case sf::Event::Closed:
                App.close();
                break;
            case sf::Event::KeyPressed:
                if( AppEvent.key.code == sf::Keyboard::R)
                {
                    for( unsigned short int ix = 0; ix < x; ++ix )
                    {
                        for( unsigned short int iy = 0; iy < y; ++iy )
                        {
                            if(static_cast<bool>(rand()%2))
                            {
                                TileMap[ix][iy] = true;
                                AliveMap.push_back(sf::Vector2u(ix,iy));
                            }
                            else
                            {
                                TileMap[ix][iy] = false;
                            }
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        if(KeyTimer.getElapsedTime().asMilliseconds() >= 50)
        {
            if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down ))
                T += 10;
            if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
            {
                if( T - 10 <= 0 )
                    T = 0;
                else
                    T -= 10;
            }
            KeyTimer.restart();
        }
        if(Timer.getElapsedTime().asMilliseconds() >= T)
        {
            AliveMap.erase(AliveMap.begin(),AliveMap.end());
            bool TmpMap[x][y];
            for( unsigned short int ix = 0; ix < x; ++ix )
            {
                for( unsigned short int iy = 0; iy < y; ++iy )
                {
                    TmpMap[ix][iy] = false;
                }
            }
            for( unsigned short int ix = 0; ix < x; ++ix )
            {
                for( unsigned short int iy = 0; iy < y; ++iy )
                {
                    unsigned short int neighbors = 0;
                    signed short int tx;
                    signed short int ty;
                    for( unsigned short int i = 0; i < 8; ++i )
                    {
                        switch(i)
                        {
                        case 0: /// -1 -1
                            tx = ix - 1;
                            ty = iy - 1;
                            break;
                        case 1: /// 0 -1
                            tx = ix;
                            ty = iy - 1;
                            break;
                        case 2: /// 1 -1
                            tx = ix + 1;
                            ty = iy - 1;
                            break;
                        case 3: /// -1 0
                            tx = ix - 1;
                            ty = iy;
                            break;
                        case 4: /// 1 0
                            tx = ix + 1;
                            ty = iy;
                            break;
                        case 5: /// -1 1
                            tx = ix - 1;
                            ty = iy + 1;
                            break;
                        case 6: /// 0 1
                            tx = ix;
                            ty = iy + 1;
                            break;
                        case 7: /// 1 1
                            tx = ix + 1;
                            ty = iy + 1;
                            break;
                        default:
                            break;
                        }
                        /// [0][1][2]
                        /// [3][t][4]
                        /// [5][6][7]
                        if(NoWalls)
                        {
                            if(tx == -1)
                                tx = x - 1;
                            else if(tx == static_cast<signed int>(x))
                                tx = 0;
                            if(ty == -1)
                                ty = y - 1;
                            else if( ty == static_cast<signed int>(y))
                                ty = 0;
                            if(TileMap[tx][ty])
                                neighbors++;
                        }
                        else
                            if( tx != -1 && tx != static_cast<signed int>(x) && ty != -1 && ty != static_cast<signed int>(y))
                                if(TileMap[tx][ty])
                                    neighbors++;

                        if(TileMap[ix][iy])
                        {
                            if(neighbors > 3)
                            {
                                TmpMap[ix][iy] = false;
                                break;
                            }
                            if( i == 7 )
                            {
                                if(neighbors < 2)
                                {
                                    TmpMap[ix][iy] = false;
                                    break;
                                }
                                else if(neighbors == 2 || neighbors == 3)
                                {
                                    TmpMap[ix][iy] = true;
                                    AliveMap.push_back(sf::Vector2u(ix,iy));
                                    break;
                                }
                            }
                        }
                        else if( i == 7)
                        {
                            if( neighbors == 3)
                            {
                                TmpMap[ix][iy] = true;
                                AliveMap.push_back(sf::Vector2u(ix,iy));
                                break;
                            }
                        }
                    }
                }
            }
            for( unsigned short int ix = 0; ix < x; ++ix )
                for( unsigned short int iy = 0; iy < y; ++iy )
                    TileMap[ix][iy] = TmpMap[ix][iy];
            Timer.restart();
        }
        App.clear(sf::Color(40,40,40));
        for( std::vector<sf::Vector2u>::iterator it = AliveMap.begin(); it != AliveMap.end(); ++it )
        {
            tile.setPosition( sf::Vector2f( App.getDefaultView().getSize().x / x * it->x, App.getDefaultView().getSize().y / y * it->y) );
            App.draw(tile);
        }
        App.display();
    }
    return EXIT_SUCCESS;
}

bool GetInt ( unsigned int *output )
{
    std::string input = "";
    std::getline(std::cin,input);
    for( std::string::iterator it = input.begin(); it != input.end(); it++ )
    {
        switch(*it)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            break;
        default:
            return false;
            break;
        }
    }
    *output = static_cast<unsigned int>( atoi( input.c_str() ) );
    return true;
}
