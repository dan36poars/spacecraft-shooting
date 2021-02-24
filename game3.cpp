#include "Classes/Game.h"
#include <time.h>

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time((unsigned)(0)));

    Game game("Space Craft Shooting");

    game.run();

    return 0;
}
