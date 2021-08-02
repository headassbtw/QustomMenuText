# Builds a .zip file for loading with BMBF
& $PSScriptRoot/build.ps1

if ($?) {
    Compress-Archive -Path "./libs/arm64-v8a/libQustomMenuText.so", "./libs/arm64-v8a/libbeatsaber-hook_1_1_5.so", "./Fonts/Beon", "./Fonts/NeonTubes2", "./Fonts/Teko", "./Fonts/ComicSansMS", "./Fonts/Impact", "./Fonts/SegoeUI", "./MenuText.txt", "./bmbfmod.json" -DestinationPath "./QustomMenuText_v0.1.0.zip" -Update
}
