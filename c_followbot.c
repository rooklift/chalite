#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hlt.h"

#define BOT_NAME "C_FollowBot"

int main(void) {

    GAME game;
    SITE neighbour;
    int x, y, direction, neutral_count, best_score, best_dir, turn;
    int ** time_captured;

    FILE * logfile;

    srand(time(NULL));

    game = GetInit();           // To start a game, you
    SendInit(BOT_NAME);         // must do these two things.

    time_captured = __new_2d_int_array(game.width, game.height);

    for (x = 0 ; x < game.width ; x++) {
        for (y = 0 ; y < game.height ; y++) {
            time_captured[x][y] = 0;
        }
    }

    turn = -1;

    while (1) {

        GetFrame(game);         // Do this once per frame

        turn++;

        // AI logic follows. Call SetMove() for each move you want to make.

        for (x = 0 ; x < game.width ; x++) {
            for (y = 0 ; y < game.height ; y++) {

                if (game.owner[x][y] == game.playertag) {

                    // Update our array of capture times, if needed.
                    // (There's a flaw in this strategy, but this is just an example bot.)

                    if (time_captured[x][y] == 0) {
                        time_captured[x][y] = turn;
                    }

                    neutral_count = 0;

                    // Attack nearby neutrals if possible

                    for (direction = 1 ; direction <= 4 ; direction++) {
                        neighbour = GetSiteFromMovement(game, x, y, direction);
                        if (neighbour.owner == 0) {
                            neutral_count++;
                            if (neighbour.strength < game.strength[x][y]) {
                                SetMove(game, x, y, direction);
                                break;
                            }
                        }
                    }

                    // If we're internal, move towards the action

                    if (game.strength[x][y] > 25 && neutral_count == 0) {

                        best_dir = STILL;
                        best_score = time_captured[x][y];

                        for (direction = 1 ; direction <= 4 ; direction++) {
                            neighbour = GetSiteFromMovement(game, x, y, direction);

                            if (time_captured[neighbour.x][neighbour.y] > best_score) {
                                best_score = time_captured[neighbour.x][neighbour.y];
                                best_dir = direction;
                            }
                        }

                        if (best_dir != STILL) {
                            SetMove(game, x, y, best_dir);
                        }
                    }
                }
            }
        }

        SendFrame(game);        // Do this once per frame
    }

    return 0;
}
