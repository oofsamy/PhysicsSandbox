#include "Engine.hpp"

void PhysicsObject::HandleClick(Vector2<float> MousePosition) {};
void PhysicsObject::Render(sf::RenderWindow& Window) {};

void PhysicsObject::Update(float DeltaTime)
{
	Vector2<float> Acceleration = m_Force / m_Mass; // Using formula a = F/m

	std::cout << m_Force.y << "=force, " << m_Mass << "=mass\n";

	this->m_Velocity = this->m_Velocity + (Acceleration * DeltaTime); // Using formula v = u + at
	this->m_Position = this->m_Position + this->m_Velocity * DeltaTime; // Using formula s = vt

	this->m_Force = { 0, 0 };
}

void PhysicsObject::ApplyForce(Vector2<float> Force)
{
	this->m_Force = this->m_Force + Force;
}

void SquareObject::HandleClick(Vector2<float> MousePosition)
{

}


void SquareObject::Update(float DeltaTime)
{
	PhysicsObject::Update(DeltaTime);

	std::cout << std::to_string(this->m_Position.y) << std::endl;

	this->m_Shape.setPosition(reinterpret_cast<sf::Vector2f&>(this->m_Position));
}

void SquareObject::Render(sf::RenderWindow& Window)
{
	Window.draw(this->m_Shape);
}

int main()
{
	EngineBase Engine({ 720, 720 }, "Physics Sandbox (A-LEVEL PROJECT)");
	SquareObject MySquare(5, false, 50, sf::Color(255, 0, 0));
	Engine.AddObject(&MySquare);
	Engine.Run();
}