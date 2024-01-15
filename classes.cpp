#include <iostream>
#include <fstream>
#include <vector>
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

int main (int argc, char *argv[])
{
	Scene scene01;
	
	
	scene01.loadFromFile("config.txt");
	scene01.print();
}
