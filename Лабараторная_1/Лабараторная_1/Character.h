#include <iostream>
#include <string>



class Character
{
	private:
		std::string name;
		int health;
		int attack;
		int defense;
		int const maxHealth;

	public:
		Character(const std::string& n, int h, int a, int d) :
			name(n),
			health(h),
			attack(a),
			defense( d ),
			maxHealth(h){}
		
		int getHealth() const{
			return health;
		}

		void displayInfo() {
			std::cout << "Name: " << name << ", HP: " << health
				<< ", Attack: " << attack << ", Defense: " << defense << std::endl;
		}

		void attackEnemy(Character& enemy) {
			int damage = attack - enemy.defense;
			if (damage > 0) {
				enemy.health -= damage;
				std::cout << name << " attacks " << enemy.name << " for " << damage << " damage!" << std::endl;
			}
			else {
				std::cout << name << " attacks " << enemy.name << ", but it has no effect!" << std::endl;
			}
		}

		int heal(int amount) {
			health += amount;
			if (health > maxHealth) {
				health = maxHealth;
				return health;
			}
			else if (health < maxHealth)
				return health;
		}

		int takeDamage(int amount) {
			health -= amount;
			if (health >= 0) {
				return health;
			}

			else if (health < 0) {
				health = 0;
				return health;
			}
		}
};