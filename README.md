# chalite

C starter package for [Halite](https://halite.io/).

Two types are defined:

* `GAME` contains all relevant game data
* `SITE` contains [x, y, owner, strength, production] for one location

A game is initialised with these 2 functions:

* `GAME GetInit()`
* `void SendInit(char *botname)`

Other important functions are:

* `void GetFrame(GAME game)`
* `void SetMove(GAME game, int x, int y, int direction)`
* `void SendFrame(GAME game)`

Note that the functions do not return pointers, nor do they take pointer arguments (they take value arguments). To get the next frame, call GetFrame() with the current GAME as its argument. The calling function's GAME is now up to date, because the GAME struct contains pointers to the actual data, and that data is updated by GetFrame(). (No extra memory allocation happens.)

One can always pull whatever info one needs out of the GAME structure. For example, to get the strength at [x,y]:

`s = game.strength[x][y]`

However, the following convenience functions are defined, which return a struct containing all the info about a single location:

* `SITE GetSiteFromXY(GAME game, int x, int y)`
* `SITE GetSiteFromMovement(GAME game, int src_x, int src_y, int direction)`

The latter is useful for finding info about neighbouring cells. Both these functions handle wraparound automagically.

Setting a move this frame is done by calling SetMove(). Once all desired moves are set, call SendFrame(). You are now ready to enter your next iteration. Note that GetFrame() will automatically clear the moves of the last frame.

Sample bots are included; they make this all fairly obvious.
