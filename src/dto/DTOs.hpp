#pragma once

#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class MyDto : public oatpp::DTO {
  
  DTO_INIT(MyDto, DTO)
  
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, message);
  
};

class JobStatusDto : public oatpp::DTO {
  DTO_INIT(JobStatusDto, DTO)
  DTO_FIELD(Int32, quantity);
  DTO_FIELD(Int32, completed);
  DTO_FIELD(Int32, passed);
  DTO_FIELD(Int32, failed);
  DTO_FIELD(Int32, status);
};

class SocketDto : public oatpp::DTO {
  DTO_INIT(SocketDto, DTO)
  DTO_FIELD(Int32, id);
  DTO_FIELD(Int32, status);
};

class SocketStatusDto : public oatpp::DTO {
  DTO_INIT(SocketStatusDto, DTO)
  DTO_FIELD(List<Object<SocketDto>>, sockets);
};

#include OATPP_CODEGEN_END(DTO)
