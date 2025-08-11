# BFS-on-GameOfLife

A simple C++ console-based implementation of Conway's Game of Life combined with Breadth-First Search (BFS) pathfinding.
📌 Overview

This project simulates Conway's Game of Life for three iterations, starting from either:

    A random initial seed, or

    A custom number of alive cells specified by the user.

After the simulation, the program asks for two coordinates representing the start and destination cells. It then uses the BFS algorithm to find the shortest path only through dead cells (#).

🎯 Features

    Game of Life Simulation

        Runs for 3 frames.

        Supports random generation or user-defined alive cell count.

    Shortest Path Finder

        BFS algorithm implementation.

        Works only on dead cells.

    Input Validation

        Prevents invalid coordinates or impossible alive cell counts.

    Clean CLI Display

        Board refresh between frames for a smooth view.

🖥 Example Output
<img width="1144" height="613" alt="Captures - File Explorer 11-Aug-25 7_52_34 PM" src="https://github.com/user-attachments/assets/89affa15-dd21-423b-b9c2-b9dbec208fa8" />

🔧 How to Run

  1.Compile the program:

    g++ GameOfLifeProject.cpp -o game

  2.Run:

    ./game
📚 Algorithms Used

    Conway's Game of Life rules:

        A cell with exactly 2 or 3 alive neighbors stays alive.

        Otherwise, it becomes or remains dead.

    Breadth-First Search (BFS):

        Finds the shortest path between two points in a grid.

🚀 Future Improvements

    Add support for wrap-around grid (toroidal map).

    Show step-by-step path visualization.

    Adjustable simulation speed.

📝 License

    This project is open-source and available under the MIT License
