#include <iostream>
#include <fstream>
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
	
	const std::vector<Shape> getShape() const
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
				}
				else if (type.compare("Font") == 0)
				{
					fin >> name >> fontSize >> red >> green >> blue;
					std::cout << "Font Name = " << name << "\n";
				}
			}
		}
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
	const int wWidth = 1280;
	const int wHeight = 720;
	
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
	window.setFramerateLimit(60);
	
	if (!ImGui::SFML::Init(window))
		return -1;
	sf::Clock deltaClock;
	
	ImGui::GetStyle().ScaleAllSizes(1.0f);
	
	float c[3] = { 0.0f, 1.0f, 1.0f };
	
	float circleRadius = 10; 
	int circleSegments = 32; 
	float circleSpeedX = 1.0f; 
	float circleSpeedY = 0.5f; 
	float shapeSpeed = 1.0f;
	bool drawCircle = true;
	bool drawText = true;
	int item_current_idx = 0;
	
	const char *figures[]
	{
		"Circle", 
		"Rectangle",
		"Square"
	};
	
	int selected = 0;
	
	sf::CircleShape circle(circleRadius, circleSegments); 
		
	circle.setPosition(10.0f, 10.0f); 
	
	
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
					circleSpeedX *= -1.0f;
				}
			}
		}
		
		ImGui::SFML::Update(window, deltaClock.restart()); 
		
		ImGui::Begin("Window Title"); 
		ImGui::Text("Window Text!"); 
		if (ImGui::BeginCombo("Shape", figures[item_current_idx], 0))
		{
		    for (int n = 0; n < 3; n++)
		    {
			if (ImGui::Selectable(figures[n]))
			    item_current_idx = n;
		    }
		    ImGui::EndCombo();
		}
		ImGui::Checkbox("Draw Shape", &drawCircle);
		ImGui::SliderFloat("Size", &circleRadius, 10.0f, 100.0f);
		ImGui::SliderFloat("Speed X ", &circleSpeedX, 1.0f, 10.0f);
		ImGui::SliderFloat("Speed Y", &circleSpeedY, 1.0f, 10.0f);
		ImGui::ColorEdit3("Shape Color", c);
		ImGui::InputText("Shape Name", displayString, 255);
		if (ImGui::Button("Set Text"))
		{
			text.setString(displayString);
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset Circle"))
		{
			circle.setPosition(0, 0);
		}
		ImGui::End();
		
		circle.setFillColor(sf::Color::Blue); 
		circle.setPointCount(circleSegments);
		circle.setRadius(circleRadius);
		circle.setPosition(circle.getPosition().x + circleSpeedX, circle.getPosition().y + circleSpeedY);
		window.clear();
		if (drawCircle)
		{
			window.draw(circle);
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
