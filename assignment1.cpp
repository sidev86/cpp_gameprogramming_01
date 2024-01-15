#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

class Shape
{
	std::string m_type = "Type"; 
	std::string m_name = "Name";
	int m_posX = 0; 
	int m_posY = 0; 
	int m_speedX = 0; 
	int m_speedY = 0; 
	int m_red;
	int m_green;
	int m_blue;
	int m_width = 0; 
	int m_height = 0; 
	int m_radius = 0;
	
public: 
	Shape() {}
	
	Shape(std::string type, std::string name, int posX, int posY, int speedX, int speedY, int red, int green, int blue, int width, int height, int radius)
		: m_type(type)
		, m_name(name)
		, m_posX(posX)
		, m_posY(posY)
		, m_speedX(speedX)
		, m_speedY(speedY)
		, m_red(red)
		, m_green(green)
		, m_blue(blue)
		, m_width(width)
		, m_height(height)
		, m_radius(radius)
	{
	
	}
	
	std::string getType()
	{
		return m_type;
	}
	
	std::string getName()
	{
		return m_name;
	}
	
	int getPosX()
	{
		return m_posX;
	}
	
	int getPosY()
	{
		return m_posY;
	}
	
	int getSpeedX()
	{
		return m_speedX;
	}
	
	int getSpeedY()
	{
		return m_speedY;
	}
	int getRedRGB()
	{
		return m_red;
	}
	
	int getGreenRGB()
	{
		return m_green;
	}
	
	int getBlueRGB()
	{
		return m_blue; 
	}
	
	int getWidth()
	{
		return m_width;
	}
	
	int getHeight()
	{
		return m_height; 
	}
	
	int getRadius()
	{
		return m_radius;
	}
	
	void print()
	{
		std::cout << "Shape: " << m_type << "\n";
		std::cout << "Name: " << m_name << "\n";
		std::cout << "Position: X = " << m_posX << "  Y = " << m_posY << "\n";
		std::cout << "Speed: X = " << m_speedX << "  Y = " << m_speedY << "\n";
		std::cout << "Color: R = " << m_red << " G = " << m_green << " B = " << m_blue << "\n"; 
		if (m_type.compare("Circle") == 0)
			std::cout << "Radius: " << m_radius << "\n";
		else if (m_type.compare("Rectangle") == 0)
		{
			std::cout << "Width: " << m_width << "\n";
			std::cout << "Height: " << m_height << "\n";
		}
		
	
	}

};

class Scene
{
	int m_width = 1280;
	int m_height = 720;
	std::vector<Shape> m_shapes;
public: 
	Scene() {}
	
	Scene(const int& width, const int& height)
		: m_width(width)
		, m_height(height)
	{
	
	}
	
	void addShape(const Shape& s)
	{
		m_shapes.push_back(s);
	}
	
	const std::vector<Shape> getShapes() const
	{
		return m_shapes;
	}
	
	void loadFromFile(const std::string& filename)
	{
		std::string type;
		std::string name;
		int fontSize = 0;
		int posX; 
		int posY; 
		int speedX = 0; 
		int speedY = 0; 
		int red;
		int green;
		int blue;
		int width = 0; 
		int height = 0; 
		int radius = 0;
		int winWidth = 0; 
		int winHeight = 0;
		
		std::ifstream fin(filename);
		while (fin >> type)
		{	if (type.compare("Circle") == 0 || type.compare("Rectangle") == 0)
			{
				fin >> name >> posX >> posY >> speedX >> speedY >> red >> green >> blue;
				if (type.compare("Circle") == 0)
					fin >> radius;
				else if (type.compare("Rectangle") == 0)
					fin >> width >> height;
				addShape(Shape(type, name, posX, posY, speedX, speedY, red, green, blue, width, height, radius));
			}
			else
			{
				if (type.compare("Window") == 0)
				{
					fin >> winWidth >> winHeight;
					std::cout << "Windows Settings --> Width = " << winWidth << "  Height = " << winHeight << "\n";
					m_width = winWidth;
					m_height = winHeight;
				}
				else if (type.compare("Font") == 0)
				{
					fin >> name >> fontSize >> red >> green >> blue;
					std::cout << "Font Name = " << name << "\n";
				}
			}
		}
	}
	
	int getWinWidth()
	{
		return m_width;
	}
	
	int getWinHeight()
	{
		return m_height;
	}
	
	void print()
	{
		for (auto& s : m_shapes)
		{
			s.print();
		}
	}
};

