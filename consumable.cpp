#include "consumable.hh"

Consumable::Consumable() {}
Consumable::~Consumable() {}

Effect Consumable::getEffect() {
    return effect_;
}
