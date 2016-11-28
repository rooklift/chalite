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

    conn = GetInit();
    SendInit(BOT_NAME);

    while (1) {

        conn = GetFrame(conn);

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

        SendFrame(conn);
    }

    return 0;
}
