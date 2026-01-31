#pragma once

#include "core/cheat/inits/inits.hpp"
#include "core/structs/structs.hpp"
#include "core/structs/color.hpp"
#include "core/structs/sdk/il2cpp.hpp"

namespace pointers {
    namespace Player {
        inline void* my_player;

        inline void (*Update) (void*);
        inline int (*get_team) (void*);
        inline void (*SendChatMessage) (void*, MonoString*, bool, bool, bool);
        inline MonoString *(*get_username) (void*);
        inline void (*set_visible) (bool);

        namespace Bones {
            inline void *(*get_bones) (void*);
        };

        namespace Weapon {
            inline void (*SpawnGrenade) (void*, int);
            inline bool (*get_shooting) (void*);
        };
    };

    namespace LocalPlayer {
        inline void (*Update) (void*);
        inline void (*TryShoot) (void*);
        inline void (*SetWeapon) (void*, int, bool);
    };

    namespace Grenade {
        inline void (*Update) (void*);
        inline void (*OnDisable) (void*);
    };

    namespace FirstPersonLook {
        inline void (*Update) (void*);
    };

    namespace FirstPersonMovement {
        inline void (*Update) (void*);
        inline void (*TryJump) (void*);
    };

    namespace Component {
        inline void *(*get_transform) (void*);
    };

    namespace Transform {
        inline void (*set_position) (void*, Vector3);
        inline Vector3 (*get_position) (void*);
    };

    namespace Camera {
        inline Vector3 (*WorldToScreenPoint) (void*, Vector3);

        namespace CameraManager {
            inline void *(*get_CameraManager) (void*);
        };
    };
    
    namespace Physics {
        inline bool (*Raycast) (Vector3, Vector3, RaycastHit&, float, int);
    };

    namespace PhotonView {
        inline void (*OnDestroy) (void*);
    };

    namespace Shader {
        inline void *(*Find) (MonoString*);
    };

    namespace Material {
        inline void (*SetShader) (void*, void*);
        inline void (*SetTexture) (void*, MonoString*, void*);
        inline void (*SetFloat) (void*, MonoString*, float);
        inline void (*SetColor) (void*, MonoString*, Color);
    };

    namespace Renderer {
        inline void *(*get_material) (void*);
    };

    namespace SettingsRender {
        inline void (*set_fog) (bool);
        inline void (*set_fogColor) (Color);
        inline void (*set_fogDensity) (float);
        inline void (*set_fogMode) (int);
        inline void (*set_ambientMode) (int);
        inline void (*set_ambientSkyColor) (Color);
    };

    namespace GlobalDetectors {
        inline void (*ObscuredDetected) (void*);
        inline void (*SpeedDetected) (void*);
        inline void (*TimeDetected) (void*);
        inline void (*WallDetected) (void*);
        inline void (*RadarDetected) (void*);
        inline void (*RecoilDetected) (void*);
    };

    namespace AudioManager {
        inline void (*PlayAudioClipFromArray) (void*, monoArray<void**>*, bool);
    };
};