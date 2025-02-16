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

bool PhysicsObject::CheckCollision(PhysicsObject& OtherObject) { return false; };

void PhysicsObject::ApplyForce(Vector2<float> Force)
{
	this->m_Force = this->m_Force + Force;
}

void RectangleObject::HandleClick(Vector2<float> MousePosition)
{

}

void RectangleObject::Update(float DeltaTime)
{
	PhysicsObject::Update(DeltaTime);

	this->m_Shape.setPosition(reinterpret_cast<sf::Vector2f&>(this->m_Position));
}

void RectangleObject::Render(sf::RenderWindow& Window)
{
	Window.draw(this->m_Shape);
}

bool RectangleObject::CheckCollision(PhysicsObject& OtherObject)
{
	SquareObject* Square = dynamic_cast<SquareObject*>(&OtherObject);

	if (Square)
	{
		return (this->m_Position.x < Square->GetPosition().x + Square->GetLength() &&
			this->m_Position.x + this->m_Size.x > Square->GetPosition().x &&
			this->m_Position.y < Square->GetPosition().y + Square->GetLength() &&
			this->m_Position.y + this->m_Size.y > Square->GetPosition().y);
	}

	RectangleObject* Rectangle = dynamic_cast<RectangleObject*>(&OtherObject);

	if (Rectangle)
	{
		
	}

	return false;
}

void SquareObject::HandleClick(Vector2<float> MousePosition)
{

}

void SquareObject::Update(float DeltaTime)
{
	PhysicsObject::Update(DeltaTime);

	this->m_Shape.setPosition(reinterpret_cast<sf::Vector2f&>(this->m_Position));
}

void SquareObject::Render(sf::RenderWindow& Window)
{
	Window.draw(this->m_Shape);
}

bool SquareObject::CheckCollision(PhysicsObject& OtherObject)
{
	const SquareObject* Square = dynamic_cast<const SquareObject*>(&OtherObject);

	if (Square)
	{
		return (this->m_Position.x < Square->m_Position.x + Square->m_Length &&
				this->m_Position.x + this->m_Length > Square->m_Position.x &&
				this->m_Position.y < Square->m_Position.y + Square->m_Length &&
				this->m_Position.y + m_Length > Square->m_Position.y);
	}

	return false;
}

int main()
{
	EngineBase Engine({ 720, 720 }, "Physics Sandbox (A-LEVEL PROJECT)");
	SquareObject MySquare(5, false, 50, sf::Color(255, 0, 0));
	MySquare.SetPosition({ 335, 100 });
	Engine.AddObject(&MySquare);

	Engine.Run();
}