int main()
{
	
	Scene scene;
	std::vector<Shape> shapes;
	sf::CircleShape circle;
	std::vector<sf::CircleShape> circles;
	int wWidth = 1280;
	int wHeight = 720;
	std::string type;
	int i = 0;
	
	scene.loadFromFile("config.txt"); 
	
	shapes = scene.getShapes();
	int arraySize = std::size(shapes);
	int circlesSize;
	
	wWidth = scene.getWinWidth();
	wHeight = scene.getWinHeight();
	std::cout << "width read = " << wWidth << "\n";
	std::cout << "height read = " << wHeight << "\n";
	
	while (i < arraySize)
	{
		std::cout << "Shape = " << shapes[i].getType() << "\n";
		i++;
	}
	std::cout << "array size = " << arraySize << "\n";
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
	window.setFramerateLimit(60);
	
	if (!ImGui::SFML::Init(window))
		return -1;
	sf::Clock deltaClock;
	
	ImGui::GetStyle().ScaleAllSizes(1.0f);

	float c[3] = { shapes[0].getRedRGB() / 255.0f, shapes[0].getGreenRGB() / 255.0f, shapes[0].getBlueRGB() / 255.0f };
	
	int radius = shapes[0].getRadius(); 
	int segments = 32; 
	int speedX = shapes[0].getSpeedX(); 
	int speedY = shapes[0].getSpeedY();
	bool draw = true;
	bool drawText = true;
	int item_current_idx = 0;
	std::string shapeName = shapes[0].getName();
	
	const char *figures[]
	{
		"Circle", 
		"Rectangle",
		"Square"
	};
	
	int selected = 0;
	
	i = 0;
	while (i < arraySize)
	{
		if (shapes[i].getType().compare("Circle") == 0)
		{
			circle.setRadius(shapes[i].getRadius());
			circle.setPointCount(segments);
			circle.setPosition(shapes[i].getPosX(), shapes[i].getPosY());
			circle.setFillColor(sf::Color(shapes[i].getRedRGB(), shapes[i].getGreenRGB(), shapes[i].getBlueRGB()));
			
			circles.push_back(circle);
		}
		i++;
	}
	circlesSize = std::size(circles);
	std::cout << "number of circles = " << circlesSize << "\n";
	//sf::CircleShape circle(radius, segments); 
		
	//circle.setPosition(shapes[0].getPosX(), shapes[0].getPosY()); 
	
	
	sf::Font myFont; 
	
	if (!myFont.loadFromFile("fonts/tech.ttf"))
	{
		std::cerr << "Could not load font!\n"; 
		exit(-1);
	}
	
	sf::Text text("Sample Text", myFont, 24);
	
	text.setPosition(0, wHeight - (float)text.getCharacterSize());
	
	
	char displayString[255] = "Sample Text"; 


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(window, event);
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				std::cout << "Key pressed with code = " << event.key.code << "\n";
				
				if (event.key.code == sf::Keyboard::X)
				{
					speedX *= -1.0f;
				}
			}
		}
		
		ImGui::SFML::Update(window, deltaClock.restart()); 
		
		ImGui::Begin("Shapes settings"); 
		ImGui::Text("Shape Selector"); 
		if (ImGui::BeginCombo("Shape", figures[item_current_idx], 0))
		{
		    for (int n = 0; n < 3; n++)
		    {
			if (ImGui::Selectable(figures[n]))
			    item_current_idx = n;
		    }
		    ImGui::EndCombo();
		}
		ImGui::Checkbox("Draw Shape", &draw);
		ImGui::SliderInt("Size", &radius, 10, 100);
		ImGui::SliderInt("Speed X ", &speedX, 1, 10);
		ImGui::SliderInt("Speed Y", &speedY, 1, 10);
		ImGui::ColorEdit3("Shape Color", c);
		char *str = &shapeName[0];
		ImGui::InputText("Shape Name", str, 255);
		if (ImGui::Button("Set Text"))
		{
			text.setString(str);
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset Circle"))
		{
			circle.setPosition(0, 0);
		}
		ImGui::End();
		
		
		i = 0; 
		while (i < circlesSize)
		{
			//circles[i].setFillColor(sf::Color(circles[i].getFillColor())); 
			circles[i].setPointCount(segments);
			circles[i].setRadius(radius);
			circles[i].setPosition(circles[i].getPosition().x + speedX, circles[i].getPosition().y + speedY);
			//window.draw(circles[i]);
			i++;
		}
		//circle.setFillColor(sf::Color(c[0]*255, c[1]*255, c[2]*255)); 
		//circle.setPointCount(segments);
		//circle.setRadius(radius);
		//circle.setPosition(circle.getPosition().x + speedX, circle.getPosition().y + speedY);
		window.clear();
		if (draw)
		{
			i = 0; 
			while (i < circlesSize)
				window.draw(circles[i++]);
		}
		if (drawText)
		{
			window.draw(text);
		}
		ImGui::SFML::Render(window);
		window.display();
		
		
	}
	ImGui::SFML::Shutdown();
	return 0;
}
