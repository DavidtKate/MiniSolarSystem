#pragma once

#include "Objects/Planet.h"
#include <vector>

class PlanetManager
{
public:

	static PlanetManager& GetInstance()
	{ 
		static PlanetManager s_planetManager;
		return s_planetManager;
	}

	void AddPlanet(Planet* a_planet) { m_planets.push_back(a_planet); }
	const std::vector<Planet*> GetPlanets() const { return m_planets; }

private:

	PlanetManager() = default;
	~PlanetManager() = default;

	std::vector<Planet*> m_planets;
};