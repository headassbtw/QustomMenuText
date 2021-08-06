#include "QMT.hpp"
#include "UI/MainFlowCoordinator.hpp"
#include "main.hpp"

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"

using namespace GlobalNamespace;
using namespace HMUI;
using namespace QuestUI;
using namespace UnityEngine;

DEFINE_TYPE(QustomMenuText, MainViewController);

namespace QustomMenuText{
    class testClass{
        public: static bool test;
    };
}

void QustomMenuText::Install(){
    custom_types::Register::AutoRegister();

    QuestUI::Init();
    QuestUI::Register::RegisterModSettingsViewController<QustomMenuText::MainViewController*>(ModInfo{"Menu Text", VERSION});

    //UI::MainFlowCoordinator();
    //UI::MainMenuViewController();
    //UI::MainSettingsModelSO();

}
void QustomMenuText::MainViewController::DidActivate(
        bool firstActivation,
        bool addedToHierarchy,
        bool screenSystemEnabling
        ) {
    if (firstActivation) {
        GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        if (OVRPlugin::GetSystemHeadsetType() == OVRPlugin::SystemHeadset::Oculus_Quest) {
            BeatSaberUI::CreateText(container->get_transform(), "<color=red>Detected Oculus Quest (1), certain tweaks *may* be unavailable.");
        }

        std::vector<std::string> entrTops;
        entrTops.push_back("balls");
        for(int i = 0; i < 10; i++)
        {
            entrTops.push_back("balls" + std::to_string(i));
        }



        BeatSaberUI::CreateDropdown(container->get_transform(), "Entry", "balls", entrTops,
                                    [](const std::string& value) {

        }
        );

        BeatSaberUI::CreateToggle(container->get_transform(), "Fake Glow", false,
                                  [](bool value) {
            HasFakeGlow = value;
            getLogger().info("AAARGH");
            if(value)
                getLogger().info("shitfuck");
        }
        );

    }
}

void QustomMenuText::MainViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
{
    getLogger().info("oi");
}