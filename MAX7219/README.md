Self-documented library for MAX7219. Works in a real device. Uses HW SPI. Has double-buffering.
Use MAX7219_uitob() to write a uint8_t into certain position of the buffer. (Positions are counted R to L, starting with 1).
Use MAX7219_Update() to push the buffer into display. 
don't forget to MAX7219_Init() first.
