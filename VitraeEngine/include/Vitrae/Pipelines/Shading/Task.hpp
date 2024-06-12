#pragma once

#include "Vitrae/Pipelines/Task.hpp"

#include "glm/glm.hpp"

namespace Vitrae
{
class ShaderTask : public Task
{
    using Task::Task;
};

namespace StandardShaderOutputNames
{
constexpr const char FRAGMENT_SHADER_OUTPUT[] = "shade";
constexpr const char VERTEX_SHADER_OUTPUT[] = "view_position";
constexpr const char COMPUTE_SHADER_OUTPUT[] = "computed_data";
} // namespace StandardShaderOutputNames

namespace StandardShaderOutputTypes
{
constexpr const TypeInfo &FRAGMENT_SHADER_OUTPUT_TYPE = Variant::getTypeInfo<glm::vec4>();
constexpr const TypeInfo &VERTEX_SHADER_OUTPUT_TYPE = Variant::getTypeInfo<glm::vec3>();
}

} // namespace Vitrae