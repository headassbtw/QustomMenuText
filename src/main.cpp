#include "main.hpp"
#include "TMPro/TextMeshPro.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/ShaderWarmupSceneSetup.hpp"
#include <fstream>
#include <sstream>
#include "HMUI/CurvedCanvasSettings.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "System/String.hpp"
#include "System/IO/Stream.hpp"
#include "System/IO/FileStream.hpp"
#include "System/IO/File.hpp"
#include "System/IO/Path.hpp"
#include "System/Linq/Enumerable.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/AssetBundle.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Color32.hpp"
#include "UnityEngine/UI/Outline.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/Random.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Texture.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/RectTransform_Axis.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/utils.h"


static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup
// Loads the config from disk using our modInfo, then returns it for use

static TMPro::TextMeshPro* mainText = nullptr;
static TMPro::TextMeshPro* bottomText = nullptr;

static std::string textPath = "";
//static std::vector<std::vector<std::string>> allEntries; defined in the header
UnityEngine::GameObject* logo = nullptr;
static UnityEngine::GameObject* textPrefab = nullptr;

static std::vector<std::vector<std::string>> readFromFile() {
    if(textPath == "") textPath = bs_utils::getDataDir(modInfo) + "/MenuText.txt";
    getLogger().info("reading from file-");
    //the list of entries to return
    std::vector<std::vector<std::string>> entriesInFile;

    //if the text file doesn't exist, create one and write an entry to it
    if(!fileexists(textPath)){
        std::ofstream MTFile(textPath);

        MTFile << "Empty File\n/sdcard/ModData/com.beatgames.beatsaber/Mods/QustomMenuText/MenuText.txt";

        MTFile.close();
    }


    //creates a stream from the file, and a temporary line and entry to store stuff to
    std::ifstream infile(textPath);
    std::string line;
    std::vector<std::string> currentEntry;
    while (std::getline(infile, line))
    {
        
        entriesInFile.clear();
        //strips out comments, doesn't do anything if the line begins with "#"
        if (line[0] == '#') {}
        else if (line[0] != '#') {

            getLogger().info("line:");


            //commits entry when a new line is detected
            if (line == "" || line[0] == '\n') {
                entriesInFile.push_back(currentEntry);
                currentEntry.clear();
                getLogger().info("added entry");
            }
            else {
                //commits current line to entry
                currentEntry.push_back(line);
            }
        }
    }
    if (currentEntry.size() != 0)
    {
        //just in case the last entry doesn't have a new line
        entriesInFile.push_back(currentEntry);
    }
    if(entriesInFile.empty())
        getLogger().info("no entries");
    return entriesInFile;
}

static UnityEngine::Color SetSaturation(UnityEngine::Color in, float saturation) {

    UnityEngine::Color tmp = in;
    float h;
    float s;
    float v;
    UnityEngine::Color::RGBToHSV(in, h, s, v);

    return UnityEngine::Color::HSVToRGB(h, saturation, v);

}

static void tmpColorer(TMPro::TextMeshPro* in, UnityEngine::Color cl) {
    if(!in) return;

    UnityEngine::Material* tempMat = in->get_fontMaterial();
    UnityEngine::Color tmpGlowColor = cl;
    tmpGlowColor.a = 0.5f;
    if(HasFakeGlow) tempMat->SetColor(il2cpp_utils::createcsstr("_GlowColor"), cl);
    if(!HasFakeGlow) tempMat->SetColor(il2cpp_utils::createcsstr("_GlowColor"), UnityEngine::Color::get_clear());

    tempMat->SetColor(il2cpp_utils::createcsstr("_FaceColor"), SetSaturation(cl, 0.65f));
}




