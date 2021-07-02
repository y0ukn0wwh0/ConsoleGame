##This is a program to mirror the screen of the console
##To do so, in the game.ino file uncommment the serial lines
##and run this when the console is connected.
##Make sure the COM port is the correct one.

import serial
import pygame
import time

#Change COM port to the one used by the Arduino
ser = serial.Serial('COM8', 250000, timeout=0)
pygame.init()

# Set up the drawing window
screen = pygame.display.set_mode([1280, 640])
buffersize = int((128*64)/8);

x = 0
y = 0

white = (255,255,255)
black = (0,0,0)

elapsedTime = 0

# Run until the user asks to quit
running = True
while running:

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    #Update the screen shown if the serial is filled with the expected size
    if ser.in_waiting == buffersize:
        buffer = ser.read(buffersize);

        screen.fill(black)

        for b in buffer:
            for i in range(0, 9):
                if b >> i & 1 == 1:
                    pygame.draw.rect(screen, (255,255,255), pygame.Rect(x, y+i*10, 10, 10))
                    #screen.set_at((x, y + i), white)
            x+=10
            if(x == 1280):
                x = 0
                y += 80

        y = 0
        x = 0
        elapsedTime = time.time()*1000

        pygame.display.flip()
    

ser.close()