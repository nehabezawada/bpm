#pragma once

#include "oatpp/Types.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class JobDto : public oatpp::DTO {
    DTO_INIT(JobDto, DTO)
    DTO_FIELD(Int32, quantity);
};

#include OATPP_CODEGEN_END(DTO)