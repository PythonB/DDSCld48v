#include <string>
#include <vector>

#ifndef DDSC_PLAYER_HPP_
#define DDSC_PLAYER_HPP_
namespace ddsc {
    namespace player {
        class player {
            private:
            std::string name;                               // Name player chosen
            short hp;                                       // Health points
            short ap;                                       // Actions per turn
            unsigned short dph;                             // Damage per hit
            unsigned char crit_chance;  // Player's crit (2x damage) chance
            short max_hp;                                   // Max Health points
            short max_ap;                                   // Max Action points
            public:
            friend void level_up(ddsc::player::player& player, unsigned char level);
            std::string get_name();                         // Return's player name
            short get_hp();
            short get_max_hp();
            unsigned short get_damage();
            unsigned char get_crit_chance();
            void set_hp(short value);                       // Set's new HP value
            short damage(unsigned short d);
            player(std::string n);
        };
        void level_up(ddsc::player::player& player, unsigned char level);
    }
}
#endif DDSC_PLAYER_HPP_