#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Circle
{
public:
    std::string N; // name
    float X;       // initial position x
    float Y;       // initial position y
    float SX;      // initial speed x
    float SY;      // initial speed y
    int R;         // RGB color R
    int G;         // RGB color G
    int B;         // RGB color B
    float RD;      // circle radius
};

struct Rectangle
{
public:
    std::string N; // name
    float X;       // initial position x
    float Y;       // initial position y
    float SX;      // initial speed x
    float SY;      // initial speed y
    int R;         // RGB color R
    int G;         // RGB color G
    int B;         // RGB color B
    float W;       // widht
    float H;       // height
};

int main()
{
    // Vectors created for stored shape data
    std::vector<Circle> circleDataList;
    std::vector<Rectangle> rectangleDataList;

    // Reading the txt file
    std::ifstream inputFile("config.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file!" << std::endl;
        return -1;
    }

    // Parsign the data form the txt file and store it in the data structures
    std::string line;
    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string shapeType;
        iss >> shapeType;

        // Assing the data from the txt file to any specific struct and push back the information in the respective vector
        if (shapeType == "Circle")
        {
            Circle circleData;
            while (iss >> circleData.N)
            {
                iss >> circleData.X >> circleData.Y >> circleData.SX >> circleData.SY >> circleData.R >> circleData.G >> circleData.B >> circleData.RD;
                circleDataList.push_back(circleData);
            }
        }
        // Assing the data from the txt file to any specific struct and push back the information in the respective vector
        else if (shapeType == "Rectangle")
        {
            Rectangle rectangleData;
            while (iss >> rectangleData.N)
            {
                iss >> rectangleData.X >> rectangleData.Y >> rectangleData.SX >> rectangleData.SY >> rectangleData.R >> rectangleData.G >> rectangleData.B >> rectangleData.W >> rectangleData.H;
                rectangleDataList.push_back(rectangleData);
            }
        }
    }
    // Always close the file
    inputFile.close();

    // Creating the SFML window to display the shapes
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML SHAPE PRIMITIVES");
    window.setFramerateLimit(60);

    //  Creating vectors in SFML
    std::vector<sf::CircleShape> circles;
    std::vector<sf::RectangleShape> rectangles;

    // creating the text inside the figures
    sf::Font font;
    if (!font.loadFromFile("OpenSans-Light.ttf"))
    {
        std::cerr << "Error reading font";
    }

    // Iterating inside the vector to store the data intially to create the shapes in SFML
    for (const Circle &circleData : circleDataList)
    {
        sf::CircleShape circle(circleData.RD);
        circle.setPosition(circleData.X, circleData.Y);
        circle.setFillColor(sf::Color(circleData.R, circleData.G, circleData.B));
        circles.push_back(circle);
    }

    for (const Rectangle &rectangleData : rectangleDataList)
    {
        sf::RectangleShape rectangle(sf::Vector2(rectangleData.W, rectangleData.H));
        rectangle.setPosition(rectangleData.X, rectangleData.Y);
        rectangle.setFillColor(sf::Color(rectangleData.R, rectangleData.G, rectangleData.B));
        rectangles.push_back(rectangle);
    }

    // Creating events an open the SFML window
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        // Update and draw the circles
        for (std::size_t i = 0; i < circles.size(); ++i)
        {
            // Update the position of the circle based on its speed

            circles[i].setPosition(circles[i].getPosition().x + circleDataList[i].SX,
                                   circles[i].getPosition().y + circleDataList[i].SY);

            // Restrictions for activity of the shapes only inside the SFML window that we created at the begining

            if (circles[i].getPosition().x < 0 || circles[i].getPosition().x > 800.0f - 2 * circleDataList[i].RD)
                circleDataList[i].SX *= -1;
            if (circles[i].getPosition().y < 0 || circles[i].getPosition().y > 600.0f - 2 * circleDataList[i].RD)
                circleDataList[i].SY *= -1;

            // Create the text of any circle
            sf::Text text;
            text.setFont(font);
            text.setString(circleDataList[i].N);
            text.setCharacterSize(18);
            text.setFillColor(sf::Color::White);

            // calculate the circle center
            float circleCenterx{circles[i].getPosition().x + circleDataList[i].RD};
            float circleCentery{circles[i].getPosition().y + circleDataList[i].RD};

            // calculate the text position to center in the circle
            sf::FloatRect textBounds{text.getGlobalBounds()};
            float textPositionx{circleCenterx - textBounds.width / 2};
            float textPositiony{circleCentery - textBounds.height / 2};
            sf::Vector2f textPosition{textPositionx, textPositiony};
            text.setPosition(textPosition);

            textPositionx += circleDataList[i].SX;
            textPositiony += circleDataList[i].SY;

            // Draw the updated circle
            window.draw(circles[i]);
            window.draw(text);
        }

        // Update and draw the rectangles
        for (std::size_t i = 0; i < rectangles.size(); ++i)
        {
            // Update the position of the rectangle based on its speed
            rectangles[i].setPosition(rectangles[i].getPosition().x + rectangleDataList[i].SX,
                                      rectangles[i].getPosition().y + rectangleDataList[i].SY);
            if (rectangles[i].getPosition().x < 0 || rectangles[i].getPosition().x > 800.0f - rectangleDataList[i].W)
                rectangleDataList[i].SX *= -1;
            if (rectangles[i].getPosition().y < 0 || rectangles[i].getPosition().y > 600.0f - rectangleDataList[i].H)
                rectangleDataList[i].SY *= -1;

            // Create the text of any rectangle
            sf::Text text;
            text.setFont(font);
            text.setString(rectangleDataList[i].N);
            text.setCharacterSize(18);
            text.setFillColor(sf::Color::White);

            // calculate the circle center
            float rectangleCenterx{rectangles[i].getPosition().x + rectangleDataList[i].W / 2};
            float rectangleCentery{rectangles[i].getPosition().y + rectangleDataList[i].H / 2};

            // calculate the text position to center in the circle
            sf::FloatRect textBounds{text.getGlobalBounds()};
            float textPositionx{rectangleCenterx - textBounds.width / 2};
            float textPositiony{rectangleCentery - textBounds.height / 2};
            sf::Vector2f textPosition{textPositionx, textPositiony};
            text.setPosition(textPosition);

            textPositionx += rectangleDataList[i].SX;
            textPositiony += rectangleDataList[i].SY;

            // Draw the updated rectangle
            window.draw(rectangles[i]);
            window.draw(text);
        }

        window.display();
    }

    return 0;
}
