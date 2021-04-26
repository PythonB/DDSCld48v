#include "item.hpp"
#include <string>
#include <vector>

// Basic item
ddsc::item::basic_item::basic_item(){
    name = "Empty item";
    icon = "";
    cost = 0;
}
ddsc::item::basic_item::basic_item(std::string n, std::string i, unsigned short c){
    name = n;
    icon = i;
    cost = c;
}

// Weapon
ddsc::item::weapon::weapon(){
    name = "Empty weapon";
    icon = "";
    cost = 0;
    damage = 0;
    upgrade_level = 0;
}
ddsc::item::weapon::weapon(std::string n, std::string i, unsigned short c, unsigned short d, unsigned char ul){
    name = n;
    icon = i;
    cost = c;
    damage = d;
    upgrade_level = ul;
}
// Armor
unsigned char ddsc::item::armor::get_armor_points(){
    return armor_points;
}
unsigned char ddsc::item::armor::get_upgrade_level(){
    return upgrade_level;
}
unsigned char ddsc::item::armor::get_str_bonus(){
    return str_bonus;
}
unsigned char ddsc::item::armor::get_dex_bonus(){
    return dex_bonus;
}
ddsc::item::armor::armor(){
    name = "Empty armor";
    icon = "";
    cost = 0;
    armor_points = 0;
    upgrade_level = 0;
    str_bonus = 0;
    dex_bonus = 0;
}
ddsc::item::armor::armor(std::string n, std::string i, unsigned short c, unsigned char ap, unsigned char ul, unsigned char s, unsigned char d){
    name = n;
    icon = i;
    cost = c;
    armor_points = ap;
    upgrade_level = ul;
    str_bonus = s;
    dex_bonus = d;
}

// Scroll
/*ddsc::item::scroll::scroll(){
    name = "Empty scroll";
    icon = "";
    cost = 0;
}*/