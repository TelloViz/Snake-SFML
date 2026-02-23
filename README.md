<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
[![Snake + SFML Logo](https://github.com/Tello-/Snake-SFML/blob/master/Snake/Snake_Logo.png)](https://github.com/Tello-/Snake-SFML)

### Snake + SFML

Snake clone built with C++ and SFML using the CMake build system.

#### Check out a demo video on YouTube!

[![Demo Video](http://img.youtube.com/vi/DtEGNMsFRR8/0.jpg)](http://www.youtube.com/watch?v=DtEGNMsFRR8)

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Controls](#controls)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [Contact](#contact)



<!-- ABOUT THE PROJECT -->
## About The Project

![Snake+SFML][product-screenshot]
![Snake+SFML][product-screenshot2]
![Snake+SFML][product-screenshot3]

Snake+SFML is a clone of the classic game popularized by Nokia. Eat fruit to increase your score. However, as you eat your snake grows and avoiding your growing body becomes more difficult. Running into your own body will reduce your lives and leave a hazard in the play area. See how long your snake can grow.


### Built With

* [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/)
* [Cereal](https://github.com/USCiLab/cereal.git)
* [CMake](https://cmake.org/)



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

* CMake 3.16+
* A C++17 compatible compiler (Visual Studio 2019+, GCC, or Clang)
* Git

### Installation
 
1. Clone the repo
```sh
git clone https://github.com/Tello-/Snake-SFML.git
cd Snake-SFML
```
2. Configure and build with CMake
```sh
# Create build directory and configure
cmake -B build

# Build the project
cmake --build build --config Release
```
3. Run the game
```sh
# The executable and assets will be in build/bin/
./build/bin/Snake
```
4. Enjoy!

<!-- CONTROLS -->
## Controls
* WASD and Arrows - Move Snake
* P - Pause (during play)

<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/Tello-/Snake-SFML/issues) for a list of proposed features (and known issues).



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be **learn**, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- CONTACT -->
## Contact

Josh Lollis - lollisjosh@csu.fullerton.edu




<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/Tello-/Snake-SFML.svg?style=flat-square
[contributors-url]: https://github.com/Tello-/Snake-SFML/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Tello-/Snake-SFML.svg?style=flat-square
[forks-url]: https://github.com/Tello-/Snake-SFML/network/members
[stars-shield]: https://img.shields.io/github/stars/Tello-/Snake-SFML.svg?style=flat-square
[stars-url]: https://github.com/Tello-/Snake-SFML/stargazers
[issues-shield]: https://img.shields.io/github/issues/Tello-/Snake-SFML.svg?style=flat-square
[issues-url]: https://github.com/Tello-/Snake-SFML/issues
[license-shield]: https://img.shields.io/github/license/Tello-/Snake-SFML.svg?style=flat-square
[license-url]: https://github.com/Tello-/Snake-SFML/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/lollisjosh
[product-screenshot]: https://github.com/Tello-/Snake-SFML/blob/master/Screenshots/TitleScreen.JPG
[product-screenshot2]: https://github.com/Tello-/Snake-SFML/blob/master/Screenshots/Bones2.JPG
[product-screenshot3]:https://github.com/Tello-/Snake-SFML/blob/master/Screenshots/HighScoreScreen.JPG