static void setText(std::vector<std::string> lines) {

    if(!mainText || !bottomText) return;
    if (lines.size() <= 0) return;
    else if (lines.size() == 2) {
        mainText->SetText(il2cpp_utils::newcsstr(lines[0]));
        bottomText->SetText(il2cpp_utils::newcsstr(lines[1]));
    }
    else {
        mainText->set_color(UnityEngine::Color::get_blue());
        tmpColorer(mainText, UnityEngine::Color::get_blue());
        bottomText->SetText(il2cpp_utils::createcsstr(""));

        UnityEngine::Vector3 newPos = mainText->get_transform()->get_position();
        newPos.y = (newPos.y + bottomText->get_transform()->get_position().y) / 2;
        mainText->get_transform()->set_localPosition(newPos);


        std::string temp;
        for (std::string line : lines)
        {
            temp += line + "\n";
        }
        mainText->set_text(il2cpp_utils::newcsstr(temp));
    }
}
void setText_Simple(std::string str1, std::string str2){
    std::vector<std::string> entrs;
    entrs.push_back(str1);
    if(str2 != "") entrs.push_back(str2);
    setText(entrs);
}
static void pickRandomEntry() {
    try
    {
        srand(time(nullptr));


        int entryPicked = rand() % allEntries.size();
        setText(allEntries[entryPicked]);
    }
    catch (std::exception &e)
    {
        std::vector<std::string> currentEntry;

        currentEntry.push_back(("i almost crashed the game"));
        currentEntry.push_back(("this is not a joke it legit did"));

        setText(currentEntry);

    }
}

Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

static UnityEngine::GameObject* loadTextPrefab() {
    try
    {
        Il2CppString* bundleFile = il2cpp_utils::createcsstr(bs_utils::getDataDir(modInfo) + "/Fonts/NeonTubes2");

        UnityEngine::AssetBundle* textBundle = UnityEngine::AssetBundle::LoadFromFile(bundleFile);

        getLogger().info("Loaded Bundle");

        return textBundle->LoadAsset<UnityEngine::GameObject*>(il2cpp_utils::createcsstr("Text"));

    }
    catch (const std::exception&)
    {
        getLogger().warning("fuck");
        return nullptr;
    }
    
}

MAKE_HOOK_MATCH(MainMenuViewController_DidActivate, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    allEntries = readFromFile();


#pragma region AssetBundle Loading
    try
    {
        if(!textPrefab) textPrefab = loadTextPrefab();
    }
    catch (const std::exception&)
    {
        getLogger().critical("Failed to load AssetBundle!");
    }
#pragma endregion
    MainMenuViewController_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    getLogger().info("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
#pragma region yeetDefaultLogo
    //leaving these here for later when i decide to add image replacement support
    /*
        UnityEngine::GameObject* beat1 = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("BatLogo"));
        UnityEngine::GameObject* saber1 = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("SaberLogo"));
        UnityEngine::GameObject* e = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("EFlickering"));
        beat1->SetActive(false);
        saber1->SetActive(false);
        e->SetActive(false);*/

        if(!logo) logo = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("Logo"));
        if(logo->get_activeInHierarchy() == true)  logo->SetActive(false);
#pragma endregion
    if (!textPrefab) textPrefab = loadTextPrefab();
    // Logo Top Pos : 0.63, 18.61, 26.1
    // Logo Bottom Pos : 0, 14, 26.1
    
    UnityEngine::Color topColor = UnityEngine::Color::get_red();
    UnityEngine::Color bottomColor = UnityEngine::Color::get_blue();

#pragma region TopText
    if (mainText == nullptr) {
        UnityEngine::GameObject* mt = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("CustomMenuText"));
        if (mt) { mainText = mt->GetComponent<TMPro::TextMeshPro*>(); }
    }
    if (mainText == nullptr) {
        UnityEngine::GameObject* textObj = UnityEngine::GameObject::Instantiate(textPrefab);
        textObj->set_name(il2cpp_utils::createcsstr("CustomMenuText"));
        textObj->SetActive(false);
        mainText = textObj->GetComponent<TMPro::TextMeshPro*>();
        if(mainText == nullptr){
            getLogger().info("main text was null, adding component");
            mainText = textObj->AddComponent<TMPro::TextMeshPro*>();
        }
            if(mainText != nullptr)
                getLogger().info("wait main text isn't null???");
        UnityEngine::MeshRenderer* mainMaterial = textObj->GetComponent<UnityEngine::MeshRenderer*>();
        mainText->set_alignment(TMPro::TextAlignmentOptions::Center);
        mainText->set_fontSize(12);
        UnityEngine::RectTransform* mtRt = mainText->get_rectTransform();
        mtRt->SetSizeWithCurrentAnchors(UnityEngine::RectTransform::Axis::Vertical, 2.0f);
        mtRt->SetSizeWithCurrentAnchors(UnityEngine::RectTransform::Axis::Horizontal, 2.0f);
        mainText->set_richText(true);
        UnityEngine::Transform* toTr = mainText->get_transform();
        toTr->set_localScale(toTr->get_localScale() * 3.7f);
        mainText->set_overflowMode(TMPro::TextOverflowModes::Overflow);
        mainText->set_enableWordWrapping(false);
        textObj->SetActive(true);
        getLogger().info("Done with top text");
    }
    UnityEngine::Vector3 topPos(0.0f, 18.61f, 26.1f);
    mainText->get_transform()->set_position(topPos);
    tmpColorer(mainText, topColor);
    mainText->set_text(il2cpp_utils::createcsstr("FUCKIN"));
