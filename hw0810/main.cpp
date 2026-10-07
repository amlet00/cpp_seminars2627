#include <functional>
#include <iostream>
#include <string>

struct Entity {
  std::string name;
  double armor;
  double magic_resist;
};

using DamageCounter = std::function<double(const double, const Entity&)>;

const DamageCounter PhysicalDamageStrategy = [](const double damage, const Entity& entity) {
  return (1.0 - entity.armor) * damage;
};
const DamageCounter MagicDamageStrategy = [](const double damage, const Entity& entity) {
  return (1.0 - entity.magic_resist) * damage;
};
const DamageCounter TrueDamageStrategy = [](const double damage, const Entity& entity) {
  return damage;
};

int main() {
  const double damage {100.0};
  
  Entity goblin {"goblin", 0.3, 0};
  Entity warrior {"warrior", 0.7, 0.3};
  Entity dragon {"dragon", 0.6, 0.8};
  Entity elder_dragon {"elder_dragon", 1.0, 1.0};

  Entity entities[] {goblin, warrior, dragon, elder_dragon};

  for (const Entity& entity : entities) {
    std::cout << "физический урон по " << entity.name << ": " << PhysicalDamageStrategy(damage, entity) << '\n';
    std::cout << "магический урон по " << entity.name << ": " << MagicDamageStrategy(damage, entity) << '\n';
    std::cout << "чистый урон по " << entity.name << ": " << TrueDamageStrategy(damage, entity) << '\n';
  }
}