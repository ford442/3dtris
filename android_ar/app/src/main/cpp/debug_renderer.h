#ifndef C_DEBUG_RENDERER_H_
#define C_DEBUG_RENDERER_H_
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/asset_manager.h>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>
#include "arcore_c_api.h"
#include "glm.h"
#include "api.hpp"
class DebugRenderer{
public:
DebugRenderer();
~DebugRenderer() = default;
void InitializeGlContent();
void Draw(const glm::mat4 &projection_mat,const glm::mat4 &view_mat);
static void setLines(const std::vector <std::pair<glm::vec3,glm::vec3>> &lines);
private:
static DebugRenderer *instance;
void setLinesImpl(const std::vector <std::pair<glm::vec3,glm::vec3>> &lines);
std::vector <GLfloat> vertices_;
std::vector <GLushort> indices_;
GLuint shader_program_;
GLuint attri_vertices_;
GLuint uniform_mvp_mat_;
GLuint uniform_color_;
};
#endif
