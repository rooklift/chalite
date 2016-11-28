# chalite

C starter package for [Halite](https://halite.io/).

Two types are defined:

* `CONN` (for "connection") contains all relevant game data
* `SITE` contains [x, y, owner, strength, production] for one location

Primary functions defined:

* `CONN GetInit()`
* `void SendInit(char *botname)`
* `CONN GetFrame(CONN conn)`
* `void SetMove(CONN conn, int x, int y, int direction)`
* `void SendFrame(CONN conn)`

Note that these do not return pointers, nor do they take pointer arguments. To get the next frame, call GetFrame() with the current CONN as its argument. The return value is then a valid CONN containing updated game data. (No extra memory allocation happens; rather, the game data is updated via pointers in the CONN struct. The returned CONN has those same pointers.)

One can always pull whatever info one needs out of the CONN structure. For example, to get the strength at [x,y]:

`s = conn.strength[x][y]`

However, the following convenience functions are defined, which return a struct containing all the info about a single location:

* `SITE GetSiteFromXY(CONN conn, int x, int y)`
* `SITE GetSiteFromMovement(CONN conn, int x, int y, int direction)`

The latter is useful for finding info about neighbouring cells. Both these functions handle wraparound automagically.

Setting a move this frame is done by calling SetMove(). Once all desired moves are set, call SendFrame(). You are now ready to enter your next iteration. Note that GetFrame() will automatically clear the moves of the last frame.

A sample bot is included which makes this all fairly obvious.
