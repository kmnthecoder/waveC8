# CHIP-8 Emulator by b4kill
A CHIP-8 emulator ran in a terminal for Windows.

# Instructions
This program relies on command line arguments in order to run.

Format: SCALE DELAY FILEPATH

Scale of 10 is a good starting place, this will determine the scaling size of the window.

Delay is how fast the emulator runs, anywhere from 1-3 is a good value depending on the game.

Filepath is the path of the file in which you want to open.

Example: ./chip8 10 1 ../roms/c8games/PONG3

If you want to compile, you'll need the SDL2 library.

# License
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
