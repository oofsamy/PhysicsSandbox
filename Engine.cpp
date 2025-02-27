#include "Engine.hpp"

void PhysicsObject::HandleClick(Vector2<float> MousePosition) {};
void PhysicsObject::Render(sf::RenderWindow& Window) {};

void PhysicsObject::Update(float DeltaTime)
{
	Vector2<float> Acceleration = m_Force / m_Mass; // Using formula a = F/m

	this->m_Velocity = this->m_Velocity + (Acceleration * DeltaTime); // Using formula v = u + at
	this->m_Position = this->m_Position + this->m_Velocity * DeltaTime; // Using formula s = vt

	this->m_Force = { 0, 0 };
}

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
	if (SquareObject* Square = dynamic_cast<SquareObject*>(&OtherObject))
	{
		return (this->m_Position.x < Square->GetPosition().x + Square->GetLength() &&
				this->m_Position.x + this->m_Size.x > Square->GetPosition().x &&
				this->m_Position.y < Square->GetPosition().y + Square->GetLength() &&
				this->m_Position.y + this->m_Size.y > Square->GetPosition().y);
	}

	if (RectangleObject* Rectangle = dynamic_cast<RectangleObject*>(&OtherObject))
	{
		return (this->m_Position.x < Rectangle->GetPosition().x + Rectangle->GetSize().x &&
				this->m_Position.x + this->m_Size.x > Rectangle->GetPosition().x &&
				this->m_Position.y < Rectangle->GetPosition().y + Rectangle->GetSize().y &&
				this->m_Position.y + this->m_Size.y > Rectangle->GetPosition().y);
	}

	return false;
}

void RectangleObject::ResolveCollision(PhysicsObject& OtherObject)
{
    Vector2<float> CollisionNormal;
    if (RectangleObject* Rectangle = dynamic_cast<RectangleObject*>(&OtherObject))
    {
        Vector2<float> rectPos = Rectangle->GetPosition();
        float OverlapX = std::min(this->m_Position.x + this->m_Size.x, rectPos.x + Rectangle->GetSize().x) - std::max(this->m_Position.x, rectPos.x);
        float OverlapY = std::min(this->m_Position.y + this->m_Size.y, rectPos.y + Rectangle->GetSize().y) - std::max(this->m_Position.y, rectPos.y);
        if (OverlapX < OverlapY)
            CollisionNormal = (this->m_Position.x < rectPos.x) ? Vector2<float>{-1, 0} : Vector2<float>{ 1, 0 };
        else
            CollisionNormal = (this->m_Position.y < rectPos.y) ? Vector2<float>{0, -1} : Vector2<float>{ 0, 1 };

        Vector2<float> RelativeVelocity = this->m_Velocity - OtherObject.GetVelocity();
        float ImpactSpeed = Vector2<float>::DotProduct(RelativeVelocity, CollisionNormal);
        if (ImpactSpeed < 0)
        {
            float RestitutionConstant = 1.0f;
            float ImpulseMagnitude = -(1 + RestitutionConstant) * ImpactSpeed;
            Vector2<float> Impulse = CollisionNormal * ImpulseMagnitude;
            if (!this->GetAnchored())
                this->m_Velocity = this->m_Velocity + (Impulse * (1 / this->m_Mass));
            if (!OtherObject.GetAnchored())
            {
                Vector2<float> OtherVelocity = OtherObject.GetVelocity();
                OtherVelocity = OtherVelocity - (Impulse * (1 / OtherObject.GetMass()));
                OtherObject.SetVelocity(OtherVelocity);
            }
        }

        if (OverlapX < OverlapY)
        {
            if (!this->GetAnchored() && !Rectangle->GetAnchored())
            {
                this->m_Position.x += (this->m_Position.x < rectPos.x ? -OverlapX / 2.0f : OverlapX / 2.0f);
                rectPos.x += (this->m_Position.x < rectPos.x ? OverlapX / 2.0f : -OverlapX / 2.0f);
                Rectangle->SetPosition(rectPos);
            }
            else if (!this->GetAnchored() && Rectangle->GetAnchored())
                this->m_Position.x += (this->m_Position.x < rectPos.x ? -OverlapX : OverlapX);
            else if (this->GetAnchored() && !Rectangle->GetAnchored())
            {
                rectPos.x += (this->m_Position.x < rectPos.x ? OverlapX : -OverlapX);
                Rectangle->SetPosition(rectPos);
            }
        }
        else
        {
            if (!this->GetAnchored() && !Rectangle->GetAnchored())
            {
                this->m_Position.y += (this->m_Position.y < rectPos.y ? -OverlapY / 2.0f : OverlapY / 2.0f);
                rectPos.y += (this->m_Position.y < rectPos.y ? OverlapY / 2.0f : -OverlapY / 2.0f);
                Rectangle->SetPosition(rectPos);
            }
            else if (!this->GetAnchored() && Rectangle->GetAnchored())
                this->m_Position.y += (this->m_Position.y < rectPos.y ? -OverlapY : OverlapY);
            else if (this->GetAnchored() && !Rectangle->GetAnchored())
            {
                rectPos.y += (this->m_Position.y < rectPos.y ? OverlapY : -OverlapY);
                Rectangle->SetPosition(rectPos);
            }
        }
    }
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

void SquareObject::ResolveCollision(PhysicsObject& OtherObject)
{

}

int main()
{
	EngineBase Engine({ 720, 720 }, "Physics Sandbox (A-LEVEL PROJECT)");
	//SquareObject MySquare(5, false, 50, sf::Color(255, 0, 0));
	//MySquare.SetPosition({ 335, 100 });
	//Engine.AddObject(&MySquare);

	RectangleObject MyRectangle(5, false, {100, 50}, sf::Color(255, 0, 0));

	RectangleObject Ground(1000, true, { 500, 100 }, sf::Color(255, 255, 0));

	MyRectangle.SetPosition({ 335, 100 });
	
	Ground.SetPosition({ 100, 500 });

    MyRectangle.SetVelocity({ 0, 100 });

	Engine.AddObject(&MyRectangle);
	Engine.AddObject(&Ground);

	Engine.Run();
}