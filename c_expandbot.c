#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hlt.h"

#define BOT_NAME "C_ExpandBot"

int main(void) {

    GAME game;
    SITE target;
    int x, y, direction, neutral_count;

    srand(time(NULL));

    game = GetInit();           // To start a game, you
    SendInit(BOT_NAME);         // must do these two things.

    while (1) {

        GetFrame(game);         // Do this once per frame

        // AI logic follows. Call SetMove() for each move you want to make.

        for (x = 0 ; x < game.width ; x++) {
            for (y = 0 ; y < game.height ; y++) {
                if (game.owner[x][y] == game.playertag) {
                    neutral_count = 0;

                    // Attack nearby neutrals if possible

                    for (direction = 1 ; direction <= 4 ; direction++) {
                        target = GetSiteFromMovement(game, x, y, direction);
                        if (target.owner == 0) {
                            neutral_count++;
                            if (target.strength < game.strength[x][y]) {
                                SetMove(game, x, y, direction);
                                break;
                            }
                        }
                    }

                    // If there are no nearby neutrals, move randomly

                    if (neutral_count == 0) {
                        direction = rand() % 5;
                        SetMove(game, x, y, direction);
                    }
                }
            }
        }

        SendFrame(game);        // Do this once per frame
    }

    return 0;
}
