#include "player.hpp"
#include <string>
#include <vector>

#ifndef DDSC_MONSTER_HPP_
#define DDSC_MONSTER_HPP_

namespace ddsc {
    namespace monster {
        class monster {
            private:
            unsigned short damage;      // Damage it deals
            unsigned max_hp;            // Maximium hp it can have
            unsigned hp;                // Current hp
            unsigned short bounty;      // Amount of money player will get after killing it
            public:
            friend short damage_monster(ddsc::monster::monster& monster, unsigned short d);
            friend void autolevel(ddsc::monster::monster& target, unsigned short level);
            std::string name;           // Name
            std::string icon;
            unsigned short get_damage();
            unsigned short get_bounty();
            short get_hp();
            short get_max_hp();
            void set_hp(short value);
            monster();
            monster(std::string n, short m, unsigned short d, unsigned short b, std::string ip);
        };
        void autolevel(ddsc::monster::monster& target, unsigned short level);
        short damage_monster(ddsc::monster::monster& monster, unsigned short player);
    }
}

#endif