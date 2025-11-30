# cub3d

Cub3D is a 3D maze exploration game. The project is written in C using the MiniLibX graphics library. It implements a basic ray-casting engine to render a dynamic first-person view inside a maze, allowing the player to navigate and explore the environment in real time.

## Features

- Real-time 3D ray-casting engine
- First-person perspective navigation
- Texture mapping for walls
- Minimap display
- Mouse look support
- Collision detection
- Configurable maps with custom textures and colors

## Prerequisites and Setup

### Linux Setup

#### Required Dependencies

Install the following packages using your distribution's package manager:

**Ubuntu/Debian:**

```bash
sudo apt-get update
sudo apt-get install build-essential make git
sudo apt-get install libx11-dev libxext-dev libbsd-dev
```

**Fedora/RHEL/CentOS:**

```bash
sudo dnf install gcc make git
sudo dnf install libX11-devel libXext-devel libbsd-devel
```

**Arch Linux:**

```bash
sudo pacman -S base-devel git
sudo pacman -S libx11 libxext libbsd
```

#### MiniLibX Setup

The project uses MiniLibX for Linux, which will be automatically cloned and built during compilation. The Makefile handles this automatically, but if you need to set it up manually:

```bash
cd libs
git clone https://github.com/42paris/minilibx-linux.git
cd minilibx-linux
./configure
make
```

### macOS Setup

#### Required Dependencies

1. **Install Xcode Command Line Tools:**

   ```bash
   xcode-select --install
   ```

2. **Install X11/XQuartz:**

   ```bash
   brew install --cask xquartz
   ```

   After installation, **restart your terminal** or log out and log back in for X11 to be properly configured.

3. **Verify X11 Installation:**

   ```bash
   echo $DISPLAY
   ```

   If this is empty, you may need to set it:

   ```bash
   export DISPLAY=:0.0
   ```

#### MiniLibX Setup for macOS

**Important:** This project uses the **Linux version of MiniLibX** on both Linux and macOS.

The school-provided macOS version of MiniLibX only works on Intel-based Macs, and while there is a beta version for Apple Silicon (M processors), it doesn't work reliably. Therefore, this project uses the Linux MiniLibX version on macOS, which requires X11 to be installed.

**Requirements:**

- XQuartz must be installed and running (see step 2 above)
- The Linux MiniLibX will be automatically cloned and built during compilation

If you encounter linking issues, you may need to install additional X11 development libraries:

```bash
brew install libx11
```

## Building the Project

1. **Clone the repository:**

   ```bash
   git clone <repository-url>
   cd cub3d
   ```

2. **Build the project:**

   ```bash
   make
   ```

   This will:

   - Automatically clone MiniLibX if not present
   - Build libft (the custom C library)
   - Build MiniLibX
   - Compile all source files
   - Link everything into the `cub3d` executable

3. **Clean build artifacts:**
   ```bash
   make clean      # Remove object files
   make fclean     # Remove object files and executable
   make re         # Clean and rebuild everything
   ```

## Usage

### Running the Game

```bash
./cub3d <path_to_map.cub>
```

**Example:**

```bash
./cub3d maps/working/map.cub
```

### Map File Format

The `.cub` file format consists of:

1. **Texture Paths** (one per line):

   - `NO <path>` - North wall texture
   - `SO <path>` - South wall texture
   - `WE <path>` - West wall texture
   - `EA <path>` - East wall texture

2. **Colors** (RGB format):

   - `F <r>,<g>,<b>` - Floor color
   - `C <r>,<g>,<b>` - Ceiling color

3. **Map** (after a blank line):
   - `1` represents walls
   - `0` represents empty space
   - `N`, `S`, `E`, `W` represents the player's starting position and direction
   - Spaces are allowed in the map but are treated as empty space

**Example map file:**

```
NO ./textures/a1.xpm
SO ./textures/a2.xpm
WE ./textures/a3.xpm
EA ./textures/a4.xpm
F 0,0,0
C 237,67,192

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111110111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000000110000001001
10000000000000001101010010N01
1100000111010101111101111000111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Controls

- **W** - Move forward
- **S** - Move backward
- **A** - Strafe left
- **D** - Strafe right
- **Left Arrow** - Rotate left
- **Right Arrow** - Rotate right
- **Mouse Movement** - Look around (rotate view)
- **ESC** - Exit the game

### Testing with Valgrind

To check for memory leaks using Valgrind (Linux only):

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d maps/working/map.cub
```

## Troubleshooting

### Linux Issues

- **"X11/X.h: No such file or directory"**: Install X11 development libraries (see Linux Setup above)
- **"Cannot open display"**: Make sure you're running in an X11 session (not pure TTY)
- **Window doesn't appear**: Check that your display server is running and `$DISPLAY` is set

### macOS Issues

- **"X11/X.h: No such file or directory"**: Install XQuartz and restart terminal
- **"Cannot open display"**:
  - Make sure XQuartz is running
  - Set `export DISPLAY=:0.0` in your terminal
  - Try launching XQuartz manually before running the program
- **Library linking errors**: You may need to use a macOS-specific MiniLibX version instead of the Linux one

## Project Structure

```
cub3d/
├── includes/          # Header files
├── src/              # Source files
├── libs/             # External libraries (libft, minilibx)
├── maps/             # Map files (working and invalid examples)
├── textures/         # XPM texture files
└── Makefile          # Build configuration
```

## License

This project is part of the 42 curriculum.
