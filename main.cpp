#include <iostream> 
#include <memory>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "imgui/imgui.h"
#include "imgui_sfml/imgui-SFML.h"


int main (int argc, char *argv[])
{
	
	const int wWidth = 1280;
	const int wHeight = 720;
	
	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "My window");
	
	window.setFramerateLimit(60);
	
	if (!ImGui::SFML::Init(window)) return -1;
	sf::Clock deltaClock;
	
	//scale imgui UI (no text)
	ImGui::GetStyle().ScaleAllSizes(1.0f);

	float c[3] = { 0.0f, 1.0f, 1.0f };
	
	float circleRadius = 50; 
	int circleSegments = 32; 
	float circleSpeedX = 1.0f; 
	float circleSpeedY = 0.5f; 
	bool drawCircle = true;
	bool drawText = true;
	
	
	
	sf::CircleShape circle(circleRadius, circleSegments); 
	
	circle.setPosition(100.0f, 100.0f); 
	
	sf::Font myFont; 
	
	if (!myFont.loadFromFile("fonts/tech.ttf"))
	{
		std::cerr << "Could not load font!\n"; 
		exit(-1);
	}
	
	sf::Text text("Sample Text", myFont, 24);
	
	text.setPosition(0, wHeight - (float)text.getCharacterSize());
	
	
	char displayString[255] = "Sample Text"; 
	// run the program as long as the window is open
	while (window.isOpen())
	{
	// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(window, event);
			// "close requested" event: we close the window
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
		ImGui::Checkbox("Draw Circle", &drawCircle);
		ImGui::SameLine();
		ImGui::Checkbox("Draw Text", &drawText);
		ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
		ImGui::SliderInt("Sides", &circleSegments, 3, 64);
		ImGui::ColorEdit3("Color Circle", c);
		ImGui::InputText("Text", displayString, 255);
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
		
	}

	return 0;
}

