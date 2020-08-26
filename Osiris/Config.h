#pragma once

#include <array>
#include <filesystem>
#include <memory>
#include <string>

#include "imgui/imgui.h"
#include "nSkinz/config_.hpp"
#include "ConfigStructs.h"

class Config {
public:
    explicit Config(const char*) noexcept;
    void load(size_t, bool incremental) noexcept;
    void save(size_t) const noexcept;
    void add(const char*) noexcept;
    void remove(size_t) noexcept;
    void rename(size_t, const char*) noexcept;
    void reset() noexcept;
    void listConfigs() noexcept;

    constexpr auto& getConfigs() noexcept
    {
        return configs;
    }

    struct Color {
        std::array<float, 3> color{ 1.0f, 1.0f, 1.0f };
        bool rainbow{ false };
        float rainbowSpeed{ 0.6f };
    };

    struct ColorToggle : public Color {
        bool enabled{ false };
    };

    struct Aimbot {
        bool enabled{ false };
        bool onKey{ false };
        int key{ 0 };
        int keyMode{ 0 };
        bool aimlock{ false };
        bool silent{ false };
        bool friendlyFire{ false };
        bool visibleOnly{ true };
        bool scopedOnly{ true };
        bool ignoreFlash{ false };
        bool ignoreSmoke{ false };
        bool autoShot{ false };
        bool autoScope{ false };
        float fov{ 0.0f };
        float smooth{ 1.0f };
        int bone{ 0 };
        float maxAimInaccuracy{ 1.0f };
        float maxShotInaccuracy{ 1.0f };
        int minDamage{ 1 };
        bool killshot{ false };
        bool betweenShots{ true };
		int shotsFired{ 1 };
		bool standaloneRecoilControl{ false };
		float recoilControlX{ 0.0f };
		float recoilControlY{ 0.0f };
    };
    std::array<Aimbot, 40> aimbot;

    struct Triggerbot {
        bool enabled = false;
        bool friendlyFire = false;
        bool scopedOnly = true;
        bool ignoreFlash = false;
        bool ignoreSmoke = false;
        bool killshot = false;
        bool onKey = false;
        int key = 0;
        int hitgroup = 0;
        int shotDelay = 0;
        int minDamage = 1;
        float burstTime = 0.0f;
		float maxAimInaccuracy{ 1.0f };
		float maxShotInaccuracy{ 1.0f };
    };
    std::array<Triggerbot, 40> triggerbot;

    struct Backtrack {
        bool enabled{ false };
        bool ignoreSmoke{ false };
        bool recoilBasedFov{ false };
        int timeLimit{ 0 };
		bool pingBased{ 0 };
        bool fakeLatency{ false };
		bool drawAllTicks{ false };
    } backtrack;

    struct AntiAim {
        bool enabled{ false };
        bool pitch{ false };
        bool yaw{ false };
        float pitchAngle{ 0.0f };
    } antiAim;

    struct Glow : ColorA {
        bool enabled{ false };
        bool healthBased{ false };
        int style{ 0 };
    };
    std::array<Glow, 21> glow;

    struct Chams {
        struct Material : ColorA {
            bool enabled = false;
            bool healthBased = false;
            bool blinking = false;
            bool wireframe = false;
            bool cover = false;
            bool ignorez = false;
            int material = 0;
        };
        std::array<Material, 7> materials;
    };

    std::unordered_map<std::string, Chams> chams;

    struct StreamProofESP {
        std::unordered_map<std::string, Player> allies;
        std::unordered_map<std::string, Player> enemies;
        std::unordered_map<std::string, Weapon> weapons;
        std::unordered_map<std::string, Projectile> projectiles;
        std::unordered_map<std::string, Shared> lootCrates;
        std::unordered_map<std::string, Shared> otherEntities;
    } streamProofESP;

    struct Font {
        ImFont* tiny;
        ImFont* medium;
        ImFont* big;
    };

    std::vector<std::string> systemFonts{ "Default" };
    std::unordered_map<std::string, Font> fonts;

    struct Visuals {
        bool disablePostProcessing{ false };
        bool inverseRagdollGravity{ false };
        bool noFog{ false };
        bool no3dSky{ false };
        bool noAimPunch{ false };
        bool noViewPunch{ false };
        bool noHands{ false };
        bool noSleeves{ false };
        bool noWeapons{ false };
        bool noSmoke{ false };
        bool noBlur{ false };
        bool noScopeOverlay{ false };
        bool noGrass{ false };
        bool noShadows{ false };
        bool wireframeSmoke{ false };
        bool zoom{ false };
        int zoomKey{ 0 };
        bool thirdperson{ false };
        int thirdpersonKey{ 0 };
        int thirdpersonDistance{ 0 };
        int viewmodelFov{ 0 };
        int fov{ 0 };
        int farZ{ 0 };
        int flashReduction{ 0 };
        float brightness{ 0.0f };
        int skybox{ 0 };
        ColorToggle world;
        ColorToggle sky;
        bool deagleSpinner{ false };
        int screenEffect{ 0 };
        int hitEffect{ 0 };
        float hitEffectTime{ 0.6f };
        int hitMarker{ 0 };
        float hitMarkerTime{ 0.6f };
        int playerModelT{ 0 };
        int playerModelCT{ 0 };

        struct ColorCorrection {
            bool enabled = false;
            float blue = 0.0f;
            float red = 0.0f;
            float mono = 0.0f;
            float saturation = 0.0f;
            float ghost = 0.0f;
            float green = 0.0f;
            float yellow = 0.0f;
        } colorCorrection;
    } visuals;

