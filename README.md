# EmbeddedFinalProject
Final project code for Embedded Systems class at the University of Iowa

##Project Description
Allow the user to play a simple game on an 8x8 RGB display, using a gyroscopic and accelerometer movements as the controls

##Main tasks
- Read data from gyroscope/accelerometer
  - I2C Communication
- Convert raw input data into orientation and movement values
  - Figure out what data is relevent
  - Math stuff to get movements
- Update game state based on movement data
  - Move character based on movement input
  - Update the game board (tic-tac-toe / obstacles)
- Display game
  - Convert game board and character into 8x8 rgb grid
  - Display 8x8 rgb grid

