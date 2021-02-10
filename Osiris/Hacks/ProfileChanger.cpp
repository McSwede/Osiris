#include "ProfileChanger.h"

bool ProfileChanger::Inventory::Presend(uint32_t& unMsgType, void* pubData, uint32_t& cubData)
{
	uint32_t MessageType = unMsgType & 0x7FFFFFFF;

	if (MessageType == k_EMsgGCAdjustItemEquippedState) {

		ProtoWriter msg((void*)((DWORD)pubData + 8), cubData - 8, 19);

		if (!msg.has(CMsgAdjustItemEquippedState::item_id)
			|| !msg.has(CMsgAdjustItemEquippedState::new_class)
			|| !msg.has(CMsgAdjustItemEquippedState::new_slot))
			return true;

		uint32_t item_id = msg.get(CMsgAdjustItemEquippedState::item_id).UInt32();
		uint32_t new_class = msg.get(CMsgAdjustItemEquippedState::new_class).UInt32();

		memory->clientState->ForceFullUpdate();

		return false;
	}
	return true;
}

void ProfileChanger::Apply() noexcept
{
    write.SendClientHello();
    write.SendMatchmakingClient2GCHello();
}

static bool profileChangerOpen = false;

void ProfileChanger::menuBarItem() noexcept
{
    if (ImGui::MenuItem("Profile Changer")) {
        profileChangerOpen = true;
        ImGui::SetWindowFocus("Profile Changer");
        ImGui::SetWindowPos("Profile Changer", { 100.0f, 100.0f });
    }
}

void ProfileChanger::tabItem() noexcept
{
    if (ImGui::BeginTabItem("Profile Changer")) {
        drawGUI(true);
        ImGui::EndTabItem();
    }
}

void ProfileChanger::drawGUI(bool contentOnly) noexcept
{
    if (!contentOnly) {
        if (!profileChangerOpen)
            return;
        ImGui::SetNextWindowSize({ 290.0f, 0.0f });
        ImGui::Begin("Profile Changer", &profileChangerOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    }
    static const char* bans_gui[] =
    {
        "Off",
        "You were kicked from the last match (competitive cooldown)",
        "You killed too many teammates (competitive cooldown)",
        "You killed a teammate at round start (competitive cooldown)",
        "You failed to reconnect to the last match (competitive cooldown)",
        "You abandoned the last match (competitive cooldown)",
        "You did too much damage to your teammates (competitive cooldown)",
        "You did too much damage to your teammates at round start (competitive cooldown)",
        "This account is permanently untrusted (global cooldown)",
        "You were kicked from too many recent matches (competitive cooldown)",
        "Convicted by overwatch - majorly disruptive (global cooldown)",
        "Convicted by overwatch - minorly disruptive (global cooldown)",
        "Resolving matchmaking state for your account (temporary cooldown)",
        "Resolving matchmaking state after the last match (temporary cooldown)",
        "This account is permanently untrusted (global cooldown)",
        "(global cooldown)",
        "You failed to connect by match start. (competitive cooldown)",
        "You have kicked too many teammates in recent matches (competitive cooldown)",
        "Congratulations on your recent competitive wins! before you play competitive matches further please wait for matchmaking servers to calibrate your skill group placement based on your lastest performance. (temporary cooldown)",
        "A server using your game server login token has been banned. your account is now permanently banned from operating game servers, and you have a cooldown from connecting to game servers. (global cooldown)"
    };
    const char* ranks_gui[] = {
        "Off",
        "Silver 1",
        "Silver 2",
        "Silver 3",
        "Silver 4",
        "Silver elite",
        "Silver elite master",
        "Gold nova 1",
        "Gold nova 2",
        "Gold nova 3",
        "Gold nova master",
        "Master guardian 1",
        "Master guardian 2",
        "Master guardian elite",
        "Distinguished master guardian",
        "Legendary eagle",
        "Legendary eagle master",
        "Supreme master first class",
        "The global elite"
    };

    ImGui::Checkbox("Enabled##profile", &profileChangerConfig.enabled);
    ImGui::Text("Rank");
    ImGui::Combo("##Rank", &profileChangerConfig.rank, ranks_gui, ARRAYSIZE(ranks_gui));
    ImGui::Text("Level");
    ImGui::SliderInt("##Level", &profileChangerConfig.level, 0, 40);
    ImGui::Text("XP");
    ImGui::InputInt("##Xp##level", &profileChangerConfig.exp);
    ImGui::Text("Wins");
    ImGui::InputInt("##Wins", &profileChangerConfig.wins);
    ImGui::Text("Friend");
    ImGui::InputInt("##Friend", &profileChangerConfig.friendly);
    ImGui::Text("Teach");
    ImGui::InputInt("##Teach", &profileChangerConfig.teach);
    ImGui::Text("Leader");
    ImGui::InputInt("##Leader", &profileChangerConfig.leader);
    ImGui::Text("Fake ban type");
    ImGui::Combo("##fake-ban", &profileChangerConfig.ban_type, bans_gui, IM_ARRAYSIZE(bans_gui));
    ImGui::Text("Fake ban time");
    ImGui::InputInt("##fake-ban-time", &profileChangerConfig.ban_time);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (250 / 2) - (190 / 2) - 20.f);
    if (ImGui::Button("Apply", ImVec2(190, 30)))
    {
        Apply();
    }
    if (!contentOnly)
        ImGui::End();
}

static void to_json(json& j, const ProfileChanger::ProfileChangerConfig& o, const ProfileChanger::ProfileChangerConfig& dummy = {})
{
    WRITE("Enabled", enabled);
    WRITE("Friendly", friendly);
    WRITE("Teacher", teach);
    WRITE("Leader", leader);
    WRITE("Rank", rank);
    WRITE("Wins", wins);
    WRITE("Level", level);
    WRITE("Experience", exp);
    WRITE("Ban Type", ban_type);
    WRITE("Ban Time", ban_time);
}

json ProfileChanger::toJson() noexcept
{
    json j;
    to_json(j, profileChangerConfig);
    return j;
}

static void from_json(const json& j, ProfileChanger::ProfileChangerConfig& a)
{
    read(j, "Enabled", a.enabled);
    read(j, "Friendly", a.friendly);
    read(j, "Teacher", a.teach);
    read(j, "Leader", a.leader);
    read(j, "Rank", a.rank);
    read(j, "Wins", a.wins);
    read(j, "Level", a.level);
    read(j, "Experience", a.exp);
    read(j, "Ban Type", a.ban_type);
    read(j, "Ban Time", a.ban_time);
}

void ProfileChanger::fromJson(const json& j) noexcept
{
    from_json(j, profileChangerConfig);
}

void ProfileChanger::resetConfig() noexcept
{
    profileChangerConfig = { };
}