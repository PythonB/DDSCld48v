#include <string>

namespace ddsc {
    namespace npc {
        enum profession {EXPLORER, BLACKSMITH, TRADER};
        class npc {
            private:
            std::string name;           // Name
            profession npc_profession;  // It's role in game
            // Profession will be combined with name, e.g. Roland the Blackmith
            public:
            std::string get_name();
            npc(std::string n, profession p);
        };
    }
}