#include "render.hpp"
#include <SFML/Graphics.hpp>
#include "monster.hpp"
#include "player.hpp"
#include <string>

void ddsc::render::init_font(){
    sf::Image image;
    image.loadFromFile("data/tileset/font/special/space.png");
    std::string path;
    // Fill all array with spaces to prevent printing unexisting charcters
    for(unsigned char i = 0; i < 128; i++){
        font_tileset[i] = image;
    }
    // Fill special symbols
    image.loadFromFile("data/tileset/font/special/exclamation_mark.png");       // !
    font_tileset[33] = image;
    image.loadFromFile("data/tileset/font/special/quotation_mark.png");         // "
    font_tileset[34] = image;
    image.loadFromFile("data/tileset/font/special/percent.png");                // %
    font_tileset[37] = image;
    image.loadFromFile("data/tileset/font/special/single_quotation_mark.png");  // '
    font_tileset[39] = image;
    image.loadFromFile("data/tileset/font/special/opening_bracket.png");        // (
    font_tileset[40] = image;
    image.loadFromFile("data/tileset/font/special/closing_bracket.png");        // )
    font_tileset[41] = image;
    image.loadFromFile("data/tileset/font/special/comma.png");                  // ,
    font_tileset[44] = image;
    image.loadFromFile("data/tileset/font/special/minus.png");                  // -
    font_tileset[45] = image;
    image.loadFromFile("data/tileset/font/special/dot.png");                    // .
    font_tileset[46] = image;
    image.loadFromFile("data/tileset/font/special/slash.png");                  // /
    font_tileset[47] = image;
    image.loadFromFile("data/tileset/font/special/double_dots.png");            // :
    font_tileset[58] = image;
    image.loadFromFile("data/tileset/font/special/question_mark.png");          // ?
    font_tileset[63] = image;

    image.loadFromFile("data/tileset/font/special/0.png");          // ?
    font_tileset[48] = image;
    image.loadFromFile("data/tileset/font/special/1.png");          // ?
    font_tileset[49] = image;
    image.loadFromFile("data/tileset/font/special/2.png");          // ?
    font_tileset[50] = image;
    image.loadFromFile("data/tileset/font/special/3.png");          // ?
    font_tileset[51] = image;
    image.loadFromFile("data/tileset/font/special/4.png");          // ?
    font_tileset[52] = image;
    image.loadFromFile("data/tileset/font/special/5.png");          // ?
    font_tileset[53] = image;
    image.loadFromFile("data/tileset/font/special/6.png");          // ?
    font_tileset[54] = image;
    image.loadFromFile("data/tileset/font/special/7.png");          // ?
    font_tileset[55] = image;
    image.loadFromFile("data/tileset/font/special/8.png");          // ?
    font_tileset[56] = image;
    image.loadFromFile("data/tileset/font/special/9.png");          // ?
    font_tileset[57] = image;
    // Fil uppercase letters (65 to 90)
    for(unsigned char i = 65; i < 90; i++){
        std::string character(1, i);
        path = "data/tileset/font/uppercase/" + character + ".png";
        image.loadFromFile(path);
        font_tileset[i] = image;
    }
    // Fill lowercasee letters (97 to 122)
    for(unsigned char i = 97; i < 122; i++){
        std::string character(1, i);
        path = "data/tileset/font/lowercase/" + character + ".png";
        image.loadFromFile(path);
        font_tileset[i] = image;
    }
}
sf::Image ddsc::render::merge_two_images(sf::Image bg, sf::Image fg){
    sf::Image result = bg;
    for(unsigned char y = 0; y < fg.getSize().y; y++){
        for(unsigned char x = 0; x < fg.getSize().x; x++){
            if(fg.getPixel(x, y) != sf::Color::Transparent){
                result.setPixel(x, y, fg.getPixel(x, y));
            }
        }
    }
    return result;
}
void ddsc::render::place_text(std::string str, unsigned char x, unsigned char y, sf::Color text_color, sf::Image tile_array[15][20]){
    unsigned char current_x = x;
    for(unsigned int i = 0; i < str.length(); i++){
        sf::Image glyph = font_tileset[str.at(i)];
        for(unsigned char y = 0; y < glyph.getSize().y; y++){
            for(unsigned char x = 0; x < glyph.getSize().x; x++){
                if(glyph.getPixel(x, y) != sf::Color::Transparent){
                    glyph.setPixel(x, y, text_color);
                }
            }
        }
        tile_array[y][current_x] = merge_two_images(tile_array[y][current_x], glyph);
        current_x++;
    }
}
void ddsc::render::place_metatile(std::string path_to_folder, unsigned char x, unsigned char y, sf::Image tile_array[15][20]){
    sf::Image tile;
    unsigned char tile_number = 0;
    for(unsigned char cy = 0; cy < 2; cy++){
        for(unsigned char cx = 0; cx < 2; cx++){
            std::string character(1, tile_number);
            tile.loadFromFile(path_to_folder+"/tile00"+std::to_string(tile_number)+".png");
            tile_array[y+cy][x+cx] = merge_two_images(tile_array[y+cy][x+cx], tile);
            tile_number++;
        }
    }
}
void ddsc::render::place_large_metatile(std::string path_to_folder, unsigned char x, unsigned char y, sf::Image tile_array[15][20]){
    sf::Image tile;
    unsigned char tile_number = 0;
    for(unsigned char cy = 0; cy < 4; cy++){
        for(unsigned char cx = 0; cx < 4; cx++){
            std::string character(1, tile_number);
            if(tile_number >= 10){
                tile.loadFromFile(path_to_folder+"/tile0"+std::to_string(tile_number)+".png");
            } else {
                tile.loadFromFile(path_to_folder+"/tile00"+std::to_string(tile_number)+".png");
            }
            tile_array[y+cy][x+cx] = merge_two_images(tile_array[y+cy][x+cx], tile);
            tile_number++;
        }
    }
}
void ddsc::render::render_splash_screen(std::string path, sf::RenderWindow& window){
    sf::Texture splashscreen;
    splashscreen.loadFromFile(path);
    sf::Sprite splashscreen_container;
    splashscreen_container.setTexture(splashscreen);
    splashscreen_container.scale(sf::Vector2f(window.getSize().x/160, window.getSize().y/120));
    window.draw(splashscreen_container);
}
void ddsc::render::render_from_tile_array(sf::RenderWindow &window, sf::Image tile_array[15][20]){
    int x_scale_factor = window.getSize().x/160;
    int y_scale_factor = window.getSize().y/120;
    sf::Texture texture_from_image;
    sf::Sprite sprite;
    sprite.scale(sf::Vector2f(x_scale_factor, y_scale_factor));
    for(unsigned char y = 0; y < 15; y++){
        for(unsigned char x = 0; x < 20; x++){
            texture_from_image.loadFromImage(tile_array[y][x]);
            sprite.setTexture(texture_from_image);
            //sprite.setColor(sf::Color::Yellow);
            sprite.setPosition(sf::Vector2f(8*x*x_scale_factor, 8*y*y_scale_factor));
            window.draw(sprite);
        }
    }
}