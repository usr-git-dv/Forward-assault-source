#pragma once

#include "core/features/functions.hpp"

    inline std::string logg;
    inline std::string log_skinned;

namespace hooks {
    namespace Player {
        void Update (void*);
    };

    namespace LocalPlayer {
        void Update (void*);
    };

    namespace Grenade {
        void Update (void*);
        void OnDisable (void*);
    };
    
    namespace FirstPersonLook {
        void Update (void*);
    };

    namespace FirstPersonMovement {
        void Update (void*);
    };

    namespace Physics {
        bool Raycast (Vector3, Vector3, RaycastHit&, float, int);
    };

    namespace PhotonView {
        void OnDestroy (void*);
    };

    namespace SettingsRender {
        void set_fog (bool);
        void set_fogColor (Color);
        void set_fogDensity (float);
        void set_fogMode (int);
        void set_ambientMode (int);
        void set_ambientSkyColor (Color);
    };

    namespace GlobalDetectors {
        void ObscuredDetected (void*);
        void SpeedDetected (void*);
        void TimeDetected (void*);
        void WallDetected (void*);
        void RadarDetected (void*);
        void RecoilDetected (void*);
    };

    namespace AudioManager {
        void PlayAudioClipFromArray (void*, monoArray<void**>*, bool);
    };
};