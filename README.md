# 🏙️City Route Planner

## 🌟 Overview
City Route Planner is a C-based program that calculates the shortest path between two cities using **Dijkstra's algorithm** and **Breadth-First Search (BFS)**. It represents the road network as a **graph** (using an adjacency matrix) and efficiently finds the minimum distance between cities.

## ✨ Features
- Implements **Dijkstra’s algorithm** for shortest path calculation.
- Uses **BFS** to explore possible routes.
- Stores the city road network in an **adjacency matrix**.
- Provides an interactive interface for users to input cities and receive the optimal route.

## 🛠️ Technologies Used
- **Language:** C  
- **Data Structures:** Graphs, Queues, Adjacency Matrix  
- **Algorithms:** Dijkstra’s Algorithm, BFS  

## 🚀 Installation & Usage
1. Clone the repository:
   ```sh
   git clone https://github.com/LinaAbufaraha/City-Route-Planner.git
   
2. Navigate to the project directory:
   ```sh
   cd City-Route-Planner   

3. Compile the program:   
    ```sh
   gcc city_route_planner.c -o city_route_planner 
4. Run the program:   
    ```sh
   ./city_route_planner  
5. Follow the on-screen instructions to enter city names and compute the shortest route.


## 🏗️ How It Works

 The program stores cities and their connections as a graph.

 The user enters two cities, and the system calculates the shortest path using:
   - Dijkstra’s Algorithm for weighted shortest path.
   - BFS for unweighted shortest path.

 The computed path and distance are displayed to the user.

## 📜 License
This project is for educational purposes. Feel free to use and modify it! 
   

