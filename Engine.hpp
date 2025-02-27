#pragma once
#include "EngineTypes.hpp"

class PhysicsObject
{
protected:
	float m_Mass;
	Vector2<float> m_Position;
	Vector2<float> m_Velocity;
	Vector2<float> m_Force;

	bool m_Anchored;

public:
	PhysicsObject(float Mass, bool Anchored) : m_Mass(Mass), m_Position({ 0,0 }), m_Velocity({ 0,0 }), m_Force({ 0,0 }), m_Anchored(Anchored) {};

public:
	// Getters
	float GetMass() { return this->m_Mass; }
	Vector2<float> GetPosition() { return this->m_Position; }
	Vector2<float> GetVelocity() { return this->m_Velocity; }
	Vector2<float> GetForce() { return this->m_Force; }
	bool GetAnchored() { return this->m_Anchored; }

	// Setters
	void SetMass(float Mass) { this->m_Mass = Mass; }
	void SetPosition(Vector2<float> Position) { this->m_Position = Position; }
	void SetVelocity(Vector2<float> Velocity) { this->m_Velocity = Velocity; }
	void SetForce(Vector2<float> Force) { this->m_Force = Force; }
	void SetAnchored(bool Anchored) { this->m_Anchored = Anchored; };

	// Base functions
	virtual void HandleClick(Vector2<float> MousePosition);
	virtual void Update(float DeltaTime);
	virtual void Render(sf::RenderWindow& Window);
	virtual bool CheckCollision(PhysicsObject& OtherObject) = 0;
	virtual void ResolveCollision(PhysicsObject& OtherObject) = 0;

	// Custom functions

	void ApplyForce(Vector2<float> Force);

};

class RectangleObject : public PhysicsObject
{
protected:
	Vector2<float> m_Size;
	sf::Color m_Color;
	sf::RectangleShape m_Shape;

public:
	RectangleObject(float Mass, bool Anchored, Vector2<float> Size, sf::Color Color) : m_Size(Size), m_Color(Color), PhysicsObject(Mass, Anchored)
	{
		this->m_Shape = sf::RectangleShape(reinterpret_cast<sf::Vector2f&>(Size));
		this->m_Shape.setFillColor(Color);
	}

public:
	//Getters
	Vector2<float> GetSize() { return this->m_Size; }
	sf::Color GetColor() { return this->m_Color; }

	//Setters
	void SetSize(Vector2<float> Size) { this->m_Size = Size; }
	void SetColor(sf::Color Color) { this->m_Color = Color; }

public:
	void HandleClick(Vector2<float> MousePosition) override;
	void Update(float DoubleTime) override;
	void Render(sf::RenderWindow& Window) override;
	bool CheckCollision(PhysicsObject& OtherObject) override;
	void ResolveCollision(PhysicsObject& OtherObject) override;

};

class SquareObject : public PhysicsObject
{
protected:
	float m_Length;
	sf::Color m_Color;
	sf::RectangleShape m_Shape;

public:
	SquareObject(float Mass, bool Anchored, float Length, sf::Color Color) : m_Length(Length), m_Color(Color), PhysicsObject(Mass, Anchored)
	{
		this->m_Shape = sf::RectangleShape({ m_Length, m_Length });
		this->m_Shape.setFillColor(Color);
	};

public:
	//Getters
	float GetLength() { return this->m_Length; }
	sf::Color GetColor() { return this->m_Color; }

	//Setters
	void SetLength(float Length) { this->m_Length = Length; }
	void SetColor(sf::Color Color) { this->m_Color = Color; }

public:
	void HandleClick(Vector2<float> MousePosition) override;
	void Update(float DoubleTime) override;
	void Render(sf::RenderWindow& Window) override;
	bool CheckCollision(PhysicsObject& OtherObject) override;
	void ResolveCollision(PhysicsObject& OtherObject) override;
};

class GraphicsObject
{
protected:
	Vector2<float> m_Position;

};

class EngineBase
{
private:
	sf::RenderWindow m_Window;
	sf::Clock m_Clock;
	sf::Color m_Background;
	bool m_Running;

private:
	std::vector<PhysicsObject*> m_Objects;
	Vector2<float> m_Gravity;

public:
	EngineBase(Vector2<unsigned int> Resolution, const std::string& Title) : m_Window(sf::VideoMode({ Resolution.x, Resolution.y }), Title), m_Gravity({ 0, GRAVITATIONAL_CONSTANT })
	{
		this->m_Running = true;
		this->m_Background = sf::Color();
	}

	void AddObject(PhysicsObject* Object)
	{
		m_Objects.push_back(Object);
	}

	void Run()
	{
		while (this->m_Running && this->m_Window.isOpen())
		{
			float DeltaTime = this->m_Clock.restart().asSeconds();
			
			this->HandleEvents();
			this->Update(DeltaTime);
			this->Render();
		}
	}

private:
	void HandleEvents()
	{
		while (const std::optional<sf::Event> Event = this->m_Window.pollEvent())
		{
			if (Event->is<sf::Event::Closed>())
			{
				this->m_Running = false;
				this->m_Window.close();
			}
			else if (Event->is<sf::Event::MouseButtonPressed>())
			{
				// Mouse button pressed
			}
		}
	}

	void Update(float DeltaTime)
	{
		for (size_t i = 0; i < this->m_Objects.size(); i++)
		{
			if (this->m_Objects[i]->GetAnchored() == false)
			{
				//this->m_Objects[i]->ApplyForce(this->m_Gravity * this->m_Objects[i]->GetMass());
			}

			for (size_t j = i + 1; j < this->m_Objects.size(); j++)
			{
				if (this->m_Objects[i]->CheckCollision(*this->m_Objects[j]))
				{
					this->m_Objects[i]->ResolveCollision(*this->m_Objects[j]);
				}
			}

			this->m_Objects[i]->Update(DeltaTime);
		}
	}

	void Render()
	{
		this->m_Window.clear(sf::Color::Black);
		
		for (PhysicsObject* Object : this->m_Objects)
		{
			Object->Render(this->m_Window);
		}

		this->m_Window.display();
	}
};
