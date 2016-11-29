#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hlt.h"

#define BOT_NAME "C_ExpandBot"

int main(void) {

    CONN conn;
    SITE target;
    int x, y, direction, neutral_count;

    srand(time(NULL));

    conn = GetInit();           // To start a game, you
    SendInit(BOT_NAME);         // must do these two things.

    while (1) {

        conn = GetFrame(conn);  // Do this once per frame

        // AI logic follows. Call SetMove() for each move you want to make.

        for (x = 0 ; x < conn.width ; x++) {
            for (y = 0 ; y < conn.height ; y++) {
                if (conn.owner[x][y] == conn.playertag) {
                    neutral_count = 0;

                    // Attack nearby neutrals if possible

                    for (direction = 1 ; direction <= 4 ; direction++) {
                        target = GetSiteFromMovement(conn, x, y, direction);
                        if (target.owner == 0) {
                            neutral_count++;
                            if (target.strength < conn.strength[x][y]) {
                                SetMove(conn, x, y, direction);
                                break;
                            }
                        }
                    }

                    // If there are no nearby neutrals, move randomly

                    if (neutral_count == 0) {
                        direction = rand() % 5;
                        SetMove(conn, x, y, direction);
                    }
                }
            }
        }

        SendFrame(conn);        // Do this once per frame
    }

    return 0;
}
