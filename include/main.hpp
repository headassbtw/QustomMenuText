#pragma once

// Include the modloader header, which allows us to tell the modloader which mod this is, and the version etc.
#include "modloader/shared/modloader.hpp"

// beatsaber-hook is a modding framework that lets us call functions and fetch field values from in the game
// It also allows creating objects, configuration, and importantly, hooking methods to modify their values
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "bs-utils/shared/utils.hpp"

#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "beatsaber-hook/shared/utils/utils.h"

#include "System/String.hpp"
#include "System/IO/FileStream.hpp"
#include "System/IO/File.hpp"

//some other shit i apparently need to put here :P
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/AssetBundle.hpp"
#include "System/Linq/Enumerable.hpp"


// Define these functions here so that we can easily read configuration and log information from other files
Configuration& getConfig();
Logger& getLogger();




//UnityEngine::GameObject loadTextPrefab(Il2CppString path);
