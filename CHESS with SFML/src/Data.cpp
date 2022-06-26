#include "Data.hpp"

Engine::Data::Data()
{
    if(tex_BackGround.loadFromFile("data/background-1.jpg")==false) exit(0);

    if(Beams_font.loadFromFile("data/Fonts/Beams.ttf")==false) exit(0);
    if(Pacifico_font.loadFromFile("data/Fonts/Pacifico-Regular.ttf")==false) exit(0);
    if(Round_Bold.loadFromFile("data/Fonts/RoundStyle-Bold.ttf")==false) exit(0);

    if(tex_BBox.loadFromFile("data/board/BBox.png")==false) exit(0);
    if(tex_WBox.loadFromFile("data/board/WBox.png")==false) exit(0);
    if(tex_arrow.loadFromFile("data/arrow.png")==false) exit(0);
}

sf::Texture Engine::Data::loadTexture(std::string str)
{
    sf::Texture tmp;
    if (!tmp.loadFromFile(str))
        std::cout << "Error loading file\n";
    return tmp;
}

sf::Texture Engine::Data::blackKing = Engine::Data::loadTexture("data/coins/BKing.png");
sf::Texture Engine::Data::blackQueen = Engine::Data::loadTexture("data/coins/BQueen.png");
sf::Texture Engine::Data::blackRook = Engine::Data::loadTexture("data/coins/BRook.png");
sf::Texture Engine::Data::blackKnight = Engine::Data::loadTexture("data/coins/BKnight.png");
sf::Texture Engine::Data::blackBishop = Engine::Data::loadTexture("data/coins/BBishop.png");
sf::Texture Engine::Data::blackPawn = Engine::Data::loadTexture("data/coins/BPawn.png");

sf::Texture Engine::Data::whiteKing = Engine::Data::loadTexture("data/coins/WKing.png");
sf::Texture Engine::Data::whiteQueen = Engine::Data::loadTexture("data/coins/WQueen.png");
sf::Texture Engine::Data::whiteRook = Engine::Data::loadTexture("data/coins/WRook.png");
sf::Texture Engine::Data::whiteKnight = Engine::Data::loadTexture("data/coins/WKnight.png");
sf::Texture Engine::Data::whiteBishop = Engine::Data::loadTexture("data/coins/WBishop.png");
sf::Texture Engine::Data::whitePawn = Engine::Data::loadTexture("data/coins/WPawn.png");


