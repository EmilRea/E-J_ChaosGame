// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

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
    font1.loadFromFile("ChaosFont.ttf");
    title.setFont(font1);
    title.setString("Chaos Game");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    // Sets font for the instructions along with it's specifications
    sf::Font font2;
    sf::Text instructions;
    font2.loadFromFile("DirectionsFont.ttf");
    instructions.setFont(font2);
    instructions.setString("- Click on three points to form a triangle.\n\n- Click on a fourth point to start the chaos.");
    instructions.setCharacterSize(25);
    instructions.setFillColor(sf::Color::White);


    vector<Vector2f> vertices;
    vector<Vector2f> points;
    
    //sets a vector of colors
    vector<Color> background;
    background.push_back(Color::Magenta);
    background.push_back(Color::Blue);
    background.push_back(Color::Red);
    background.push_back(Color::Yellow);
    background.push_back(Color::Green);
    background.push_back(Color::Cyan);

    int frames = 0;
    int randColor = 0;

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

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
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
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            float trianglePoint;
            float newX, newY;

            trianglePoint = rand() % 3;

            newX = (vertices[trianglePoint].x + points[points.size() - 1].x) / 2;
            newY = (vertices[trianglePoint].y + points[points.size() - 1].y) / 2;

            sf::Vector2f newPoint(newX, newY);
            points.push_back(newPoint);

        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();
        if (vertices.size() == 0)
        {
            //displays the title and instructions
            title.setPosition(540.f, 300.f);
            instructions.setPosition(600.f, 360.f);
            window.draw(title);
            window.draw(instructions);
        }
        else
        {
            //once a user clicks, sets background to the bottom right corner
            if (frames == 0 || frames % 500 == 0)
            {
                //color changes every 500 frames
                randColor = rand() % 6;
            }
            title.setPosition(1100.f, 1000.f);
            //sets the color of the bottom right conrer to a random color
            title.setFillColor(background[randColor]);
            window.draw(title);

        }
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect1(Vector2f(10,10));
            rect1.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect1.setFillColor(Color::Blue);
            window.draw(rect1);
        }
        for (int j = 0; j < points.size(); j++)
        {
            //displays the points after the triangle is set
            RectangleShape rect2(Vector2f(10, 10));
            rect2.setPosition(Vector2f(points[j].x, points[j].y));
            rect2.setFillColor(Color::White);
            window.draw(rect2);
        }
        frames++;
        window.display();
    }
}
