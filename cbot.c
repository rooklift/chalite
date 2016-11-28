#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cbot.h"

#define BOT_NAME "C_semirandom_2"

int main(void) {

    CONN conn;
    SITE me, target;
    int x, y, direction;

    srand(time(NULL));

    conn = GetInit();           // To start a game, you
    SendInit(BOT_NAME);         // must do these two things.

    while (1) {

        conn = GetFrame(conn);  // Do this once per frame
        
        // AI logic here. Call SetMove() for each move you want to make.

        for (x = 0 ; x < conn.width ; x++) {
            for (y = 0 ; y < conn.height ; y++) {
                if (conn.owner[x][y] == conn.playertag) {
                    me = GetSiteFromXY(conn, x, y);
                    direction = rand() % 5;
                    target = GetSiteFromMovement(conn, x, y, direction);
                    if (target.strength < me.strength) {
                        SetMove(conn, x, y, direction);
                    }
                }
            }
        }

        SendFrame(conn);        // Do this once per frame
    }

    return 0;
}
