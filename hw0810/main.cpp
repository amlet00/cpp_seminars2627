#include <functional>
#include <iostream>
#include <random>
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

DamageCounter DoubleDamage(const DamageCounter& damage_counter) {
  return [damage_counter](const double damage, const Entity& entity) {
    return damage_counter(2.0 * damage, entity);
  };
}

DamageCounter CriticalDamage(const DamageCounter& damage_counter, const double chance = 0.3, const double multiplier = 2.5) {
  return [damage_counter, chance, multiplier](const double damage, const Entity& entity) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::bernoulli_distribution d(chance);
    
    if (d(gen)) {
      return damage_counter(multiplier * damage, entity);
    }
    return damage_counter(damage, entity);
  };
}

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

  DamageCounter DoublePhysicalDamageStrategy {DoubleDamage(PhysicalDamageStrategy)};
  DamageCounter CriticalMagicDamageStrategy {CriticalDamage(MagicDamageStrategy)};
  DamageCounter OneHunderedPercentChanceX100CriticalTrueDamageStrategy 
    {CriticalDamage(TrueDamageStrategy, 1.0, 100.0)};

  for (const Entity& entity : entities) {
    std::cout << "двойной физический урон по " << entity.name << ": " << 
      DoublePhysicalDamageStrategy(damage, entity) << '\n';
    std::cout << "критический магический урон по " << entity.name << ": " << 
      CriticalMagicDamageStrategy(damage, entity) << '\n';
    std::cout << "стопроцентный X100 критический чистый урон по " << entity.name << ": " 
      << OneHunderedPercentChanceX100CriticalTrueDamageStrategy(damage, entity) << '\n';
  }
}