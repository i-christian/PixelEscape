# PixelEscape

## Escape the Pixelated Labyrinth: A 3D Raycasting Maze Adventure 🎮

![GitHub repo size](https://img.shields.io/github/repo-size/i-christian/PixelEscape?style=flat-square)
![GitHub license](https://img.shields.io/github/license/i-christian/PixelEscape?style=flat-square)

### Introduction
Embark on a thrilling journey through a captivating 3D maze rendered using raycasting techniques. Navigate intricate corridors, solve challenging puzzles, and overcome obstacles as you strive to escape. Unleash your creativity to customize the map, textures, and game mechanics.

- **Deployed Site**: [PixelEscape Demo](https://i-christian.github.io/alx-landing_Page/)
- **Final Project Blog Article**: [PixelEscape: Exploring 3D Raycasting](https://medium.com/@icmhango/my-journey-in-raycasting-a-3d-game-development-odyssey-aaf2764a3c82)
- **Author(s) LinkedIn**: [Christian Mhango](https://www.linkedin.com/in/i-christian/)

### Description
PixelEscape is a 3D maze adventure game developed using raycasting techniques. It offers an immersive experience with dynamic lighting, weather effects, and customizable maps.

### Key Features
- Immersive 3D environment powered by raycasting.
- Optional map textures and decorations.
- Dynamic lighting and weather effects (rain).
- Keyboard controls for intuitive movement.

### Requirements
- **Operating System**: Linux (Ubuntu 14.04 LTS) or Later
- **Compiler**: gcc (Version 4.8.4-2ubuntu1~14.04) or Later
- **Development Libraries**: [SDL2](https://www.libsdl.org/)

### Installation
To install PixelEscape, follow these steps:

1. Check for SDL2 libraries:
    ```bash
    apt-cache search libsdl2
    ```
2. Install SDL2 development libraries:
    ```bash
    apt-get install libsdl2-dev
    ```

### Build Instructions
1. Clone the project repository:
    ```bash
    git clone https://github.com/i-christian/PixelEscape.git
    ```
2. Navigate to the project directory:
    ```bash
    cd PixelEscape
    ```
3. Compile the code:
    ```bash
    make
    ```

### Usage
- Run the game:
    ```bash
    ./PixelEscape maps/MAP_1
    ```
- Use the arrow keys to move and rotate the camera.
- Press `↑` to move forward, `←` to move left, `↓` to move backward, and `→` to move right.
- Press `m` to switch between 2D and 3D views.
- Press `t` to switch between textured and untextured views.
- Press the appropriate keys to interact with objects, trigger events, and overcome challenges.
- Explore the map, solve puzzles, and find the exit to win! 🏆

### Screenshots
![PixelEscape Screenshot](screenshot.png)

### Contributing
Contributions to PixelEscape are welcome! If you'd like to contribute, please follow the guidelines outlined in the [CONTRIBUTING.md](CONTRIBUTING.md) file.

### Related Projects
Explore these related projects for more inspiration:
- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Ray-Casting Tutoria](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [Make Your Own Raycaster](https://www.youtube.com/watch?v=gYRrGTC7GtA)

### Licensing
PixelEscape is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

### Portfolio Requirement
PixelEscape was developed as a portfolio requirement for the ALX Full Stack Software Engineering online course. It showcases proficiency in 3D game development, raycasting algorithms, and project management skills.
