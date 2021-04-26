#include <SFML/Graphics.hpp>
#include "monster.hpp"
#include "player.hpp"

namespace ddsc {
    namespace render {
        class tile {
            public:
            sf::Image image;
            tile();
            tile(std::string path="data/tileset/missing.png");
        };
        sf::Image font_tileset[128];
        void init_font();   // Load font into font_tileset array
        sf::Image merge_two_images(sf::Image bg, sf::Image fg);
        void place_tile(tile tile, unsigned char x, unsigned char y, sf::Image tile_array[15][20]);                             // 1x1 tiles
        void place_metatile(std::string path_to_folder, unsigned char x, unsigned char y, sf::Image tile_array[15][20]);        // 2x2 tiles
        void place_large_metatile(std::string path_to_folder, unsigned char x, unsigned char y, sf::Image tile_array[15][20]);  // 4x4 tiles
        void place_text(std::string str, unsigned char x, unsigned char y, sf::Color text_color, sf::Image tile_array[15][20]);
        void render_from_tile_array(sf::RenderWindow &window, sf::Image tile_array[15][20]);
        void render_splash_screen(std::string path, sf::RenderWindow& window);  // Show full screen image
    }
}