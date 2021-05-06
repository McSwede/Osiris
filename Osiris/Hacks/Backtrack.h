#pragma once

#include <algorithm>
#include <cstddef>
#include <deque>

#include "../JsonForward.h"

#include "../SDK/matrix3x4.h"
#include "../SDK/ModelRender.h"
#include "../SDK/NetworkChannel.h"

enum class FrameStage;
struct UserCmd;

#define OSIRIS_BACKTRACK() true

namespace Backtrack
{
    struct BacktrackConfig {
        bool enabled = false;
        bool ignoreSmoke = false;
        bool recoilBasedFov = false;
        int timeLimit = 200;
        int pingBasedVal = 0;
        bool pingBased = false;
        bool fakeLatency = false;
        bool drawAllTicks = false;
    } backtrackConfig;

    void update(FrameStage) noexcept;
    void run(UserCmd*) noexcept;
    void AddLatencyToNetwork(NetworkChannel*, float) noexcept;
    void UpdateIncomingSequences(bool reset = false) noexcept;

    struct Record {
        Vector origin;
        float simulationTime;
        matrix3x4 matrix[256];
    };

    const std::deque<Record>* getRecords(std::size_t index) noexcept;
    bool valid(float simtime) noexcept;
    
    struct IncomingSequence
    {
        int inreliablestate;
        int sequencenr;
        float servertime;
    };
    extern std::deque<IncomingSequence>sequences;

    float getExtraTicks() noexcept;
    void init() noexcept;

    // GUI
    void menuBarItem() noexcept;
    void tabItem() noexcept;
    void drawGUI(bool contentOnly) noexcept;

    // Config
    json toJson() noexcept;
    void fromJson(const json& j) noexcept;
    void resetConfig() noexcept;
}
