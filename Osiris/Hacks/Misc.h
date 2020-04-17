#pragma once

#include "../Memory.h"
#include "../Interfaces.h"
#include "../SDK/FrameStage.h"
#include "../SDK/UserCmd.h"
#include "../SDK/WeaponId.h"
#include "../SDK/NetworkChannel.h"
#include "../SDK/Entity.h"
#include "../SDK/Client.h"
#include "../SDK/GameEvent.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/Surface.h"

namespace Misc
{
    void edgejump(UserCmd* cmd) noexcept;
    void slowwalk(UserCmd* cmd) noexcept;
    void inverseRagdollGravity() noexcept;
    void updateClanTag(bool = false) noexcept;
    void spectatorList() noexcept;
    void sniperCrosshair() noexcept;
    void recoilCrosshair() noexcept;
    void watermark() noexcept;
    void prepareRevolver(UserCmd*) noexcept;
    void fastPlant(UserCmd*) noexcept;
    void drawBombTimer() noexcept;
	void drawBombDamage() noexcept;
    void stealNames() noexcept;
    void disablePanoramablur() noexcept;
    void quickReload(UserCmd*) noexcept;
    bool changeName(bool, const char*, float) noexcept;
    void bunnyHop(UserCmd*) noexcept;
	void humanBunnyHop(UserCmd*) noexcept;
    void fakeBan(bool = false) noexcept;
    void nadePredict() noexcept;
    void quickHealthshot(UserCmd*) noexcept;
    void fixTabletSignal() noexcept;
    void fakePrime() noexcept;
    void killMessage(GameEvent& event) noexcept;
	void fixMovement(UserCmd* cmd, float yaw) noexcept;
    void antiAfkKick(UserCmd* cmd) noexcept;
    void fixAnimationLOD(FrameStage stage) noexcept;
    void autoPistol(UserCmd* cmd) noexcept;
    void chokePackets(bool& sendPacket) noexcept;
    void autoReload(UserCmd* cmd) noexcept;
    void revealRanks(UserCmd* cmd) noexcept;
    void autoStrafe(UserCmd* cmd) noexcept;
    void removeCrouchCooldown(UserCmd* cmd) noexcept;
    void moonwalk(UserCmd* cmd) noexcept;
    void playHitSound(GameEvent& event) noexcept;
    void knifeLeft() noexcept;

	static float actualFov = 0.0f;

	constexpr void drawAimbotFov() noexcept
	{
		if (config.misc.drawAimbotFov && interfaces.engine->isInGame())
		{
			auto localPlayer = interfaces.entityList->getEntity(interfaces.engine->getLocalPlayer());
			if (!localPlayer || !localPlayer->isAlive() || !localPlayer->getActiveWeapon()) return;
			int weaponId = getWeaponIndex(localPlayer->getActiveWeapon()->itemDefinitionIndex2());
			if (!config.aimbot[weaponId].enabled) weaponId = 0;
			if (!config.aimbot[weaponId].enabled) return;
			auto [width, heigth] = interfaces.surface->getScreenSize();
			if (config.aimbot[weaponId].silent)
				interfaces.surface->setDrawColor(255, 10, 10, 255);
			else interfaces.surface->setDrawColor(10, 255, 10, 255);
			float radius = std::tan(degreesToRadians(config.aimbot[weaponId].fov / 2.f)) / std::tan(degreesToRadians(actualFov / 2.f)) * width;
			interfaces.surface->drawOutlinedCircle(width / 2, heigth / 2, radius, 100);
		}
	}
}
