Guide for main method
Step 1: Build rules library with attributes
Step 2: User Input (Skip for now)
Step 3: Split building into smaller volumes - roof and rest of building
     - if it's an outside block, add shape to the active shape list
     Shape should have: 
     	   - float xyz[3]; //coord of its lower left corner
	   - float wdh[3]; // width, depth, height of block
	   - int rc[2]; //block the shape belongs to
	   - char *symbol;
	   - int floor;
	   - Attribute a;
	   - int dir[3]; //front facing direction of shape (for 3D drawings)
Step 4: Put in door, band, cornice
     - put door on random 1st floor shape/ middle of front
     - put band and cornice on first and second floor
     - add all active region to end of active list
     - add all terminal shapes to end of build design
     *** Remember to free parent shape ***
Step 5: Add Window & Roof
     - If Window style for the floor is NULL, pick one and all other windows on the same floor uses the same style
Step 6: Loop through building design and transform/rotate design based on dir 
     of shapes



MISC
Axis: positive x - right; positive y - up; positive z - out of screen
Given a building, lower left front corner is 0,0
Row counts along z axis (dec), column along x (inc), level along y (inc)
Width is column diff (x), Depth is row diff (z), Height is level diff (y)
Given, lower left corner of cube, these are 4 coords of shape (in order, LL, LR, UL, UR) when:
       - r = 0 (front):	  (x,y,z), (x+w, y, z), (x+w, y+h, z), (x, y+h, z)
       - r = max (back):  (x+w, y, z-d), (x,y,z-d), (x, y+h, z-d), (x+c, y+h, z-d)
       - c = 0 (left):	  (x, y, z-d), (x, y, z), (x, y+h, z), (x, y+h, z-d)
       - c = max (right): (x+w, y, z), (x+w, y, z-d), (x+w, y+h, z-d), (x+w, y+h, z)


Things to do:
In Attribute:
	- build an attribute library with preset attributes
	- attribute matching function takes in the attribute library and an attribute and 
	returns the attribute of shape of best fit (ex: takes in attribute with symbol 
	‘WIN’. Look for attribute of best fit with symbol ‘WIN’ and returns)

Symbols Needing matching:
Actually just do matching for window please. Given interval for simple, match one.
All else plays role in user specification
- F/F1: KS or not above window
- WIN: Frame pattern
- DOOR: Steps or not
- CORNICE: number of layer
- BAND: tiny window or not

Attributes should have the window stuff in paper and properties for other shapes 
	(i.e. boolean for whether or not doors have steps leading up to it,  
	should window have a keystone/balcony)

Active Symbols: F/F1 (facade/flr1/2 facade), CORNICE (cornice, 1 or 2 layer), DOOR, 
	STEP (steps), WIN, BAND
Terminal Symbol: BWIN (tiny band window), WALL(2D terminal), PRISM(3D terminal), 
	KS (keystone), WINDOW
