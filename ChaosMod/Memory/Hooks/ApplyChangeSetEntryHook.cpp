#include <stdafx.h>

#include "Memory/Hooks/Hook.h"

// Thanks to FiveM - https://github.com/citizenfx/fivem/blob/master/code/components/gta-core-five/src/PatchFilterDLC.cpp
struct ChangeSetEntry
{
	struct DataFile
	{
		char name[128];
	} *dataFile;

	int type;
	// ...
};

void (*OG_ApplyChangeSetEntryStub)(ChangeSetEntry *entry);
void HK_ApplyChangeSetEntryStub(ChangeSetEntry *entry)
{
	static const std::unordered_set<std::string> badFiles {
		"dlc_mpG9EC:/x64/levels/gta5/vehicles/mpG9EC.rpf",
		"dlc_mpG9EC:/x64/levels/mpg9ec/vehiclemods/vehlivery3_mods.rpf",
		"dlc_mpG9ECCRC:/common/data/levels/gta5/vehicles.meta",
		"dlc_mpG9ECCRC:/common/data/carcols.meta",
		"dlc_mpG9ECCRC:/common/data/carvariations.meta",
		"dlc_mpG9ECCRC:/common/data/handling.meta",
		"dlc_mpG9ECCRC:/common/data/shop_vehicle.meta",
		"dlc_mpG9EC:/x64/levels/mpg9ec/vehiclemods/arbitergt_mods.rpf",
		"dlc_mpG9EC:/x64/levels/mpg9ec/vehiclemods/astron2_mods.rpf",
		"dlc_mpG9EC:/x64/levels/mpg9ec/vehiclemods/cyclone2_mods.rpf",
		"dlc_mpG9EC:/x64/levels/mpg9ec/vehiclemods/ignus2_mods.rpf",
		"dlc_mpG9EC:/x64/levels/mpg9ec/vehiclemods/s95_mods.rpf",
		"dlc_mpG9EC:/x64/levels/gta5/props/Prop_Exc_01.rpf",
		"dlc_mpG9EC:/x64/levels/gta5/props/exc_Prop_Exc_01.ityp",
		"dlc_mpG9EC:/x64/levels/gta5/props/Prop_tr_overlay.rpf",
		"dlc_mpG9EC:/x64/levels/gta5/props/exc_Prop_tr_overlay.ityp",
		"dlc_mpG9EC:/x64/anim/creaturemetadata.rpf",
		"dlc_mpG9EC:/common/data/effects/peds/first_person_alternates.meta",
		"dlc_mpG9ECCRC:/common/data/mp_m_freemode_01_mpg9ec_shop.meta",
		"dlc_mpG9EC:/x64/models/cdimages/mpg9ec_male.rpf",
		"dlc_mpG9ECCRC:/common/data/mp_f_freemode_01_mpg9ec_shop.meta",
		"dlc_mpG9EC:/x64/models/cdimages/mpg9ec_female.rpf",

		"dlc_mpSum2_g9ec:/x64/levels/mpsum2_g9ec/vehiclemods/feltzer3hsw_mods.rpf",
		"dlc_mpSum2_g9ec:/x64/levels/mpsum2_g9ec/vehiclemods/vigero2hsw_mods.rpf",
		"dlc_mpSum2_g9ec:/x64/models/cdimages/mpSum2_g9ec_female.rpf",
		"dlc_mpSum2_g9ec:/x64/models/cdimages/mpSum2_g9ec_female_p.rpf",
		"dlc_mpSum2_g9ec:/x64/models/cdimages/mpSum2_g9ec_male.rpf",
		"dlc_mpSum2_g9ec:/x64/models/cdimages/mpSum2_g9ec_male_p.rpf",
		"dlc_mpSum2_g9ecCRC:/common/data/mp_f_freemode_01_mpSum2_g9ec_shop.meta",
		"dlc_mpSum2_g9ecCRC:/common/data/mp_m_freemode_01_mpSum2_g9ec_shop.meta",
		"dlc_mpSum2_g9ec:/x64/anim/creaturemetadata.rpf",
		"dlc_mpSum2_g9ec:/common/data/effects/peds/first_person_alternates.meta",
		"dlc_mpSum2_g9ec:/common/data/effects/peds/first_person.meta",
		"dlc_mpSum2_g9ecCRC:/common/data/pedalternatevariations.meta",

		"dlc_mpChristmas3_G9EC:/x64/levels/mpChristmas3_G9EC/vehiclemods/entity3hsw_mods.rpf",
		"dlc_mpChristmas3_G9EC:/x64/levels/mpChristmas3_G9EC/vehiclemods/issi8hsw_mods.rpf",

		"dlc_mp2023_01_G9EC:/common/data/overlayinfo.xml",
		"dlc_mp2023_01_G9EC:/x64/levels/gta5/mp2023_01_g9ec_additions/mp2023_01_g9ec_additions.rpf",
		"dlc_mp2023_01_G9EC:/x64/levels/gta5/mp2023_01_g9ec_additions/mp2023_01_g9ec_additions_metadata.rpf",
		"dlc_mp2023_01_G9EC:/x64/levels/mp2023_01_G9EC/vehiclemods/buffalo5hsw_mods.rpf",
		"dlc_mp2023_01_G9EC:/x64/levels/mp2023_01_G9EC/vehiclemods/coureurhsw_mods.rpf",
		"dlc_mp2023_01_G9EC:/x64/levels/mp2023_01_G9EC/vehiclemods/monstrocitihsw_mods.rpf",
		"dlc_mp2023_01_G9EC:/x64/levels/mp2023_01_G9EC/vehiclemods/stingertthsw_mods.rpf",

		"dlc_mp2023_02_G9EC:/common/data/overlayinfo.xml",
		"dlc_mp2023_02_G9EC:/common/data/interiorProxies.meta",
		"dlc_mp2023_02_G9EC:/x64/levels/gta5/mp2023_02_g9ec_additions/mp2023_02_g9ec_additions.rpf",
		"dlc_mp2023_02_G9EC:/x64/levels/gta5/mp2023_02_g9ec_additions/mp2023_02_g9ec_additions_metadata.rpf",
		"dlc_mp2023_02_G9EC:/x64/levels/gta5/interiors/int_placement_m23_2_g9ec.rpf",
		"dlc_mp2023_02_G9EC:/x64/levels/gta5/interiors/mp2023_02_dlc_int_3.rpf",
		"dlc_mp2023_02_G9EC:/x64/levels/mp2023_02_G9EC/vehiclemods/vivanitehsw_mods.rpf",

		"dlc_mp2024_01_G9EC:/common/data/overlayinfo.xml",
		"dlc_mp2024_01_G9EC:/common/data/interiorProxies.xml",
		"dlc_mp2024_01_G9EC:/x64/levels/gta5/interiors/int_placement_m24_1_g9ec.rpf",
		"dlc_mp2024_01_G9EC:/x64/levels/gta5/interiors/m24_1_dlc_int_02.rpf",
		"dlc_mp2024_01_G9EC:/x64/levels/mp2024_01_g9ec/vehiclemods/eurosx32hsw_mods.rpf",
		"dlc_mp2024_01_G9EC:/x64/levels/mp2024_01_g9ec/vehiclemods/niobehsw_mods.rpf",

		"dlc_mp2024_02_G9EC:/x64/levels/mp2024_02_G9EC/vehiclemods/banshee3hsw_mods.rpf",
		"dlc_mp2024_02_G9EC:/x64/levels/mp2024_02_G9EC/vehiclemods/firebolthsw_mods.rpf",
		"dlc_mp2024_02_G9EC:/common/data/weaponArchetypes.meta",
		"dlc_mp2024_02_G9EC:/x64/models/cdimages/weapons.rpf",
		"dlc_mp2024_02_G9EC:/common/data/shop_weapon.meta",
		"dlc_mp2024_02_G9ECCRC:/common/data/ai/loadouts.meta",
		"dlc_mp2024_02_G9ECCRC:/common/data/pedpersonality.meta",
		"dlc_mp2024_02_G9ECCRC:/common/data/pickups.meta",
		"dlc_mp2024_02_G9ECCRC:/common/data/ai/weapon_strickler.meta",
		"dlc_mp2024_02_G9ECCRC:/common/data/ai/weaponanimations.meta",
		"dlc_mp2024_02_G9ECCRC:/common/data/ai/weaponcomponents.meta",

		"dlc_mp2025_01_G9EC:/x64/levels/mp2025_01_G9EC/vehiclemods/tampa4hsw_mods.rpf",
		"dlc_mp2025_01_G9EC:/x64/levels/mp2025_01_G9EC/vehiclemods/woodlanderhsw_mods.rpf"
	};

	if (entry->type == 6 || entry->type == 7 || !entry->dataFile || !badFiles.contains(entry->dataFile->name))
		OG_ApplyChangeSetEntryStub(entry);
}

static bool OnHook()
{
	if (IsLegacy())
	{
		Handle handle;

		handle = Memory::FindPattern("48 8D 0C 40 48 8D 0C CE E8 ? ? ? ? FF C3");
		if (!handle.IsValid())
			return false;

		Memory::AddHook(handle.At(8).Into().Get<void>(), HK_ApplyChangeSetEntryStub, &OG_ApplyChangeSetEntryStub);
	}

	return true;
}

static RegisterHook registerHook(OnHook, nullptr, "_ApplyChangeSetEntryStub");