#include <functional>
#include <string>

struct Entity {
  std::string name;
  double armor;
  double magic_resist;
};

using DamageCounter = std::function<double(const double, const Entity&)>;

int main() {
  const double damage {100.0};
  
  Entity goblin {"goblin", 0.3, 0};
  Entity warrior {"warrior", 0.7, 0.3};
  Entity dragon {"dragon", 0.6, 0.8};
  Entity elder_dragon {"elder_dragon", 1.0, 1.0};

  Entity entities[] {goblin, warrior, dragon, elder_dragon};
}