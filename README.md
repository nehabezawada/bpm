# BPM System – Fullstack Hardware Programming Simulator

## Overview

This project is a fullstack application (BPM) simulator, featuring:
- **Backend:** C++ with Oatpp, simulating hardware programming, job control, and robot workflow via REST APIs.
- **Frontend:** React + Material UI dashboard for real-time job control, socket status, and robot workflow monitoring.

---

## Table of Contents

- [Features](#features)
- [Architecture](#architecture)
- [Prerequisites](#prerequisites)
- [Setup Instructions](#setup-instructions)
  - [Backend Setup](#backend-setup)
  - [Frontend Setup](#frontend-setup)
- [Oatpp Integration](#oatpp-integration)
- [Usage](#usage)
- [API Endpoints](#api-endpoints)
- [Troubleshooting](#troubleshooting)
- [Demo](#demo)
---

## Features

- Start, pause, resume, and stop programming jobs
- Real-time socket status grid with color-coded states
- Robot workflow simulation (ready to place/pick, device placed/picked)
- Responsive, modern dashboard UI
- Toast notifications for job and robot events

---

## Architecture

- **Backend:** C++ (Oatpp), modular controllers, DTOs, RESTful API
- **Frontend:** React, Material UI, modular components, real-time polling

---

## Prerequisites

### Backend
- C++17 compatible compiler (e.g., `g++`, `clang++`)
- CMake 3.10+
- Git

### Frontend
- Node.js (v16 or v18 recommended)
- npm (v8+)

---

## Setup Instructions

### Backend Setup

1. **Clone the repository:**
   ```sh
   git clone https://github.com/nehabezawada/bpm.git
   cd <bpm>
   ```

2. **Initialize submodules (for Oatpp):**
   ```sh
   git submodule update --init --recursive
   ```

3. **Build the backend:**
   ```sh
   mkdir -p build
   cd build
   cmake ..
   make
   ```

4. **Run the backend server:**
   ```sh
   ./my-project-exe
   ```
   The server will start on port **8000** by default.

---

### Frontend Setup

1. **Navigate to the frontend directory:**
   ```sh
   cd bpm-frontend
   ```

2. **Install dependencies:**
   ```sh
   npm install
   ```

3. **Start the frontend:**
   ```sh
   npm start
   ```
   The app will run at [http://localhost:3000](http://localhost:3000).

---

## Oatpp Integration

This project uses [Oatpp](https://github.com/oatpp/oatpp) as the backend REST API framework. Oatpp is included as a **git submodule** in the `third_party/oatpp` directory. This allows for easy integration and version control of the Oatpp library within the project.

### How Oatpp Was Set Up

- **Added as a Git Submodule:**
  - Oatpp is not installed globally. Instead, it is included in the project as a submodule for portability and reproducibility.
  - To add Oatpp as a submodule, the following command was used:
    ```sh
    git submodule add https://github.com/oatpp/oatpp.git third_party/oatpp
    ```
  - After cloning the repository, you must initialize and update submodules:
    ```sh
    git submodule update --init --recursive
    ```

- **CMake Configuration:**
  - The project's `CMakeLists.txt` is set up to include and link Oatpp directly from the `third_party/oatpp` directory.
  - This ensures that the correct version of Oatpp is always used, and no system-wide installation is required.
  - All Oatpp headers and sources are referenced relative to the submodule path.

- **Rationale:**
  - Using a submodule ensures that anyone cloning the repository will have the exact Oatpp version required, avoiding compatibility issues.
  - This approach also makes the project self-contained and easier to build on any machine.

- **Summary of Steps:**
  1. Add Oatpp as a submodule to `third_party/oatpp`.
  2. Run `git submodule update --init --recursive` after cloning.
  3. Build the project as usual; CMake will use the local Oatpp source.

---

## Usage

1. **Start the backend server** (see above).
2. **Start the frontend dashboard** (see above).
3. Open [http://localhost:3000](http://localhost:3000) in your browser.
4. Use the dashboard to:
   - Start, pause, resume, or stop jobs
   - Monitor socket status in real time
   - Simulate robot actions (ready to place/pick, device placed/picked)
   - View job metrics and notifications

---

## API Endpoints

| Endpoint                        | Method | Description                        |
|----------------------------------|--------|------------------------------------|
| `/api/job/start`                | POST   | Start a new programming job        |
| `/api/job/stop`                 | POST   | Stop the current job               |
| `/api/job/pause`                | POST   | Pause the current job              |
| `/api/job/resume`               | POST   | Resume a paused job                |
| `/api/sockets`                  | GET    | Get status of all sockets          |
| `/api/programming/sockets`      | GET    | Get programming sockets status     |
| `/api/robot/ready-to-place`     | POST   | Simulate robot ready to place      |
| `/api/robot/ready-to-pick`      | POST   | Simulate robot ready to pick       |
| `/api/robot/device-placed`      | POST   | Simulate device placed by robot    |
| `/api/robot/device-picked`      | POST   | Simulate device picked by robot    |

---

## Troubleshooting

- **React errors about missing modules:**  
  Run `npm install` in the `bpm-frontend` directory.
- **Material UI or icon errors:**  
  Run `npm install @mui/material@5 @mui/icons-material@5 @emotion/react @emotion/styled` in the frontend directory.
- **Port conflicts:**  
  Make sure nothing else is running on ports 8000 (backend) or 3000 (frontend).
- **CMake or build errors:**  
  Ensure you have a C++17 compiler and CMake 3.10+ installed. Clean the build directory and try again.
- **CORS issues:**  
  The frontend is configured to proxy API requests to the backend. If you deploy separately, set up CORS headers on the backend.

---

## Demo

To demonstrate the system:
1. Start both backend and frontend as described above.
2. Use the dashboard to:
   - Start a job and observe socket status updates.
   - Pause/resume/stop jobs and see real-time changes.
   - Use the robot panel to simulate device placement and pickup.
   - Watch for notifications and job metrics updates.

---

