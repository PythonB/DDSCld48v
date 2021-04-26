#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "monster.hpp"
#include "npc.hpp"
#include "player.hpp"
#include "render.cpp"
#include <string>
#include <time.h>
#include <unistd.h>

#define border_tile_path "data/tileset/border.png"
#define border_metatile_path "data/tileset/Player"

ddsc::player::player player("Player");
std::string ingame_console[5];

void encounter_generator();
void render_character_bar(sf::Image tile_array[15][20]);
void render_fight_screen(std::vector<ddsc::monster::monster> enemy_team, sf::Image tile_array[15][20]);
void render_room_view(sf::Image tile_array[15][20]);
void console_write(std::string str, sf::Image tile_array[15][20]);
void use_skill(unsigned char n);
void expire_skill();

unsigned char skill_1_reset_timer = 0;
unsigned char skill_2_reset_timer = 0;
unsigned char skill_3_reset_timer = 0;
unsigned short damage_modifier = 0;
unsigned int killed_monsters_total = 0;
unsigned short rooms = 0;
unsigned int time_passed = 0;

int main(void){
    // Init window
    sf::RenderWindow window(sf::VideoMode(1920, 1440), "Dark Dungeons and Scary Creatures");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    // Init variables and random
    sf::Clock clock;    // To get how long you played
    srand(time(NULL));
    sf::Image blank;
    blank.create(8, 8, sf::Color(245, 236, 223, 255));
    sf::Image tile_array[15][20];
    for(unsigned char y = 0; y < 15; y++){
        for(unsigned char x = 0; x < 20; x++){
            tile_array[y][x] = blank;
        }
    }
    // Game
    ddsc::render::init_font();
    ddsc::monster::monster skeleton("Skeleton", 12, 2, 15, "data/tileset/monsters/skeleton");
    ddsc::monster::monster skeleton_peaksman("Skeleton", 15, 4, 20, "data/tileset/monsters/skeleton");
    ddsc::monster::monster goblin("Goblin", 6, 1, 7, "data/tileset/monsters/goblin");
    ddsc::monster::monster goblin_looter("Goblin", 9, 1, 2, "data/tileset/monsters/goblin_looter");
    ddsc::monster::monster kobold("Kobold", 10, 2, 2, "data/tileset/monsters/kobold");
    ddsc::monster::monster kobold_spearsman("Kobold", 11, 3, 2, "data/tileset/monsters/kobold_spearsman");
    ddsc::monster::monster monster_pool[6] = {skeleton, skeleton_peaksman, goblin, goblin_looter, kobold, kobold_spearsman};
    ddsc::monster::monster dead_monster("Dead Monster", -1, 0, 0, "data/tileset/monsters/dead_monster"); // Dead monster sprite
    std::vector<ddsc::monster::monster> enemy_team;
    enemy_team.clear();
    for(unsigned char i = 0; i < (rand()%4)+1; i++){
        ddsc::monster::monster monster = monster_pool[rand()%6];
        ddsc::monster::autolevel(monster, rooms);
        enemy_team.push_back(monster);
    }
    ddsc::monster::autolevel(enemy_team.at(0), 5);
    while(window.isOpen()){
        time_passed = clock.getElapsedTime().asSeconds();
        sf::Event event;
        char command;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            } else if (event.type == sf::Event::TextEntered){
                if (event.text.unicode < 128){
                    command = static_cast<char>(event.text.unicode);
                }
            }
        }
        if(player.get_hp() > 0){
            render_character_bar(tile_array);
            ddsc::render::place_text("a:Attack", 10, 1, sf::Color::Black, tile_array);
            ddsc::render::place_text("1-6:Targ.", 10, 2, sf::Color::Black, tile_array);
            ddsc::render::place_text("", 10, 3, sf::Color::Black, tile_array);
            ddsc::render::place_text("1-3:Skill", 10, 4, sf::Color::Black, tile_array);
            //encounter_generator(window, monster_pool, tile_array);
            render_fight_screen(enemy_team, tile_array);
        }
        ddsc::render::render_from_tile_array(window, tile_array);
        unsigned char killed_monsters_room;
        if(command == '1'){
            use_skill(1);
        } else if(command == '2'){
            use_skill(2);
        } else if(command == '3'){
            use_skill(3);
        } else if(command == 'a'){
            char target = ' ';
            while(target == ' '){
                while (window.pollEvent(event)){
                    if(event.type == sf::Event::Closed){
                        window.close();
                    } else if (event.type == sf::Event::TextEntered){
                        if (event.text.unicode < 128){
                            target = static_cast<char>(event.text.unicode);
                            if(!(target > '0' && target <= enemy_team.size()+48)){
                                target = ' ';
                            }
                        }
                    }
                }
            }
            if(enemy_team.at(target-48-1).get_hp() >= 0){ // To prevent attacking dead monsters
                console_write("", tile_array);
                console_write("Attacking "+enemy_team.at(target-48-1).name, tile_array);
                ddsc::monster::damage_monster(enemy_team.at(target-48-1), player.get_damage()+damage_modifier);
                unsigned short damage_given = ddsc::monster::damage_monster(enemy_team.at(target-48-1), player.get_damage()+damage_modifier);
                console_write(std::to_string(damage_given) + " damage dealt", tile_array);
                if(enemy_team.at(target-48-1).get_hp() <= 0 && enemy_team.at(target-48-1).name != "Dead Monster"){
                    console_write(enemy_team.at(target-48-1).name + " dead", tile_array);
                    enemy_team.at(target-48-1) = dead_monster;
                    killed_monsters_room++;
                    killed_monsters_total++;
                }
            } else {
                console_write("You stab dead body", tile_array);
                console_write("nothing happens...", tile_array);
            }
            command = ' ';
            short prev_player_hp = player.get_hp();

            // Monster's turn
            for(unsigned char j = 0; j < enemy_team.size(); j++){ // This controls which monster do what
                if(enemy_team.at(j).get_hp() > 0){    // Only for living monsters
                    console_write(" ", tile_array);
                    short damage_amount = prev_player_hp-player.damage(enemy_team.at(j).get_damage());
                    if(player.get_hp() <= 0){
                        sf::Image black_bg;
                        black_bg.create(8, 8, sf::Color::Black);
                        for(unsigned char y = 0; y < 15; y++){
                            for(unsigned char x = 0; x < 20; x++){
                                tile_array[y][x] = black_bg;
                            }
                        }
                        ddsc::render::place_text("  Game Over, " + player.get_name(), 0, 0, sf::Color::Yellow, tile_array);
                        ddsc::render::place_text("Kills:"+std::to_string(killed_monsters_total), 0, 3, sf::Color::Yellow, tile_array);
                        ddsc::render::place_text("Rooms:"+std::to_string(rooms), 0, 4, sf::Color::Yellow, tile_array);

                        ddsc::render::place_text("Thank you", 0, 13, sf::Color::Yellow, tile_array);
                        ddsc::render::place_text("for playing.", 0, 14, sf::Color::Yellow, tile_array);
                    } else {
                        console_write(enemy_team.at(j).name + " attacks and ", tile_array);
                        console_write("deals " + std::to_string(damage_amount) + " damage", tile_array);
                    };
                }
            }
            expire_skill();
            if(killed_monsters_room == enemy_team.size()){
                rooms++;
                if(rooms%3 == 0){
                    ddsc::player::level_up(player, rooms/3);
                    console_write("Level up !", tile_array);
                    console_write("+DAM  +HP", tile_array);
                }
                console_write("'d' to go deeper.", tile_array);
            }
        } else if(command == 'd' && killed_monsters_room >= enemy_team.size()) {
            ddsc::render::render_splash_screen("data/splashscreens/new_room.png", window);
        }
        if(command == 'd' && killed_monsters_room >= enemy_team.size()){
            window.display();
            sf::Time delayTime = sf::seconds(1);
            sf::sleep(delayTime);
            // Create new enemies
            killed_monsters_room = 0;
            enemy_team.clear();
            for(unsigned char i = 0; i < (rand()%4)+1; i++){
                ddsc::monster::monster monster = monster_pool[rand()%6];
                ddsc::monster::autolevel(monster, rooms);
                enemy_team.push_back(monster);
            }
            command = ' ';
        } else {
            window.display();
        }
    }
    // Whoever will read this, you are amazing ! Thanks for spending time on my little game.
    return 0;
}
void use_skill(unsigned char n){
    if(n == 1 && skill_1_reset_timer == 0){
        damage_modifier = player.get_damage();
        skill_1_reset_timer = 3;
    } else if(n == 2 && skill_2_reset_timer == 0){
        unsigned short heal_amount = player.get_hp()+player.get_max_hp()/4;
        if(player.get_hp()+heal_amount > player.get_max_hp()){
            player.set_hp(player.get_max_hp());
        } else {
            player.set_hp(heal_amount);
        }
        skill_2_reset_timer = 3;
    } else if(n == 3 && skill_3_reset_timer == 0){
        damage_modifier = player.get_damage()*4;
        skill_3_reset_timer = 3;
    }
}
void expire_skill(){
    if(skill_1_reset_timer > 0){
        skill_1_reset_timer--;
    }
    if(skill_2_reset_timer > 0){
        skill_2_reset_timer--;
    }
    if(skill_3_reset_timer > 0){
        skill_3_reset_timer--;
    }
    damage_modifier = 0;
}
void render_character_bar(sf::Image tile_array[15][20]){
    // Clear bar
    sf::Image blank;
    blank.create(8, 8, sf::Color(245, 236, 223, 255));
    for(unsigned char y = 12; y < 14; y++){
        for(unsigned char x = 1; x < 19; x++){
            tile_array[y][x] = blank;
        }
    }
    // Fill it
    sf::Image border;
    border.loadFromFile(border_tile_path);
    for(unsigned char y = 0; y < 15; y++){
        for(unsigned char x = 0; x < 20; x++){
            if(y == 0 || y == 14 || y == 11 || x == 0 || x == 19){
                tile_array[y][x] = border;
            }
        }
    }
    unsigned char hp = ceil(100/player.get_max_hp()*player.get_hp());
    ddsc::render::place_text("HP:"+std::to_string(player.get_hp())+" / "+std::to_string(player.get_max_hp()), 1, 12, sf::Color(224, 72, 72, 255), tile_array);
    ddsc::render::place_text("1:  2:  3: ", 1, 13, sf::Color::Black, tile_array);
    sf::Image skill1, skill2, skill3, time_to_activation, inactive;
    inactive.create(8, 8, sf::Color(40, 40, 40, 255));
    if(skill_1_reset_timer == 0){
        skill1.loadFromFile("data/tileset/skills/Skill_1.png");
        skill1 = ddsc::render::merge_two_images(blank, skill1);
    } else {
        skill1.loadFromFile("data/tileset/skills/Skill_1_inactive.png");
        skill1 = ddsc::render::merge_two_images(inactive, skill1);
        time_to_activation.loadFromFile("data/tileset/subscript/Subscript_" + std::to_string(skill_1_reset_timer) + ".png");
        skill1 = ddsc::render::merge_two_images(skill1, time_to_activation);
    }
    if(skill_2_reset_timer == 0){
        skill2.loadFromFile("data/tileset/skills/Skill_2.png");
        skill2 = ddsc::render::merge_two_images(blank, skill2);
    } else {
        skill2.loadFromFile("data/tileset/skills/Skill_2_inactive.png");
        skill2 = ddsc::render::merge_two_images(inactive, skill2);
        time_to_activation.loadFromFile("data/tileset/subscript/Subscript_" + std::to_string(skill_2_reset_timer) + ".png");
        skill2 = ddsc::render::merge_two_images(skill2, time_to_activation);
    }
    if(skill_3_reset_timer == 0){
        skill3.loadFromFile("data/tileset/skills/Skill_3.png");
        skill3 = ddsc::render::merge_two_images(blank, skill3);
    } else {
        skill3.loadFromFile("data/tileset/skills/Skill_3_inactive.png");
        skill3 = ddsc::render::merge_two_images(inactive, skill3);
        time_to_activation.loadFromFile("data/tileset/subscript/Subscript_" + std::to_string(skill_3_reset_timer) + ".png");
        skill3 = ddsc::render::merge_two_images(skill3, time_to_activation);
    }
    tile_array[13][3] = skill1;
    tile_array[13][7] = skill2;
    tile_array[13][10] = skill3;
}
void render_fight_screen(std::vector<ddsc::monster::monster> enemy_team, sf::Image tile_array[15][20]){
    sf::Image tile;
    tile.loadFromFile(border_tile_path);
    for(unsigned char x = 0; x < 20; x++){
        tile_array[5][x] = tile;
        if(x == 9){
            for(unsigned char y = 1; y < 6; y++){
                tile_array[y][x] = tile;
            }
        }
    }
    ddsc::render::place_large_metatile("data/tileset/battle/tile1", 1, 1, tile_array);
    ddsc::render::place_large_metatile("data/tileset/battle/tile2", 5, 1, tile_array);
    unsigned char monster_y, monster_x;
    monster_x = 0;
    monster_y = 0;
    for(unsigned char i = 0; i < enemy_team.size(); i++){
        ddsc::monster::monster monster = enemy_team.at(i);
        ddsc::render::place_metatile(monster.icon, 7-monster_x, 1+monster_y, tile_array);
        sf::Image subscript;
        subscript.loadFromFile("data/tileset/subscript/Subscript_" + std::to_string(i+1) + ".png");
        tile_array[1+monster_y+1][7-monster_x+1] = ddsc::render::merge_two_images(tile_array[1+monster_y+1][7-monster_x+1], subscript);
        //monster_y += 2;
        if(i == 1){
            monster_x += 2;
            monster_y = 0;
        } else {
            monster_y += 2;
        }
    }
    ddsc::render::place_metatile(border_metatile_path, 1, 1, tile_array);
}
void console_write(std::string str, sf::Image tile_array[15][20]){
    if(str.size() > 18){
        str.erase(str.end()-(str.size()-18), str.end());
    }
    sf::Image blank;
    blank.create(8, 8, sf::Color(245, 236, 223, 255));
    // Clear console
    for(unsigned char y = 6; y < 11; y++){
        for(unsigned char x = 1; x < 19; x++){
            tile_array[y][x] = blank;
        }
    }
    // Push new string
    ingame_console[4] = ingame_console[3];
    ingame_console[3] = ingame_console[2];
    ingame_console[2] = ingame_console[1];
    ingame_console[1] = ingame_console[0];
    ingame_console[0] = str;
    for(unsigned char i = 0; i < 5; i++){
        ddsc::render::place_text(ingame_console[4-i], 1, 6+i, sf::Color(0, 0, 0, 255), tile_array);
    }
}
