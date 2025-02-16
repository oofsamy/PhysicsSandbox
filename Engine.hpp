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
	PhysicsObject(float Mass, bool Anchored) : m_Mass(Mass), m_Anchored(Anchored) {};

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

	// Custom functions

	void ApplyForce(Vector2<float> Force);

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
		for (PhysicsObject* Object : this->m_Objects)
		{
			if (Object->GetAnchored() == false)
			{
				Object->ApplyForce(this->m_Gravity * Object->GetMass()); // Apply gravity if unanchored
			}

			Object->Update(DeltaTime);
		}
	}

	void Render()
	{
		this->m_Window.clear(sf::Color::Black);
		
		for (PhysicsObject* Object : this->m_Objects)
		{
			std::cout << "render object\n";

			Object->Render(this->m_Window);
		}

		this->m_Window.display();
	}
};
