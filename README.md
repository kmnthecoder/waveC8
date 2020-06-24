# CHIP-8 Emulator
A CHIP-8 emulator using C++ and SDL2 for rendering.

![Space Invaders](demo/invaders_demo.gif)

![PONG2](demo/pong2_demo.gif)

# Tests
Passes CHIP-8 tests

![Opcode Test](demo/test1_demo.gif)

![BestCoder Test](demo/test2_demo.gif)

# How to run
This program relies on command line arguments in order to run.

Format: 
    
    PROGRAM_PATH SCALE DELAY FILE_PATH
    
Example:

    ./waveC8 10 1 ../roms/PONG2

Scale of 10 is a good starting place, this will determine the scaling size of the window.

Delay is how fast the emulator runs, anywhere from 1-3 is a good value depending on the game.

Filepath is the path of the file in which you want to open.

# Keys
Keys are mapped to:

      CHIP-8 keypad            Your keyboard
        +-+-+-+-+                +-+-+-+-+
        |1|2|3|C|                |1|2|3|4|
        +-+-+-+-+                +-+-+-+-+
        |4|5|6|D|                |Q|W|E|R|
        +-+-+-+-+       =>       +-+-+-+-+
        |7|8|9|E|                |A|S|D|F|
        +-+-+-+-+                +-+-+-+-+
        |A|0|B|F|                |Z|X|C|V|
        +-+-+-+-+                +-+-+-+-+

# Building
You'll need the SDL2 library in order to build. The makefile I used is included in the repository. I compiled with MinGW-w64.

# Lessons learned / Final thoughts
This project was undertaken in order to familiarize myself with C++ after not having used it for quite a while. 

I've learned a lot about emulation development; namely, how each system component interacts with each other (e.g., RAM, CPU, display), and SDL2-like libraries (handling input, graphics, audio).

The biggest hurdle in this project was understanding the different components, and understanding how the CPU worked. Some of the OP codes were challenging to implement, such as the draw OP code. They have taught me a lot about bit-wise operations and the inner workings of a CPU architecture.

I highly recommend this type of project to anyone wanting to delve into emulator development, low level system development, and video game programming.

# License [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

    Copyright 2020 Kevin Nguyen

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
