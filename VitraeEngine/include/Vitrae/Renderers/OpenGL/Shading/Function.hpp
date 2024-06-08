#pragma once

#include "Vitrae/Pipelines/Shading/Function.hpp"
#include "Vitrae/Renderers/OpenGL/Shading/Task.hpp"

#include "dynasma/keepers/abstract.hpp"

#include <filesystem>
#include <variant>

namespace Vitrae
{

class OpenGLShaderFunction : public ShaderFunction, public OpenGLShaderTask
{
    std::vector<StringId> m_inputOrder;
    std::vector<StringId> m_outputOrder;
    String m_functionName;
    String m_fileSnippet;

  public:
    OpenGLShaderFunction(const SetupParams &params);
    ~OpenGLShaderFunction() = default;

    std::size_t memory_cost() const override;
    void extractUsedTypes(std::set<const TypeInfo *> &typeSet) const override;
    void extractSubTasks(std::set<const Task *> &taskSet) const override;

    void outputDeclarationCode(BuildContext args) const override;
    void outputDefinitionCode(BuildContext args) const override;
    void outputUsageCode(
        BuildContext args, const std::map<StringId, String> &inputParamsToSharedVariables,
        const std::map<StringId, String> &outputParamsToSharedVariables) const override;
};

} // namespace Vitrae