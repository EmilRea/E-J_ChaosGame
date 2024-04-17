
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cmath>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    srand(time(0));

    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game", Style::Default);

    // Sets font for the title along with it's specifications
    sf::Font font1;
sf:Text title;
    font1.loadFromFile("./fonts/BungeeSpice-Regular.ttf");
    title.setFont(font1);
    title.setString("Chaos Game");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    // Sets font for the instructions along with it's specifications
    sf::Font font2;
    sf::Text instructions;
    font2.loadFromFile("./fonts/Frijole-Regular.ttf");
    instructions.setFont(font2);
    instructions.setString("\n- Click on three points to form a triangle.\n\n- Click on a fourth point to start the chaos.\n\n- Click 'r' to restart.");
    instructions.setCharacterSize(25);
    instructions.setFillColor(sf::Color::White);
    // Sets restarting screen
    sf::Font font3;
    sf::Text restarting;
    font3.loadFromFile("./fonts/RockSalt-Regular.ttf");
    restarting.setFont(font3);
    restarting.setString("restarting...");
    restarting.setCharacterSize(25);
    restarting.setPosition(1700.f, 1000.f);
    restarting.setFillColor(sf::Color::White);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    //sets a vector of colors Purpose: is for logo changing colors
    vector<Color> background;
    background.push_back(Color::Magenta);
    background.push_back(Color::Blue);
    background.push_back(Color::Red);
    background.push_back(Color::Yellow);
    background.push_back(Color::Green);
    background.push_back(Color::Cyan);

    bool restart = false;

    int frames = 0;
    int randColor = 0;
    int area_of_mid_size_triangle = 109005;//line 116
    int restartingScreen = 0;

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        //restarts to main menu
        if (Keyboard::isKeyPressed(Keyboard::R))
        {
            restartingScreen = 1000;//starts the restarting screen to display for 1000 frames
            restart = true;
        }
        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            float trianglePoint;
            float newX, newY;
            int currentArea;
            //this next part gets the area of the current triangle 
            currentArea = .5 * abs((vertices[0].x * (vertices[1].y - vertices[2].y) + vertices[1].x * (vertices[2].y - vertices[1].y) + vertices[2].x * (vertices[0].y - vertices[2].y)));
            if (points.size() < 31000)
            {
                if (currentArea < area_of_mid_size_triangle)
                {

                    for (int i = 0; i < 3; i++)//creates 3 dots a frame for a slower pattern generation rate
                    {

                        if (points.size() < 5500)//Medium size triangle and under: stops generating more dots when it his 5500 dots
                        {
                            trianglePoint = rand() % 3;

                            newX = (vertices[trianglePoint].x + points[points.size() - 1].x) / 2;
                            newY = (vertices[trianglePoint].y + points[points.size() - 1].y) / 2;

                            sf::Vector2f newPoint(newX, newY);
                            points.push_back(newPoint);
                        }
                    }

                }
                else
                {
                    for (int i = 0; i < 50; i++)//creats 50 dots a frame to create a bigger pattern faster
                    {
                        if (points.size() < 31000)//medium size triangle and over: stops generating more dots when it hits 31000 dots
                        {
                            trianglePoint = rand() % 3;

                            newX = (vertices[trianglePoint].x + points[points.size() - 1].x) / 2;
                            newY = (vertices[trianglePoint].y + points[points.size() - 1].y) / 2;

                            sf::Vector2f newPoint(newX, newY);
                            points.push_back(newPoint);
                        }
                    }
                }
            }


        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();
        if (restartingScreen > 0)//displays restarting screen
        {
            window.draw(restarting);
            --restartingScreen;
        }
        else {
            if (vertices.size() == 0)
            {
                //displays the title and instructions
                title.setPosition(540.f, 300.f);
                instructions.setPosition(600.f, 360.f);
                window.draw(title);
                window.draw(instructions);
            }
            else if (restart)
            {
                //clears all of the points made
                vertices.clear();
                points.clear();
                restart = false;

            }
            else
            {
                if ((frames == 0 || frames % 500 == 0) && points.size() < 2000)//if there are less than 2000 points on the screen
                {
                    //color changes every 500 frames
                    randColor = rand() % 6;
                }
                else if (frames % 10 == 0 && points.size() > 2000)//once there are more than 2000 points one the screen
                {
                    //color changes every 100 frames
                    randColor = rand() % 6;
                }
                //once a user clicks, sets background to the bottom right corner
                title.setPosition(1540.f, 970.f);
                //sets the color of the bottom right corner to a random color
                title.setFillColor(background[randColor]);
                window.draw(title);

            }
            for (int i = 0; i < vertices.size(); i++)
            {
                //displays triangle points
                RectangleShape rect1(Vector2f(10, 10));
                rect1.setPosition(Vector2f(vertices[i].x, vertices[i].y));
                rect1.setFillColor(Color::Blue);
                window.draw(rect1);
            }
            for (int j = 0; j < points.size(); j++)
            {
                //displays the points after the triangle is set
                RectangleShape rect2(Vector2f(7, 7));
                rect2.setPosition(Vector2f(points[j].x, points[j].y));
                rect2.setFillColor(Color::White);
                window.draw(rect2);
            }
        }
        frames++;
        window.display();
    }
}
