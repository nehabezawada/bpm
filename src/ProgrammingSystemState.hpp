#pragma once

#include <vector>
#include <mutex>
#include <random>
#include <chrono>

enum class SocketStatus {
    IDLE,
    ACTIVE,
    COMPLETED_PASSED,
    COMPLETED_FAILED
};

struct Socket {
    int id;
    SocketStatus status;
};

enum class JobStatus {
    IDLE,
    RUNNING,
    PAUSED,
    STOPPED,
    COMPLETED
};

struct ProgrammingJob {
    int quantity;
    int completed;
    int passed;
    int failed;
    JobStatus status;
};

class ProgrammingSystemState {
public:
    std::vector<Socket> sockets;
    ProgrammingJob job;
    std::mutex mtx;

    ProgrammingSystemState() {
        // Initialize 8 sockets (0-7) as IDLE
        for (int i = 0; i < 8; ++i) {
            sockets.push_back({i, SocketStatus::IDLE});
        }
        job = {0, 0, 0, 0, JobStatus::IDLE};
    }

    // Add methods for state management as needed
};

extern ProgrammingSystemState systemState;
