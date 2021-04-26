#include <string>
#include <vector>

#ifndef DDSC_ITEM_HPP_
#define DDSC_ITEM_HPP_
namespace ddsc {
    namespace item {
        class basic_item {
            private:
            std::string name;           // Up to 32 characters (33 if \0 included)
            std::string icon;           // Icon path
            unsigned short cost;        // Base Cost when sold to traders (cost of purchase is 1.2*cost)
            public:
            std::string get_name();
            basic_item();
            basic_item(std::string n, std::string i, unsigned short c);
        };
        class weapon {
            private:
            std::string name;               // Up to 32 characters (33 if \0 included)
            std::string icon;               // Icon path
            unsigned short cost;            // Base Cost when sold to traders (cost of purchase is 1.2*cost)
            unsigned short damage;          // Because I do not neeed "Asian MMO"-like 472k of damage in one hit)
            unsigned char upgrade_level;    // Blacksmith's upgrade level (+1 per level, no more then 10 times)
            public:

            unsigned int get_damage();      // Calculate damage and return it. U_INT to prevent overflow
            weapon();
            weapon(std::string n, std::string i, unsigned short c, unsigned short d, unsigned char ul);
        };
        //enum armor_slots {HEAD, TORSO, GLOVES, LEGS};
        class armor {
            private:
            std::string name;               // Up to 32 characters (33 if \0 included)
            std::string icon;               // Icon path
            unsigned short cost;            // Base Cost when sold to traders (cost of purchase is 1.2*cost)
            unsigned char armor_points;         // How much AP it adds
            unsigned char upgrade_level;        // Additional AP per level
            unsigned char str_bonus;            // Bonus to wearer's strength
            unsigned char dex_bonus;            // Bonus to wearer's dexterity
            public:
            //armor_slots target_slot;
            unsigned char get_armor_points();   // Return AP
            unsigned char get_upgrade_level();  // Returns upgrade level
            unsigned char get_str_bonus();      // Returns dexterity bonus
            unsigned char get_dex_bonus();      // Returns strength bonus 
            armor();
            armor(std::string n, std::string i, unsigned short c, unsigned char ap, unsigned char ul, unsigned char s, unsigned char d);

        };
        /*class scroll : basic_item {     // Spells, but for non-mages
            private:
            std::string name;           // Up to 32 characters (33 if \0 included)
            std::string icon;           // Icon path
            unsigned short cost;        // Base Cost when sold to traders (cost of purchase is 1.2*cost)
            ddsc::magic::spell effect;  // Spell to be used
            unsigned char uses;         // Times it can be used
            public:
            scroll();
            scroll(std::string n, std::string i, unsigned short c, ddsc::magic::spell e, unsigned char u);
        };*/
    }

}
#endif DDSC_ITEM_HPP_