#pragma endregion
   
#pragma region BottomText //BOTTOM TEXT
    if (bottomText == nullptr) {
        UnityEngine::GameObject* bt = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("CustomMenuText-Bot"));
        if (bt) { bottomText = bt->GetComponent<TMPro::TextMeshPro*>(); }
    }
    if (bottomText == nullptr) {
        //UnityEngine::GameObject::Instantiate(textPrefab);
        UnityEngine::GameObject* textObj = UnityEngine::GameObject::Instantiate(textPrefab);
        textObj->set_name(il2cpp_utils::createcsstr("CustomMenuText-Bot"));
        textObj->SetActive(false);
        bottomText = textObj->GetComponent<TMPro::TextMeshPro*>();
        if(bottomText == nullptr){
            getLogger().info("bottom text was null, adding component");
            bottomText = textObj->AddComponent<TMPro::TextMeshPro*>();
        }
        bottomText->set_alignment(TMPro::TextAlignmentOptions::Center);
        bottomText->set_fontSize(12);
        UnityEngine::RectTransform* btRt = bottomText->get_rectTransform();
        btRt->SetSizeWithCurrentAnchors(UnityEngine::RectTransform::Axis::Vertical, 2.0f);
        btRt->SetSizeWithCurrentAnchors(UnityEngine::RectTransform::Axis::Horizontal, 2.0f);
        bottomText->set_richText(true);
        UnityEngine::Transform* toTr = bottomText->get_transform();
        toTr->set_localScale(toTr->get_localScale() * 3.7f);
        bottomText->set_overflowMode(TMPro::TextOverflowModes::Overflow);
        bottomText->set_enableWordWrapping(false);
        textObj->SetActive(true);
        getLogger().info("Done with BOTTOM TEXT");
    }
    UnityEngine::Vector3 botPos = UnityEngine::Vector3(0.0f, 14.0f, 26.1f);
    bottomText->get_transform()->set_localPosition(botPos);
    tmpColorer(bottomText, bottomColor);
    bottomText->set_text(il2cpp_utils::createcsstr("BEES"));
#pragma endregion

    pickRandomEntry();
}




// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = "QustomMenuText";
    info.version = "0.1.1";
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");

}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    QustomMenuText::Install();
    HasFakeGlow = true;


    getLogger().info("Installing hooks...");
    // Install our hooks (none defined yet)

    INSTALL_HOOK(getLogger(), MainMenuViewController_DidActivate);



    getLogger().info("Installed all hooks!");
}
