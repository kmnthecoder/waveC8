# CHIP-8 Emulator by kmnthecoder
A CHIP-8 emulator using C++ and SDL2 for rendering.

# Tests

Passing tests:

# How to run
This program relies on command line arguments in order to run.

Format: 
    
    SCALE DELAY FILEPATH
    
Example:

    ./chip8 10 1 ../roms/c8games/PONG3

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
You'll need the SDL2 library in order to build. The makefile I used is included in the repository. I compiled with MinGW64.

# Lessons learned / Final thoughts

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
