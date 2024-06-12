#pragma once

#include "Vitrae/Pipelines/Compositing/SceneRender.hpp"
#include "Vitrae/Util/ScopedDict.hpp"

#include <functional>
#include <vector>

namespace Vitrae
{

class OpenGLRenderer;

class OpenGLComposeSceneRender : public ComposeSceneRender
{
  public:
    using ComposeSceneRender::ComposeSceneRender;

    OpenGLComposeSceneRender(const SetupParams &params);

    void run(RenderRunContext args) const override;
    void prepareRequiredFrameStores(
        std::map<StringId, dynasma::FirmPtr<FrameStore>> &frameStores) const override;
    void prepareRequiredTextures(
        std::map<StringId, dynasma::FirmPtr<Texture>> &textures) const override;

  protected:
    StringId m_sceneInputNameId, m_displayOutputNameId;
};

} // namespace Vitrae