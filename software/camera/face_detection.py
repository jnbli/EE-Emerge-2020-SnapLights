# Face Detection Example
#
# This example shows off the built-in face detection feature of the OpenMV Cam.
#
# Face detection works by using the Haar Cascade feature detector on an image. A
# Haar Cascade is a series of simple area contrasts checks. For the built-in
# frontalface detector there are 25 stages of checks with each stage having
# hundreds of checks a piece. Haar Cascades run fast because later stages are
# only evaluated if previous stages pass. Additionally, your OpenMV Cam uses
# a data structure called the integral image to quickly execute each area
# contrast check in constant time (the reason for feature detection being
# grayscale only is because of the space requirment for the integral image).

import sensor, time, image
from pyb import UART

uart = UART(3, 9600)

# Reset sensor
sensor.reset()

# Sensor settings
sensor.set_contrast(3)
sensor.set_gainceiling(16)
# HQVGA and GRAYSCALE are the best for face tracking.
sensor.set_framesize(sensor.HQVGA)
sensor.set_pixformat(sensor.GRAYSCALE)

# Load Haar Cascade
# By default this will use all stages, lower satges is faster but less accurate.
face_cascade = image.HaarCascade("frontalface", stages=25)
print(face_cascade)

# FPS clock
clock = time.clock()

while (True):
    clock.tick()

    # Capture snapshot
    img = sensor.snapshot()

    # Find objects.
    # Note: Lower scale factor scales-down the image more and detects smaller objects.
    # Higher threshold results in a higher detection rate, with more false positives.
    objects = img.find_features(face_cascade, threshold=0.75, scale_factor=1.25)

    # Draw objects
    for r in objects:
        img.draw_rectangle(r)

        #Horizontal
        if (r[0] > 110 and 20 < r[1] and r[1] < 60):
            #middle-right
            uart.write('5')
            if (uart.any()):
                print(uart.read())

        elif (50 < r[0] and r[0] < 110 and 20 < r[1] and r[1] < 60):
            #middle-middle
            uart.write('4')
            if (uart.any()):
                print(uart.read())

        elif (r[0] < 50 and 20 < r[1] and r[1] < 60):
            #middle-left
            uart.write('3')
            if (uart.any()):
                print(uart.read())

        # Vertical
        elif (r[1] > 60 and 50 < r[0] and r[0] < 110):
            #bottom-middle
            uart.write('7')
            if (uart.any()):
                print(uart.read())

        elif (r[1] < 20 and 50 < r[0] and r[0] < 110):
            # top-middle
            uart.write('1')
            if (uart.any()):
                print(uart.read())

        # Corners
        elif (r[0] < 50 and r[1] > 60):
            #bottom-left
            uart.write('6')
            if (uart.any()):
                print(uart.read())

        elif (r[0] > 110 and r[1] > 60):
            #bottom-right
            uart.write('8')
            if (uart.any()):
                print(uart.read())

        elif (r[0] < 50 and r[1] < 20):
            # top-left
            uart.write('0')
            if (uart.any()):
                print(uart.read())

        elif (r[0] > 110 and r[1] < 20):
            # top-right
            uart.write('2')
            if (uart.any()):
                print(uart.read())

        print('-------')
        print(r[0])
        print(r[1])

# Print FPS.
# Note: Actual FPS is higher, streaming the FB makes it slower.
i = i+1
if (i == 50):
    print(clock.fps())
    i = 0
