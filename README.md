# chalite

C starter package for [Halite](https://halite.io/).

Two types are defined:

* `GAME` contains all relevant game data
* `SITE` contains [x, y, owner, strength, production] for one location

A game is initialised with these 2 functions:

* `GAME GetInit()`
* `void SendInit(char *botname)`

Other important functions are:

* `GAME GetFrame(GAME game)`
* `void SetMove(GAME game, int x, int y, int direction)`
* `void SendFrame(GAME game)`

Note that the functions do not return pointers, nor do they take pointer arguments. To get the next frame, call GetFrame() with the current GAME as its argument. The return value is then a valid GAME containing updated game data. (No extra memory allocation happens; rather, the game data is updated via pointers in the GAME struct. The returned GAME has those same pointers.)

One can always pull whatever info one needs out of the GAME structure. For example, to get the strength at [x,y]:

`s = game.strength[x][y]`

However, the following convenience functions are defined, which return a struct containing all the info about a single location:

* `SITE GetSiteFromXY(GAME game, int x, int y)`
* `SITE GetSiteFromMovement(GAME game, int src_x, int src_y, int direction)`

The latter is useful for finding info about neighbouring cells. Both these functions handle wraparound automagically.

Setting a move this frame is done by calling SetMove(). Once all desired moves are set, call SendFrame(). You are now ready to enter your next iteration. Note that GetFrame() will automatically clear the moves of the last frame.

Sample bots are included; they make this all fairly obvious.
