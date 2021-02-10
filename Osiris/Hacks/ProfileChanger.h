#pragma once
#include "../Protobuffs/ProtoWriter.h"
#include "../Protobuffs/Messages.h"
#include "../SDK/SteamAPI.h"
#include "../Protobuffs/Protobuffs.h"
#include "../Config.h"
#include "../ConfigStructs.h"
#include "../Memory.h"
#include "../Interfaces.h"
#include "../SDK/Engine.h"
#include "../SDK/NetworkChannel.h"
#define START_MUSICKIT_INDEX 1500000
#define START_ITEM_INDEX     2000000

namespace ProfileChanger
{
	struct wskin
	{
		int wId;
		int paintKit;
		int quality;
		float wear;
		int seed;
		std::string name;
		bool in_use_t;
		bool in_use_ct;
		int slot;
	};

	inline std::unordered_map<int, wskin> g_InventorySkins;

	class Inventory
	{
	public:
		void FixNullInventory(ProtoWriter& cache);
		void ClearEquipState(ProtoWriter& object);
		void AddAllItems(ProtoWriter& object);
		void AddItem(ProtoWriter& object, int index, int itemIndex, int rarity, int paintKit, int seed, float wear, std::string name);
		bool Presend(uint32_t& unMsgType, void* pubData, uint32_t& cubData);
		void ApplyMedals(ProtoWriter& object);
		static int GetAvailableClassID(int definition_index);
		std::string Changer(void* pubDest, uint32_t* pcubMsgSize);
	};

	inline Inventory* g_Inventory;

	struct ProfileChangerConfig {
		bool enabled = false;
		int friendly = 0;
		int teach = 0;
		int leader = 0;
		int rank = 0;
		int wins = 0;
		int level = 0;
		int exp = 0;
		int ban_type = 0;
		int ban_time = 0;
	} profileChangerConfig;

	void Apply() noexcept;

	// GUI
	void menuBarItem() noexcept;
	void tabItem() noexcept;
	void drawGUI(bool contentOnly) noexcept;

	// Config
	json toJson() noexcept;
	void fromJson(const json& j) noexcept;
	void resetConfig() noexcept;
}
