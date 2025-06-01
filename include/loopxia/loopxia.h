#pragma once

#include "loopxia/log.h"
#include "loopxia/math.h"
#include "loopxia/ui.h"
#include "loopxia/event.h"

#include "loopxia/bounding_volume/bounding_volume.h"

#include "loopxia/render/shader.h"
#include "loopxia/render/render_buffer.h"
#include "loopxia/render/mesh_renderer.h"

#include "loopxia/resource/resource_manager.h"

#include "loopxia/object/camera.h"

#include "loopxia/scene/avatar.h"
#include "loopxia/scene/scene_renderer.h"

#include "loopxia/game/game.h"
#include "loopxia/game/camera_controller.h"

namespace loopxia
{
    void InitEngine();
    void ShutdownEngine();
}
