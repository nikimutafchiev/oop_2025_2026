#include <iostream>
#include <vector>

class Building {
protected:
	float happiness;
	std::string name;
	
public:
	Building() = default;
	Building(std::string name, float happiness):name(name),happiness(happiness) {

	}
	virtual Building* copy()const = 0;
	float getHappiness()const {
		return happiness;
	}
	virtual float trigger_effect(float current_happiness)const = 0;
};
class Mayor {
	std::string name;
	float bonus;
public:
	Mayor(std::string name,float bonus):name(name),bonus(bonus) {

	}
	Mayor(Mayor& other) {
		name = other.name;
		bonus = other.bonus;
	}
	float influence(const Building** buildings, int num_buildings) {
		float infl = 0;
		for (unsigned i = 0; i < num_buildings; i++) {
			infl += buildings[i]->getHappiness();
		}
		for (unsigned i = 0; i < num_buildings; i++) {
			infl += buildings[i]->trigger_effect(infl);
		}
		return infl+bonus;
	};
};

class Municipality : public Building {
	Mayor* mayor;
	std::vector<Building*> buildings;

public:
	Municipality(Mayor* mayor) {
		this->mayor = new Mayor(*mayor);
	}
	Municipality(Mayor* mayor, const std::vector<Building*>& buildings) {
		this->mayor = new Mayor(*mayor);
		this->buildings = buildings;
	}
	Municipality* copy() const override
	{
		return new Municipality(mayor, buildings);
	}
	float calculate_happiness() {
		size_t size = buildings.size();
		int happiness = mayor->influence(buildings.data(), size);
		for (unsigned i = 0; i < size; i++) {
			happiness += buildings[i]->trigger_effect(happiness);
		}
		return happiness;
	}
	void add_building(const Building& building) {
		buildings.push_back(building.copy());
	}
	float trigger_effect(float current_happiness)const override {
		return current_happiness;
	}
};
class City {
	std::string name;
	std::vector<Municipality*> municipalities;
public:
	void add_municipality(const Municipality& municipality) {
		municipalities.push_back(municipality.copy());
	}
	float calculate_total_happiness() {
		float total_happiness = 0;
		for (Municipality* m : municipalities) {
			total_happiness += m->calculate_happiness();
		}
		return total_happiness;
	}
};

class Park : public Building {
public:
	Park(std::string name) :Building(name, 10) {

	}
	Park* copy() const override{
		return new Park(name);
	}
	float trigger_effect(float current_happiness)const {
		return 1.1 * current_happiness;
	}
};
class School : public Building {
public:
	School(std::string name) :Building(name, 20) {

	}
	School* copy() const override {
		return new School(name);
	}
	float trigger_effect(float current_happiness)const {
		return 1.2 * current_happiness;
	}
};
class Hospital : public Building {
public:
	Hospital(std::string name) : Building(name, 30) {

	}
	Hospital* copy() const override {
		return new Hospital(name);
	}
	float trigger_effect(float current_happiness)const {
		return 1.3 * current_happiness;
	}
};
class BusinessPark : public Building {
public:
	BusinessPark(std::string name) : Building(name, -30) {

	}
	BusinessPark* copy() const override {
		return new BusinessPark(name);
	}
	float trigger_effect(float current_happiness)const {
		return 1.25;
	}
};

int main() {
	Mayor m1("Mamdani", 5),m2("Terziev",5),m3("GhettoMan",-15);
}