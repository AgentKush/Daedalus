#pragma once
#include "Mod/Mod.h"
#include <string>
#include <vector>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

class MusicRadioMod : public Mod
{
public:
    MusicRadioMod()
    {
        ModName = "MusicRadioMod";
        ModVersion = "0.3.0";
        ModDescription = "Adds music playback to the placeable Music Radio";
        ModAuthors = "AgentKush";
        ModLoaderVersion = "2.3.0";

        ModRef = this;
        CompleteModCreation();
    }

    virtual void InitializeMod() override;
    virtual void InitGameState() override;
    virtual void BeginPlay(UE4::AActor* Actor) override;
    virtual void PostBeginPlay(std::wstring ModActorName, UE4::AActor* Actor) override;
    virtual void DX11Present(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRenderTargetView) override;
    virtual void DX12Present(IDXGISwapChain* pSwapChain, ID3D12GraphicsCommandList* pCommandList) override;
    virtual void OnModMenuButtonPressed() override;
    virtual void DrawImGui() override;

private:
    // Radio state
    bool radioPlaced = false;
    bool isPlaying = false;
    int currentTrackIndex = 0;
    int volume = 80; // 0-100

    // Track list
    std::vector<std::string> trackNames;
    std::vector<std::wstring> trackPaths;
    std::wstring audioFolder;

    // Actor tracking
    std::vector<UE4::AActor*> radioActors;

    // Audio functions
    void ScanForTracks();
    void PlayTrack(int index);
    void StopPlayback();
    void NextTrack();
    void PrevTrack();
    void SetVolume(int vol);
    void TogglePlayback();
    
    // Helpers
    std::wstring GetAudioFolderPath();
    bool IsRadioActor(const std::string& className);
};
