#include <SFML/Graphics.hpp>
#include<iostream>
#include <SFML/System.hpp>
#include<chrono>
#include <time.h>
#include<stdio.h>
#include <cstdlib>

int positionX = 0;
int i = 0;
int spaceStatus = 0;
float gravity = 1;
float velocityX = 0;
float velocityY = 2;
int gameStatus = 0;
long long oldBarTime = 0;
int barStatus = 0;
float pipeVelocity = 0;
float pipeSpeed = 3;
int  counterStatus = 0;
int counter = 0;
sf::Vector2f pipeV(350, -180);
sf::Vector2f pipe2V(900, -250);

void setup() {
    std::cout << "Program Start";
    srand(time(0));
}

class Pipe
{
       public:
        float deltaX = 0;
        float pipePositionX = 0;
        float pipePositionY = 0;
        int max = -150, min = 150;
        int randomNumber = 0;
     
    void pipeMove(sf::RenderWindow& window, sf::Vector2f Vpipe,sf::Vector2f& position) {
        sf::Texture Pipe;
        sf::Sprite pipe;
        
        if (gameStatus == 2) {
           
        }
        pipePositionX = Vpipe.x + pipeVelocity + 62+ deltaX;
        pipePositionY = Vpipe.y + randomNumber;
         

        Pipe.loadFromFile("img/Pipe.png");
    
        pipe.setTexture(Pipe);

        if (gameStatus == 0)
        {

            pipe.setPosition(Vpipe.x,Vpipe.y);
            window.draw(pipe);
        }
        else {
            pipe.setPosition(pipePositionX  - 62, pipePositionY);
            window.draw(pipe);
            sf::RectangleShape pipeBoxUp(sf::Vector2f (75, 610));
            pipeBoxUp.setPosition(pipePositionX, pipePositionY );
            sf::RectangleShape pipeBoxDown(sf::Vector2f(75, 610));
            pipeBoxDown.setPosition(pipePositionX, pipePositionY+870);
           // window.draw(pipeBoxDown);
           // window.draw(pipeBoxUp);
  }
                
        if (pipePositionX <-70) {
            
            randomNumber = (rand() % (min - max + 1)) + max;
            deltaX += 1070;
          
        }
       
        if (position.x+100 > pipePositionX &&position.x <pipePositionX+75 ) {
            if (position.y > pipePositionY + 585 && position.y < pipePositionY + 795) {
                if (counterStatus == 0) {
                    counter++;
                    counterStatus = 1;                 
                }
       
          }
            else 
            {
                gameStatus = 2;
                std::cout << "konec" << std::endl;
            }

        }
        else {
            counterStatus = 0;
           // std::cout << counter;
        }
      
    }
};

class Bird 
{

public:
    float deltaPosition = 0;

    void move(sf::RenderWindow& window, sf::Vector2f& position) {
        
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Sprite spriteUP;
        sf::Texture textureUP;
        
        
       // std::cout << RealTime.asSeconds() << std::endl;

        textureUP.loadFromFile("img/Bird_up.png");
        texture.loadFromFile("img/Bird_down.png");
        spriteUP.setTexture(textureUP);
        sprite.setTexture(texture);
        spriteUP.setPosition(position.x  , position.y );
        sprite.setPosition(position.x , position.y );

        sf::RectangleShape rectangle(sf::Vector2f(100, 100));
        rectangle.setPosition(position.x, position.y);
        if (gameStatus == 0) {
            if (position.y >= 500)
            {
                gravity = 0.5;
                velocityY = -10;

            }
        }
        else {
            gravity = 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spaceStatus == 0) {
      
            spaceStatus = 1;  
                                   
            velocityY = -18;
            
             }else{     
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
             spaceStatus = 0;
            }
        }       
        if (gameStatus != 2) {
            velocityY += gravity;                                                           
            position.x += velocityX;
            position.y += velocityY;
        }
             //+spaceStatus
         
        if (position.y >= 900) {
            position.y = 900;
            velocityY = 0;
        }
        if (position.y < 10) {
            position.y = 10;
            gravity *= -1;
            
            velocityY = 0;            
      }
     
        if (deltaPosition > position.y) {

            window.draw(spriteUP);
        }
        else 
        {
            window.draw(sprite);

        } 
        //window.draw(rectangle);
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
       // std::cout << velocityY <<"  ";
       // std::cout << gravity <<'\n';
        deltaPosition = position.y;
       // std::cout << time << std::endl;
    }
};

class Game : public Bird
{
public:
    Pipe pipe;
    Pipe pipe2;
    

    void gameStart(sf::RenderWindow& window, sf::Vector2f& position) {
        if (gameStatus == 0) {
            pressToPlay(window, position);
            
        }
        else {
            gameLoop(window, position);
        }
    }
    void gameLoop(sf::RenderWindow& window, sf::Vector2f& position) {
        if (gameStatus == 1) {
            Bird::move(window, position);
            pipeVelocity -= pipeSpeed;
            pipe.pipeMove(window,pipeV,position);
            pipe2.pipeMove(window, pipe2V,position);

        }
        else if( gameStatus == 2) {
            gameOver( window,position);
        }
    }

    void gameOver(sf::RenderWindow& window, sf::Vector2f& position) {

          
        Bird::move(window, position);
        
        barJump(window);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            gameStatus = 0;
            
            pipe.pipePositionX = 450;
             pipe2.pipePositionX = 1150;
             pipeVelocity = 0;
             pipe.deltaX = 200;
             pipe2.deltaX = 200;
             position.x = 150;
             position.y = 300;
          
            gameStart(window, position);

        }

    }
private:
    void pressToPlay(sf::RenderWindow& window, sf::Vector2f& position)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || gameStatus == 1) {
            Game::gameLoop(window, position);
          
            if (gameStatus == 2) {

            }
            else {
                gameStatus = 1;
            }
        }
        else {
            
            Bird::move(window, position);
            pipe.pipeMove(window, pipeV,position);
            
          
            barJump(window);
        }


    }
    void barJump(sf::RenderWindow& window) {
       
        sf::Sprite barWhite;
        sf::Sprite barBlack;
        sf::Texture barWhite1;
        sf::Texture barBlack1;
        auto barTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        barWhite1.loadFromFile("img/button_white.png");
        barBlack1.loadFromFile("img/button_black.png");
        barBlack.setTexture(barBlack1);
        barWhite.setTexture(barWhite1);
        barBlack.setPosition(100, 270);
        barWhite.setPosition(100, 270);
        if (barTime - oldBarTime > 500) {
            barStatus++;
            oldBarTime = barTime;


        }
        if (barStatus > 1) {
            barStatus = 0;
        }
        if (barStatus == 0)
        {
            window.draw(barBlack);
        }
        else
        {

            window.draw(barWhite);
        }
    }
};

int main()
    {
    Game game;
    Bird bird;
       

        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        auto millitime = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch()).count();
        setup();
        sf::RenderWindow window(sf::VideoMode(900, 1000), "Floppy_Bird");
        sf::Vector2f position(150, 300);
        sf::Clock clock;


        sf::Texture wallpapers;
        sf::Sprite Swallpapers;
        wallpapers.loadFromFile("img/wallpapers.png");
        Swallpapers.setTexture(wallpapers);


        while (window.isOpen())
        {

            sf::Event event;
            while (window.pollEvent(event))


            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            
            window.clear();
            window.draw(Swallpapers);                                            // kresleni pozadi 
            game.gameStart(window, position);                             // volání class Bird
            // volani class pipe
            window.display();

        }
        return 0;
 }