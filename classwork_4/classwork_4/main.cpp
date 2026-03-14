#include <iostream>
#include <functional>

enum class CardType {
	Additive, Multiplicative
};

class Hero;

class Card {
	union {
		int points;
		float mult;
	}value;

	CardType type;

	int damage;
	unsigned int armor;
public:
	Card() = default;
	Card(CardType type, int damage, unsigned int armor) :type(type), damage(damage), armor(armor) {
		if (type == CardType::Additive) {
			value.points = 5;
		}
		else {
			value.mult = 1.5;
		}
	}
	unsigned int getArmor() const{
		return this->armor;
	}

	void Play(Hero& h1, Hero& h2) const;
	void PlayAOE(Hero& h1, Hero heroes[], unsigned heroesCount) const;

	Card& operator=(Card& other) {
		if (this != &other) {
			this->armor = other.armor;
			this->value = other.value;
			this->type = other.type;
			this->damage = other.damage;
		}
		return *this;
	}
};
enum class HeroType {
	Aggressive, Passive, Merchant,Player
};

class Hero {
	HeroType type;
	char name[50];
	int health;
	int armor;

	const static int maxCardCount = 16;
	Card cards[maxCardCount];
	unsigned int cardCount;
	
	const static int maxModifierCount = 4;
	std::function<int(int)> modifiers[maxModifierCount];
	unsigned int modifierCount;
public:
	Hero(HeroType type, const char* name,Card cards[],unsigned cardCount, int health, int armor, std::function<int(int)>* modifiers,unsigned modifierCount):type(type),health(health),armor(armor) {
		if (cardCount > maxCardCount) {
			cardCount = maxCardCount;
		}
		if (modifierCount > maxModifierCount) {
			modifierCount = maxModifierCount;
		}
		this->modifierCount = modifierCount;
		strcpy(this->name,name);

		for (unsigned i = 0; i < cardCount; i++) {
			this->cards[i] = cards[i];
		}
		for (unsigned i = 0; i < modifierCount; i++) {
			this->modifiers[i] = modifiers[i];
		}
	}
	unsigned getModifierCount() const{
		return this->modifierCount;
	}
	std::function<int(int)> getModifier(unsigned index) const{
		if (index >= modifierCount)
		{
			std::cerr << "Invalid index";
			std::exit(1);
		}
		return this->modifiers[index];
	}
	void healPoints(int armor) {
		this->armor += armor;
	}
	int getArmor() const{
		return this->armor;
	}
	int getHealth()const {
		return this->health;
	}
	void dealDamage(int damage) {
		if (this->armor < damage) {
			damage -= this->armor;
			this->armor = 0;
			if (this->health < damage) {
				this->health = 0;
				std::cout << "I'm dead" << std::endl;
			}
			else {
				this->health -= damage;
			}
		}
		else {
			this->armor -= damage;
		}
	}

};

void Card::Play(Hero&h1,Hero&h2) const{
	h1.healPoints(this->armor);

	int damage = this->damage;
	int modCount = h1.getModifierCount();

	for (int i = 0; i < modCount; i++) {
		damage = h1.getModifier(i)(damage);
	}

	if (this->type == CardType::Additive) {
		damage += this->value.points;
	}
	else if (this->type == CardType::Multiplicative) {
		damage = (int)damage * this->value.mult;
	}
	h2.dealDamage(damage);
}
void Card::PlayAOE(Hero& h1, Hero heroes[], unsigned heroesCount)const {
	for (unsigned i = 0; i < heroesCount; i++) {
		this->Play(h1, heroes[i]);
	}
}
int main() {
	Card c1(CardType::Additive, 12, 10), c2(CardType::Multiplicative,4,20);
	Card cards[] = {c1,c2};
	std::function<int(int)> modifiers[] = { [](int damage)->int {return damage + 5; },[](int damage)->int {return damage * 2; } };
	Hero h1(HeroType::Aggressive, "Lion", cards, 2, 100, 100, modifiers, 2), h2(HeroType::Passive,"Tree",cards,2,1000,100,modifiers,2);

	c1.Play(h1, h2);
	std::cout << "Hero 1 armor: " << h1.getArmor() << std::endl;
	std::cout << "Hero 2 armor: " << h2.getArmor() << std::endl;

	c2.Play(h2, h1);
	std::cout << "Hero 1 armor: " << h1.getArmor() << std::endl;
	std::cout << "Hero 2 armor: " << h2.getArmor() << std::endl;
}