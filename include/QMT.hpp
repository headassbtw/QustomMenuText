
#pragma once
#include "modloader/shared/modloader.hpp"
#include <stdint.h> // Required due to a beatsaber-hook bug.
#include "main.hpp"
#include "HMUI/ViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

namespace QustomMenuText{
    namespace UI{
        void GameplayCoreInstaller();
        void MainFlowCoordinator();
        void MainMenuViewController();
        void MainSettingsModelSO();
        void MainSystemInit();
        void ParametricBoxFakeGlowController();
        void PyramidBloomMainEffectSO();
        void TubeBloomPrePassLight();
        void VRRenderingParamsSetup();
    }
    void Install();
}
DECLARE_CLASS_CODEGEN(QustomMenuText, MainViewController, HMUI::ViewController,
                      DECLARE_INSTANCE_FIELD(bool, _requireRestart); // Used to tell our ViewController when DidDeactivate is run to soft-restart our game.

                      DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
                      DECLARE_OVERRIDE_METHOD(void, DidDeactivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidDeactivate", 2), bool removedFromHierarchy, bool screenSystemDisabling);
                      )