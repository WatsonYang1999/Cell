#ifndef CELL_RENDERER_H
#define CELL_RENDERER_H

#include <math/linear_algebra/matrix.h>

#include "../lighting/point_light.h"
#include "../lighting/directional_light.h"
#include "command_buffer.h"

namespace Cell
{
    /* NOTE(Joey):

      Forward declare the types, s.t. we don't need to include the
      required header files here. Seeing as most objects throughout Cell will
      link to renderer.h we want to reduce as much unnecesary additional
      header code as much as possible (saves in compilation times). And seeing
      as we only need the typename for the function specifications this works
      just fine.

    */
    class Mesh;
    class Material;
    class Scene;
    class SceneNode;
    class Camera;

    /* NOTE(Joey):

      The main renderer; responsible for maintaining a render buffer queue
      and providing the front push commands for filling the buffer, then
      sorting the buffer, manage multiple render passes and render the
      buffer accordingly.

    */
    class Renderer
    {
    private:
        CommandBuffer m_CommandBuffer;

        Camera       *m_Camera;

        //std::map<std::string, Material*> m_Materials;

        // render state
        std::vector<DirectionalLight*> m_DirectionalLights;
        std::vector<PointLight*>       m_PointLights;
    public:
        Renderer();

        void Init();

        void SetTarget(/*FrameBuffer/RenderTexture target*/);

        Camera* GetCamera();
        void    SetCamera(Camera *camera);

        void PushRender(Mesh *mesh, Material *material, math::mat4 transform);
        void PushRender(SceneNode *node);
        void PushRender(Scene *scene);

        void PushLight(DirectionalLight *light);
        void PushLight(PointLight       *light);

        //Material* NewMaterial(std::string name); // NOTE(Joey): will by default material when created
        //Material *GetMaterial(std::String name);

        void Render();

        //void RenderToCubemap(SceneNode *root, Cubemap *cubemap, unsigned int faceWidth, unsigned int faceHeight, math::vec3 position);
    };
}

#endif