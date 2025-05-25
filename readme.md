# EvPong

A simple software rendered pong clone I made. Control the paddle using the up and down arrow keys, quit the game by pressing ESC. The AI is a bit juiced, but certainly beatable.

If you're on Linux, just install the SDL3 library (or build it yourself) and run build.sh. On Windows you'll need to grab the binaries and adjust the CMake config.

## Supported Platforms

Anything that is supported by SDL3 but confirmed to work on:

- Microsoft Windows
- Linux
- MacOS (we're software rendering here, so no OpenGL dependencies or any requirement for Vulkan or Metal).

If you wanna try port it to the Nintendo Switch or the PS2 or something then be my guest.
