#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"
#include "../dto/JobDto.hpp"
#include "../ProgrammingSystemState.hpp"
#include "../dto/JobDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/Environment.hpp"

#include <thread>
#include <chrono>
#include <random>
#include <atomic>

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
public:
  ENDPOINT("GET", "/api/hello", hello) {
    return createResponse(Status::CODE_200, "Hello, BPM Assignment!");
  }
  /**
   * Constructor with object mapper.
   * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
   */
  MyController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
    : oatpp::web::server::api::ApiController(apiContentMappers)
  {}
public:
  
  ENDPOINT("GET", "/", root) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }
  
  ENDPOINT("POST", "/api/job/start", startJob,
           BODY_DTO(Object<JobDto>, jobDto)) {
    std::lock_guard<std::mutex> lock(systemState.mtx);

    if (systemState.job.status == JobStatus::RUNNING) {
        return createResponse(Status::CODE_400, "Job already running");
    }

    systemState.job.quantity = jobDto->quantity;
    systemState.job.completed = 0;
    systemState.job.passed = 0;
    systemState.job.failed = 0;
    systemState.job.status = JobStatus::RUNNING;

    for (auto& socket : systemState.sockets) {
        socket.status = SocketStatus::IDLE;
    }

    auto response = createResponse(Status::CODE_200, "{\"status\":\"ok\"}");
    response->putHeader("Content-Type", "application/json");
    return response;
}

  ENDPOINT("GET", "/api/job/status", getJobStatus) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      
      auto response = JobStatusDto::createShared();
      response->quantity = systemState.job.quantity;
      response->completed = systemState.job.completed;
      response->passed = systemState.job.passed;
      response->failed = systemState.job.failed;
      response->status = static_cast<int>(systemState.job.status);
      
      return createDtoResponse(Status::CODE_200, response);
  }

  ENDPOINT("POST", "/api/job/pause", pauseJob) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      
      if (systemState.job.status != JobStatus::RUNNING) {
          return createResponse(Status::CODE_400, "Job is not running");
      }
      
      systemState.job.status = JobStatus::PAUSED;
      return createResponse(Status::CODE_200, "Job paused");
  }

  ENDPOINT("POST", "/api/job/resume", resumeJob) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      
      if (systemState.job.status != JobStatus::PAUSED) {
          return createResponse(Status::CODE_400, "Job is not paused");
      }
      
      systemState.job.status = JobStatus::RUNNING;
      return createResponse(Status::CODE_200, "Job resumed");
  }

  ENDPOINT("POST", "/api/job/stop", stopJob) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      
      if (systemState.job.status == JobStatus::IDLE) {
          return createResponse(Status::CODE_400, "No job to stop");
      }
      
      systemState.job.status = JobStatus::STOPPED;
      return createResponse(Status::CODE_200, "Job stopped");
  }

  ENDPOINT("GET", "/api/sockets", getSocketStatus) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      
      auto response = SocketStatusDto::createShared();
      auto socketsList = oatpp::List<Object<SocketDto>>::createShared();
      
      for (const auto& socket : systemState.sockets) {
          auto socketDto = SocketDto::createShared();
          socketDto->id = socket.id;
          socketDto->status = static_cast<int>(socket.status);
          socketsList->push_back(socketDto);
      }
      
      response->sockets = socketsList;
      return createDtoResponse(Status::CODE_200, response);
  }

  ENDPOINT("POST", "/api/socket/{id}/activate", activateSocket,
           PATH(Int32, id)) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      
      if (id < 0 || id >= static_cast<int>(systemState.sockets.size())) {
          return createResponse(Status::CODE_400, "Invalid socket ID");
      }
      
      if (systemState.sockets[id].status != SocketStatus::IDLE) {
          return createResponse(Status::CODE_400, "Socket is not idle");
      }
      
      systemState.sockets[id].status = SocketStatus::ACTIVE;
      return createResponse(Status::CODE_200, "Socket activated");
  }

  ENDPOINT("POST", "/api/socket/{id}/deactivate", deactivateSocket,
           PATH(Int32, id)) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      
      if (id < 0 || id >= static_cast<int>(systemState.sockets.size())) {
          return createResponse(Status::CODE_400, "Invalid socket ID");
      }
      
      systemState.sockets[id].status = SocketStatus::IDLE;
      return createResponse(Status::CODE_200, "Socket deactivated");
  }

  ENDPOINT("GET", "/api/programming/sockets", programmingSockets) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      auto response = SocketStatusDto::createShared();
      auto socketsList = oatpp::List<Object<SocketDto>>::createShared();
      for (const auto& socket : systemState.sockets) {
          auto socketDto = SocketDto::createShared();
          socketDto->id = socket.id;
          socketDto->status = static_cast<int>(socket.status);
          socketsList->push_back(socketDto);
      }
      response->sockets = socketsList;
      return createDtoResponse(Status::CODE_200, response);
  }

  ENDPOINT("GET", "/api/robot/ready-to-place", robotReadyToPlace) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      auto response = SocketStatusDto::createShared();
      auto socketsList = oatpp::List<Object<SocketDto>>::createShared();
      for (const auto& socket : systemState.sockets) {
          if (socket.status == SocketStatus::IDLE) {
              auto socketDto = SocketDto::createShared();
              socketDto->id = socket.id;
              socketDto->status = static_cast<int>(socket.status);
              socketsList->push_back(socketDto);
          }
      }
      response->sockets = socketsList;
      return createDtoResponse(Status::CODE_200, response);
  }

  ENDPOINT("GET", "/api/robot/ready-to-pick", robotReadyToPick) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      auto response = SocketStatusDto::createShared();
      auto socketsList = oatpp::List<Object<SocketDto>>::createShared();
      for (const auto& socket : systemState.sockets) {
          if (socket.status == SocketStatus::COMPLETED_PASSED || socket.status == SocketStatus::COMPLETED_FAILED) {
              auto socketDto = SocketDto::createShared();
              socketDto->id = socket.id;
              socketDto->status = static_cast<int>(socket.status);
              socketsList->push_back(socketDto);
          }
      }
      response->sockets = socketsList;
      return createDtoResponse(Status::CODE_200, response);
  }

  ENDPOINT("POST", "/api/robot/device-placed", robotDevicePlaced,
           BODY_DTO(Object<SocketDto>, socketDto)) {
      OATPP_LOGd("MyController", "device-placed endpoint called");
      std::lock_guard<std::mutex> lock(systemState.mtx);
      int id = socketDto->id;
      if (id < 0 || id >= static_cast<int>(systemState.sockets.size())) {
          return createResponse(Status::CODE_400, "Invalid socket ID");
      }
      if (systemState.sockets[id].status != SocketStatus::IDLE) {
          return createResponse(Status::CODE_400, "Socket not ready to place");
      }
      if (systemState.job.status != JobStatus::RUNNING) {
          return createResponse(Status::CODE_400, "No running job");
      }
      systemState.sockets[id].status = SocketStatus::ACTIVE;
      simulateProgramming(id);
      return createResponse(Status::CODE_200, "Device placed, programming started");
  }

  ENDPOINT("POST", "/api/robot/device-picked", robotDevicePicked,
           BODY_DTO(Object<SocketDto>, socketDto)) {
      std::lock_guard<std::mutex> lock(systemState.mtx);
      int id = socketDto->id;
      if (id < 0 || id >= static_cast<int>(systemState.sockets.size())) {
          return createResponse(Status::CODE_400, "Invalid socket ID");
      }
      if (systemState.sockets[id].status != SocketStatus::COMPLETED_PASSED && systemState.sockets[id].status != SocketStatus::COMPLETED_FAILED) {
          return createResponse(Status::CODE_400, "Socket not ready to pick");
      }
      systemState.sockets[id].status = SocketStatus::IDLE;
      return createResponse(Status::CODE_200, "Device picked, socket ready for next job");
  }
  
  // TODO Insert Your endpoints here !!!
  
private:
  void simulateProgramming(int socketId) {
    std::thread([socketId]() {
      std::this_thread::sleep_for(std::chrono::seconds(5));
      std::lock_guard<std::mutex> lock(systemState.mtx);
      if (systemState.job.status != JobStatus::RUNNING) return;
      if (systemState.sockets[socketId].status != SocketStatus::ACTIVE) return;
      systemState.job.completed++;
      if (rand() % 100 < 80) {
        systemState.job.passed++;
        systemState.sockets[socketId].status = SocketStatus::COMPLETED_PASSED;
      } else {
        systemState.job.failed++;
        systemState.sockets[socketId].status = SocketStatus::COMPLETED_FAILED;
      }
      if (systemState.job.completed >= systemState.job.quantity) {
        systemState.job.status = JobStatus::COMPLETED;
      }
    }).detach();
  }
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
