<a name="readme-top"></a>

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

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Jdiazcaminos/HOOF-IMU">
    <img src="logo.png" alt="Logo" width="auto" height="80">
  </a>

<h3 align="center">Horse Hoof IMU - Senior Project</h3>

  <p align="center">
    The purpose of this project is to provide client with data regarding the IMU readings gathered from a Horse's Hoof to use towards determining the health of the Horse. Basically, sports watch for a horse.
    <br />
    <a href="https://github.com/Jdiazcaminos/HOOF-IMU"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Jdiazcaminos/HOOF-IMU">View Demo</a>
    ·
    <a href="https://github.com/Jdiazcaminos/HOOF-IMU/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    ·
    <a href="https://github.com/Jdiazcaminos/HOOF-IMU/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

# About The Project

A custom 9-DOF IMU with an additional 3-axis high-g accelerometer, which is used for impulses where the low-g accelerometer may clip, will be used to detect laminitis or rotational hoof sickness, in racehorses. The IMUs come equipped with a 3-axis low-g accelerometer, 3-axis high-g accelerometer, 3-axis gyroscope, and 3-axis magnetometer. Additionally, circuitry will be added for other features like GPS, Real-time timekeeping, and power management.

The IMUs will communicate directly to a central hub through a BLE mesh, which will allow wireless transmission of recorded data from each unique IMU device. After data collection, the data will be read from the central into a serial port on a computer where it will save the data and provide a real-time plot for data processing later.

## Built With

- ![Static Badge](https://img.shields.io/badge/sparkfun-black?style=for-the-badge&logo=sparkfun&logoColor=white&labelColor=%23E53525)

- ![Static Badge](https://img.shields.io/badge/arduino-black?style=for-the-badge&logo=arduino&labelColor=%2300878F)

- ![Static Badge](https://img.shields.io/badge/C-black?style=for-the-badge&logo=c&logoColor=white&labelColor=%23A8B9CC)

- ![Static Badge](https://img.shields.io/badge/c%2B%2B-black?style=for-the-badge&logo=cplusplus&logoColor=white&labelColor=%2300599C)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->

## Getting Started

In order to get this project up and running, there are two parts that need to be finished. The first is making sure the Central device is programmed and connected to the peripheral device, and the second is programming and connecting to the peripheral device on your laptop

**Preface:** Here are a couple links to help familiarize yourself with Git and GitHub.

Links:

(1) How to use Git click [here](https://youtu.be/USjZcfj8yxE?si=m7MtrsjsvbkFWDZs)

(2) How to use GitHub click [here](https://www.youtube.com/watch?v=nhNq2kIvi9s&ab_channel=ColtSteele)

### Prerequisites and Installation

1. Download Arduino IDE [https://www.arduino.cc/](https://www.arduino.cc/)
2. Clone the repo
   ```sh
   git clone https://github.com/Jdiazcaminos/HOOF-IMU.git
   ```
3. Add SEED library to arduino
   ```
   https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
   ```
4. Build and Install corresponding codes on central and peripheral device

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->

## Usage

TBD

### Terminology:

**IMU** - Inertial Measurement Unit

**DOF** - Degrees of Freedom

**Laminitis** - The inflammation of the laminae of the foot, which results in extreme pain and instability in horses.

_For more examples, please refer to the [Documentation](https://example.com)_

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ROADMAP -->

## Roadmap

- [x] Test with mobile battery pack
- [x] Add Timestamp to periphal data packet
- [x] Distance/Reliablility measurement ~40 ft
- [x] Complete power management system
- [x] Complete real-time plotting using BetterSerialMonitor
- [ ] Integrate GPS into the IMU system No Longer Feasbile due to Time Constraints
- [ ] Complete PCB design with integrated circuits and order appropriate chips Future Goal
      See the [open issues](https://github.com/Jdiazcaminos/HOOF-IMU/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->

## Contact

Josue D:

- [Github](https://github.com/Jdiazcaminos)
- [LinkedIn](https://www.linkedin.com/in/josuediaz-caminos/)

Andres R:

- [Github](https://github.com/Jdiazcaminos)
- [LinkedIn](https://www.linkedin.com/in/and-r/)

Alex G:

- [Github](https://github.com/)
- [LinkedIn](https://www.linkedin.com/in//)

Project Link: [https://github.com/Jdiazcaminos/HOOF-IMU](https://github.com/Jdiazcaminos/HOOF-IMU)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->

## Past Repository Maintainer

Kyle G:

- [GitHub](https://github.com/kyobg)
- [LinkedIn](https://www.linkedin.com/in/kyle-b-garcia/)

Kevin B:

- [GitHub](https://github.com/kevinbrannan)
- [LinkedIn](https://www.linkedin.com/in/kevin-brannan-885446233/)

Elena M:

- [GitHub](https://github.com/evolutis101)
- [LinkedIn](https://www.linkedin.com/in/elenammontalvo/)

Jonathan H:

- [GitHub](https://github.com/Grlee316)
- [LinkedIn](https://www.linkedin.com/in/jhanbali/)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/Jdiazcaminos/HOOF-IMU.svg?style=for-the-badge
[contributors-url]: https://github.com/Jdiazcaminos/HOOF-IMU/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Jdiazcaminos/HOOF-IMU.svg?style=for-the-badge
[forks-url]: https://github.com/Jdiazcaminos/HOOF-IMU/network/members
[stars-shield]: https://img.shields.io/github/stars/Jdiazcaminos/HOOF-IMU.svg?style=for-the-badge
[stars-url]: https://github.com/Jdiazcaminos/HOOF-IMU/stargazers
[issues-shield]: https://img.shields.io/github/issues/Jdiazcaminos/HOOF-IMU.svg?style=for-the-badge
[issues-url]: https://github.com/Jdiazcaminos/HOOF-IMU/issues
[license-shield]: https://img.shields.io/github/license/Jdiazcaminos/HOOF-IMU.svg?style=for-the-badge
[license-url]: https://github.com/Jdiazcaminos/HOOF-IMU/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
