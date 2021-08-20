#include "QMT.hpp"
#include "UI/MainFlowCoordinator.hpp"
#include "main.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"
#include "System/IO/Stream.hpp"
#include "System/IO/FileStream.hpp"
#include <fstream>
#include <sstream>
#include "System/String.hpp"
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
std::string topString = "";
std::string bottomString = "";

void QustomMenuText::MainViewController::DidActivate(
        bool firstActivation,
        bool addedToHierarchy,
        bool screenSystemEnabling
        ) {
    if (firstActivation) {
        GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());

        std::vector<std::string> entrTops;
        entrTops.push_back("balls");
        entrTops.push_back("your mother");
        entrTops.push_back("i have no life");
        for(int i = 0; i < 10; i++)
        {
            //entrTops.push_back("balls" + std::to_string(i));
        }

        topString = currentTextEntry[0];
        if(currentTextEntry.size() >= 2)
            bottomString = currentTextEntry[1];
        else
            bottomString = "";

        /*BeatSaberUI::CreateDropdown(container->get_transform(), "Entry", "balls", entrTops, [](const std::string& value) {
            setText_Simple(value);
        }
        );*/

        BeatSaberUI::CreateStringSetting(container->get_transform(), "Top Text", topString,
                                         [](std::string value) {
            topString = value;
        });

        BeatSaberUI::CreateStringSetting(container->get_transform(), "Bottom Text", bottomString,
                                         [](std::string value) {
            bottomString = value;
        });

        UnityEngine::UI::Button* applyButton = BeatSaberUI::CreateUIButton(container->get_transform(), "Apply",
                                                           [this]() {
            setText_Simple(topString, bottomString);

            if(fileexists(textPath)) std::remove(textPath.c_str());
            std::ofstream MTFile(textPath);

            if(topString != "" && bottomString != ""){
                MTFile << topString;
                MTFile << "\n";
                MTFile << bottomString;
            }
            if(topString == "" && bottomString != ""){
                MTFile << bottomString;
            }
            if(topString == "" && bottomString == ""){
                MTFile << "BEAT\nSABER";
            }
            if(topString != "" && bottomString == ""){
                MTFile << topString;
                MTFile << "\n";
            }
            MTFile.close();
        });
        BeatSaberUI::AddHoverHint(applyButton->get_gameObject(), "Applies the text");


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