#include "player.hpp"
#include <string>
#include <vector>

// Player
std::string ddsc::player::player::get_name(){
    return name;
}
short ddsc::player::player::get_hp(){
    return hp;
}
short ddsc::player::player::get_max_hp(){
    return max_hp;
}
unsigned short ddsc::player::player::get_damage(){
    return dph;
}
unsigned char ddsc::player::player::get_crit_chance(){
    return crit_chance;
}
void ddsc::player::player::set_hp(short value){
    hp = value;
}
short ddsc::player::player::damage(unsigned short value){
    if(rand()%100 <= 10) {  // Dodge chance, only 0.5 damage taken
        hp -= value*0.5;
    } else {
        hp -= value;
    }
    return hp;
}
ddsc::player::player::player(std::string n){
    name = n;
    max_hp = 10;
    hp = max_hp;
    crit_chance = 5;
    dph = 5;
}
void ddsc::player::level_up(ddsc::player::player& player, unsigned char level){
    player.max_hp = 10*level;
    player.hp = player.max_hp;
    player.dph = 5*level;
}