#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hlt.h"

#define BOT_NAME "C_StupidBot"

int main(void) {

    GAME game;
    SITE me, target;
    int x, y, direction;

    srand(time(NULL));

    game = GetInit();           // To start a game, you
    SendInit(BOT_NAME);         // must do these two things.

    while (1) {

        game = GetFrame(game);  // Do this once per frame

        // AI logic follows. Call SetMove() for each move you want to make.

        for (x = 0 ; x < game.width ; x++) {
            for (y = 0 ; y < game.height ; y++) {
                if (game.owner[x][y] == game.playertag) {
                    me = GetSiteFromXY(game, x, y);
                    direction = rand() % 5;
                    target = GetSiteFromMovement(game, x, y, direction);
                    if (target.strength < me.strength) {
                        SetMove(game, x, y, direction);
                    }
                }
            }
        }

        SendFrame(game);        // Do this once per frame
    }

    return 0;
}