    std::array<item_setting, 36> skinChanger;

    struct Sound {
        int chickenVolume{ 100 };

        struct Player {
            int masterVolume{ 100 };
            int headshotVolume{ 100 };
            int weaponVolume{ 100 };
            int footstepVolume{ 100 };
        };

        std::array<Player, 3> players;
    } sound;

    struct Style {
        int menuStyle{ 0 };
        int menuColors{ 0 };
    } style;

	struct Misc {
		int menuKey{ 0x2D }; // VK_INSERT
		bool antiAfkKick{ false };
		bool autoStrafe{ false };
		bool bunnyHop{ false };
		bool humanBunnyHop{ false };
		bool customClanTag{ false };
		bool clocktag{ false };
		bool animatedClanTag{ false };
		bool fastDuck{ false };
		bool moonwalk{ false };
		bool edgejump{ false };
		bool slowwalk{ false };
		bool autoPistol{ false };
		bool autoReload{ false };
		bool autoAccept{ false };
		bool radarHack{ false };
		bool revealRanks{ false };
		bool revealMoney{ false };
		bool revealSuspect{ false };
		bool fixAnimationLOD{ false };
		bool fixBoneMatrix{ false };
		bool fixMovement{ false };
		bool disableModelOcclusion{ false };
		bool nameStealer{ false };
		bool disablePanoramablur{ false };
		bool killMessage{ false };
		bool nadePredict{ false };
		bool fixTabletSignal{ false };
		bool fakePrime{ false };
		bool fastPlant{ false };
		bool quickReload{ false };
		bool prepareRevolver{ false };
		bool oppositeHandKnife{ false };
		bool fastStop{ false };
		bool sniperCrosshair{ false };
		bool bombDamage{ false };
		bool drawAimbotFov{ false };
		int bhop_hit_chance{ 100 };
		int hops_restricted_limit{ 1 };
		int max_hops_hit{ 5 };
		char clanTag[16];
		int edgejumpkey{ 0 };
		int slowwalkKey{ 0 };
		ColorToggleThickness noscopeCrosshair;
		ColorToggleThickness recoilCrosshair;
		ColorToggle spectatorList;
		ColorToggle watermark;
		float aspectratio{ 0 };
		std::string killMessageString{ "Gotcha!" };
		int banColor{ 6 };
		std::string banText{ "Cheater has been permanently banned from official CS:GO servers." };
		ColorToggle bombTimer{ 1.0f, 0.55f, 0.0f };
		int prepareRevolverKey{ 0 };
		int hitSound{ 0 };
		int chokedPackets{ 0 };
		int chokedPacketsKey{ 0 };
		int quickHealthshotKey{ 0 };
		float maxAngleDelta{ 255.0f };
		int killSound{ 0 };
		std::string customKillSound;
		std::string customHitSound;
		PurchaseList purchaseList;

        struct Reportbot {
            bool enabled = false;
            bool textAbuse = false;
            bool griefing = false;
            bool wallhack = true;
            bool aimbot = true;
            bool other = true;
            int target = 0;
            int delay = 1;
            int rounds = 1;
        } reportbot;
    } misc;

    struct Wpos {
        float AimbotX{ 250.0f }; // wpos config .h //
        float AimbotY{ 250.0f };
        float AntiAimX{ 250.0f };
        float AntiAimY{ 250.0f };
        float TriggerBotX{ 250.0f };
        float TriggerBotY{ 250.0f };
        float BacktrackX{ 250.0f };
        float BacktrackY{ 250.0f };
        float GlowX{ 250.0f };
        float GlowY{ 250.0f };
        float ChamsX{ 250.0f };
        float ChamsY{ 250.0f };
        float EspX{ 250.0f };
        float EspY{ 250.0f };
        float VisualsX{ 250.0f };
        float VisualsY{ 250.0f };
        float SkinchangerX{ 250.0f };
        float SkinchangerY{ 250.0f };
        float SoundX{ 250.0f };
        float SoundY{ 250.0f };
        float StyleX{ 250.0f };
        float StyleY{ 250.0f };
        float MiscX{ 250.0f };
        float MiscY{ 250.0f };
        float ReportbotX{ 250.0f };
        float ReportbotY{ 250.0f };
        float ConfigX{ 250.0f };
        float ConfigY{ 250.0f };
        float Style2X{ 250.0f };
        float Style2Y{ 250.0f };
        float PurchaseListX{ 250.0f };
        float PurchaseListY{ 250.0f };
        float PurchaseListScaleX{ 200.0f };
        float PurchaseListScaleY{ 200.0f };

        const char* LockFlags[16] = { // "wpos Locks" //
            "Aimbot", "Anti Aim", "Triggerbot", "Backtrack",
            "Glow", "Chams", "Esp", "Visuals", "Skinchanger",
            "Sound", "Style", "Misc", "Reportbot", "Config",
            "Style2", "PurchaseList"
        };
        bool LockSelectedFlags[16] = {
            false, false, false, false,
            false, false, false, false,
            false, false, false, false,
            false, false, false, false
        };
    } wpos;

    void scheduleFontLoad(const std::string& name) noexcept;
    bool loadScheduledFonts() noexcept;

private:
    std::vector<std::string> scheduledFonts{ "Default" };
    std::filesystem::path path;
    std::vector<std::string> configs;
};

inline std::unique_ptr<Config> config;
