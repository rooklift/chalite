#include <stdio.h>
#include <stdlib.h>

// In general, none of the public functions return pointers,
// nor do they take pointer arguments.

#define STILL 0
#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

typedef struct Site_struct {
    int x;
    int y;
    int owner;
    int strength;
    int production;
} SITE;

typedef struct Conn_struct {
    int width;
    int height;
    int playertag;
    int ** moves;
    int ** owner;
    int ** production;
    int ** strength;
} CONN;

int ** __new_2d_int_array(int width, int height) {

    int x;
    int **result;

    result = malloc(sizeof(int*) * width);
    if (result == NULL) {
        printf("Malloc 1 failed in __new_2d_int_array()\n");
        exit(1);
    }

    for (x = 0 ; x < width ; x++) {
        result[x] = malloc(sizeof(int) * height);
        if (result[x] == NULL) {
            printf("Malloc 2 failed in __new_2d_int_array()\n");
            exit(1);
        }
    }

    return result;
}

int __getnextint() {

    int ch;

    int result = 0;
    int seen_any_digits = 0;

    while (1) {
        ch = getchar();
        if (ch == EOF) {
            printf("EOF received. Halite engine quit?\n");
            exit(1);
        }
        if (ch >= 48 && ch <= 57) {
            seen_any_digits = 1;
            result *= 10;
            result += ch - 48;
        } else {
            if (seen_any_digits) {
                return result;
            }
        }
    }

    return 54321;       // Never get here.
}

CONN __parseproduction(CONN conn) {
    int x, y;
    for (y = 0 ; y < conn.height ; y++) {
        for (x = 0 ; x < conn.width ; x++) {
            conn.production[x][y] = __getnextint();
        }
    }
    return conn;
}

CONN __parsemap(CONN conn) {

    int x, y;
    int run;
    int owner;
    int total_set;
    int set_this_run;

    x = 0;
    y = 0;
    total_set = 0;
    set_this_run = 0;
    while (total_set < conn.width * conn.height) {

        run = __getnextint();
        owner = __getnextint();

        for (set_this_run = 0 ; set_this_run < run ; set_this_run++) {

            conn.owner[x][y] = owner;
            total_set++;

            x++;
            if (x == conn.width) {
                x = 0;
                y += 1;
            }
        }
    }

    for (y = 0 ; y < conn.height ; y++) {
        for (x = 0 ; x < conn.width ; x++) {
            conn.strength[x][y] = __getnextint();
        }
    }

    return conn;
}

CONN GetInit() {

    CONN conn;

    conn.playertag = __getnextint();
    conn.width = __getnextint();
    conn.height = __getnextint();

    conn.moves = __new_2d_int_array(conn.width, conn.height);
    conn.owner = __new_2d_int_array(conn.width, conn.height);
    conn.production = __new_2d_int_array(conn.width, conn.height);
    conn.strength = __new_2d_int_array(conn.width, conn.height);

    conn = __parseproduction(conn);
    conn = __parsemap(conn);

    return conn;
}

void SendInit(char *botname) {
    printf("%s\n", botname);
    fflush(stdout);
}

CONN GetFrame(CONN conn) {

    int x, y;
    conn = __parsemap(conn);

    // Reset the moves array while we're at it.

    for (x = 0 ; x < conn.width ; x++) {
        for (y = 0 ; y < conn.height ; y++) {
            conn.moves[x][y] = STILL;
        }
    }

    return conn;
}

int __sanitise_x(CONN conn, int x) {
    if (x < 0) {
        x += -(x / conn.width) * conn.width + conn.width;      // Can make x == width, so must still use % later
    }
    x %= conn.width;
    return x;
}

int __sanitise_y(CONN conn, int y) {
    if (y < 0) {
        y += -(y / conn.height) * conn.height + conn.height;   // Can make y == height, so must still use % later
    }
    y %= conn.height;
    return y;
}

SITE GetSiteFromXY(CONN conn, int x, int y) {

    SITE result;

    x = __sanitise_x(conn, x);
    y = __sanitise_y(conn, y);

    result.x = x;
    result.y = y;

    result.owner = conn.owner[result.x][result.y];
    result.production = conn.production[result.x][result.y];
    result.strength = conn.strength[result.x][result.y];

    return result;
}

SITE GetSiteFromMovement(CONN conn, int src_x, int src_y, int direction) {

    SITE result;
    int x, y;
    
    x = src_x;
    y = src_y;

    switch (direction) {
    case NORTH:
        y--;
        break;
    case EAST:
        x++;
        break;
    case SOUTH:
        y++;
        break;
    case WEST:
        x--;
        break;
    }

    x = __sanitise_x(conn, x);
    y = __sanitise_y(conn, y);

    result = GetSiteFromXY(conn, x, y);

    return result;
}

void SetMove(CONN conn, int x, int y, int direction) {
    x = __sanitise_x(conn, x);
    y = __sanitise_y(conn, y);
    conn.moves[x][y] = direction;
    return;
}

void SendFrame(CONN conn) {
    int x, y;

    for (x = 0 ; x < conn.width ; x++) {
        for (y = 0 ; y < conn.height ; y++) {
            if (conn.moves[x][y] != STILL && conn.owner[x][y] == conn.playertag) {
                printf("%d %d %d ", x, y, conn.moves[x][y]);
            }
        }
    }

    printf("\n");
    fflush(stdout);

    return;
}
