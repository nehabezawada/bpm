# BPM Programming System

This repository contains a full-stack Business Process Management (BPM) simulation system with:
- **C++ OATPP backend** for job and socket management
- **React frontend dashboard** for real-time control and monitoring

## Features
- REST API for job control, socket management, and robot workflow
- 8-socket programming simulation with pass/fail logic
- Real-time dashboard with job progress and socket status
- Modular, testable, and well-documented code

## Project Structure
- `src/` — C++ backend source code (OATPP)
- `bpm-frontend/` — React frontend dashboard
- `test/` — Backend test code

## Backend Setup
1. **Install dependencies:**
   - Requires CMake, a C++17 compiler, and OATPP (see `utility/install-oatpp-modules.sh`)
2. **Build the backend:**
   ```sh
   mkdir build && cd build
   cmake .. && make
   ```
3. **Run the backend:**
   ```sh
   ./my-project-exe
   ```
   The server runs on [http://localhost:8000](http://localhost:8000)

## Frontend Setup
1. **Install dependencies:**
   ```sh
   cd bpm-frontend
   npm install
   ```
2. **Start the frontend:**
   ```sh
   npm start
   ```
   The app runs at [http://localhost:3000](http://localhost:3000)

## API Overview
See the [bpm-frontend/README.md](bpm-frontend/README.md) for endpoint details and usage examples.

## Testing
- Backend: See `test/` for example test cases.
- Frontend: Run `npm test` in `bpm-frontend` for basic React tests.

## Deliverables
- Complete C++ backend (OATPP)
- React dashboard
- Test coverage
- Documentation (this file, API docs)
- Demo video (see submission instructions)

## Submission
- Pushed all code to GitHub
- Include this README and the frontend README
- Provide a demo video showing the system in action

