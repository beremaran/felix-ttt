# Felix: Tic Tac Toe
![status-dev](https://img.shields.io/badge/status-dev-yellow.svg) ![version-0-0-1](https://img.shields.io/badge/version-0.0.1-blue.svg)

![felix logo](https://beremaran.com/felix.png)

![felix gui screenshot](https://beremaran.com/felix_ss.jpg)

Tic Tac Toe playing MCTS agent, written in C99. Predecessor for Felix: Go, developed as an experiment.

## Getting Started

Felix has no dependencies, apart from GTK+ 3.0.

### Prerequisities

 * CMake (3.10+) (or compile it by yourself, doesn't matter)
 * GTK+3.0
 

### Installing

 * Fork and clone repository to your machine
   
        git clone https://github.com/<your_username>/felix-ttt.git
        
 * Get in your repository directory
        
        cd felix-ttt
        
 * Create a directory as your build workspace
 
        mkdir build
        
 * Get in your newly created `build` directory
 
        cd build
        
 * Run `cmake` pointed to parent project directory
 
        cmake ..
        
 * Aaaand, `make`
 
        make
        
### Play Against Felix

Currently, Felix has ASCII (CLI) and GUI (GTK) interfaces which you can play tic-tac-toe against Felix.

`felix_ttt` is the command-line interface while `felix_ttt_gui` is the GUI interface to the Felix.

## Notes

 * I also created protocols and file formats for communicating between tic tac toe playing programs and storing tic tac toe games based on GNU and SGF specifications, called as TGF (Tic Tac Toe Game Format) and TTP (Tic Tac Toe Text Protocol).
 * TTP is not yet implemented, and seems like it would never gonna be implemented. But I still provide the documentation for those interested in.

## Contributing
Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.
I will appreciate any pull request to kill [TODO.md](TODO.md).

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the tags on this repository.

## Authors

 * __Berke Emrecan Arslan__ - _Initial work_ - [beremaran.com](beremaran.com)
 
## License

This project is licensed under the MIT license - see the [LICENSE](LICENSE) file for details