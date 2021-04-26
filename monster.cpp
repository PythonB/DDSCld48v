#include "monster.hpp"
#include "player.hpp"
#include <string>
#include <vector>

unsigned short ddsc::monster::monster::get_damage(){
    return damage;
}
unsigned short ddsc::monster::monster::get_bounty(){
    return bounty;
}
short ddsc::monster::monster::get_hp(){
    return hp;
}
short ddsc::monster::monster::get_max_hp(){
    return max_hp;
}
ddsc::monster::monster::monster(){
    name = "Empty monster";
    damage = 0;
    max_hp = 1;
    hp = max_hp;
}
ddsc::monster::monster::monster(std::string n, short m, unsigned short d, unsigned short b, std::string ip){
    name = n;
    icon = ip;
    max_hp = m;
    hp = max_hp;
    damage = d;
    bounty = b;
}

void ddsc::monster::autolevel(ddsc::monster::monster &target, unsigned short level){
    target.name = target.name;
    target.icon = target.icon;
    target.max_hp = target.max_hp*((0.5*level)+1)*level;
    target.hp = target.max_hp;
    target.bounty = target.bounty*((0.5*level)+1)*level;
    target.damage = target.damage*floor((level/2)+0.5);
}
short ddsc::monster::damage_monster(ddsc::monster::monster& monster, unsigned short d){
    short player_damage = d;
    char luck = rand()%100;
    if(luck <= 2){ // Crit fail. 0.5 Damage
        player_damage = d*0.5;
    } else if(luck >= 95){ // Crit success
        player_damage = d*2;
    }
    monster.hp = monster.hp-player_damage;
    return player_damage;
}