# Builds a .qmod file for loading with QuestPatcher
$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

$ArchiveName = "QustomMenuText_v0.2.4.qmod"
$TempArchiveName = "QustomMenuText_v0.2.4.qmod.zip"

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk
Compress-Archive -Path "./libs/arm64-v8a/libQustomMenuText.so", "./libs/arm64-v8a/libbeatsaber-hook_2_2_5.so", "./libs/arm64-v8a/libquestui.so", "./libs/arm64-v8a/libbs-utils.so", "./mod.json", "./NeonTubes2" -DestinationPath $TempArchiveName -Force
Move-Item $TempArchiveName $ArchiveName -Force
