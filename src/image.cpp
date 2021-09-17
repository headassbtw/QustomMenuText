#include "main.hpp"
#include "System/String.hpp"
#include "System/IO/Stream.hpp"
#include "System/IO/FileStream.hpp"
#include "System/IO/File.hpp"
#include "System/IO/Path.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/SpriteMeshType.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/ImageConversion.hpp"
#include <fstream>
#include <iterator>
#include <cstdio>
#include <vector>


UnityEngine::GameObject* BatLogo = nullptr;
UnityEngine::GameObject* ELogo = nullptr;
UnityEngine::GameObject* SaberLogo = nullptr;

void ClearAll(){
    BatLogo = nullptr;
    ELogo = nullptr;
    SaberLogo = nullptr;
}

void FindLogos(){
    if(BatLogo == nullptr)
        UnityEngine::GameObject* BatLogo = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("BatLogo"));
    if(SaberLogo == nullptr)
        UnityEngine::GameObject* SaberLogo = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("SaberLogo"));
    if(ELogo == nullptr)
        UnityEngine::GameObject* ELogo = UnityEngine::GameObject::Find(il2cpp_utils::createcsstr("EFlickering"));
}


UnityEngine::Texture2D* LoadPNG(std::string filePath)
{
    std::ifstream instream(filePath, std::ios::in | std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
    Array<uint8_t>* bytes = il2cpp_utils::vectorToArray(data);
    UnityEngine::Texture2D* texture = UnityEngine::Texture2D::New_ctor(0, 0, UnityEngine::TextureFormat::RGBA32, false, false);
    UnityEngine::ImageConversion::LoadImage(texture, bytes, false);
    return texture;
}

UnityEngine::Sprite* SpriteFromPNG(std::string filePath){
    UnityEngine::Texture2D* texture = LoadPNG(filePath);
    return UnityEngine::Sprite::Create(texture, UnityEngine::Rect(0.0f, 0.0f, (float)texture->get_width(), (float)texture->get_height()), UnityEngine::Vector2(0.5f,0.5f), 1024.0f, 1u, UnityEngine::SpriteMeshType::FullRect, UnityEngine::Vector4(0.0f, 0.0f, 0.0f, 0.0f), false);

}

void Replace(UnityEngine::GameObject* gameObject, std::string imagePath){
    UnityEngine::SpriteRenderer* lsr = gameObject->GetComponent<UnityEngine::SpriteRenderer*>();
    UnityEngine::Texture2D* spng = LoadPNG(imagePath);
    UnityEngine::Rect* sRect = new UnityEngine::Rect(0, 0, 128, 128);
    lsr->set_sprite(SpriteFromPNG(imagePath));
}