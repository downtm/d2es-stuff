#include <iostream>
#include "../../Includes/ClientCore.cpp"
#include "../../Includes/itemPrefix.h"
#include "../../Includes/itemSuffix.h"
#include "ItemWatcher.h"

BOOL PRIVATE Radius(char** argv, int argc);
BOOL PRIVATE GoldSpeed(char** argv, int argc);
BOOL PRIVATE MinGold(char** argv, int argc);
BOOL PRIVATE ToggleShowItemLevel(char** argv, int argc);
BOOL PRIVATE ReloadItemDefs(char** argv, int argc);

ItemWatcher itemWatcher;
bool enabled = true;
bool waitingForItemPickup = false;

BOOL PRIVATE Enable(char** argv, int argc)
{
	server->GameInfof("Pick Enabled");
	enabled = true;

	return TRUE;
}

BOOL PRIVATE Disable(char** argv, int argc)
{
	server->GameInfof("Pick Disabled");
	enabled = false;

	return TRUE;
}

BOOL PRIVATE Toggle(char** argv, int argc)
{
	if(enabled)
		return Disable(argv, argc);

	return Enable(argv, argc);
}


BOOL PRIVATE SetTownPickup(char **argv, int argc)
{
	if(argc == 3)
	{
		itemWatcher.SetTownPickup(atoi(argv[2]) == 1);
		return TRUE;
	}

	server->GameErrorf("Invalid input, correct usage is .pick townpick n");
	return FALSE;
}

BOOL PRIVATE Radius(char** argv, int argc)
{
	if(argc == 3)
	{
		itemWatcher.SetRadius(atoi(argv[2]));
		return TRUE;
	}

	server->GameErrorf("Invalid input, correct usage is .pick radius n");
	return FALSE;
}

BOOL PRIVATE GoldSpeed(char** argv, int argc)
{
	if (argc == 3)
	{
		itemWatcher.SetGoldSpeed(atoi(argv[2]));
		return TRUE;
	}

	server->GameErrorf("Invalid input, correct usage is .pick goldspeed n");
	return FALSE;
}

BOOL PRIVATE Mute(char** argv, int argc)
{
	itemWatcher.Mute();
	return TRUE;
}

BOOL PRIVATE Items(char **argv, int argc)
{
	itemWatcher.TogglePickItems();
	return TRUE;
}

BOOL PRIVATE MinGold(char** argv, int argc)
{
	if(argc == 3)
	{
		itemWatcher.SetMinGold(atoi(argv[2]));
		return TRUE;
	}

	server->GameErrorf("Invalid input, correct usage is .pick min n");
	return FALSE;
}

BOOL PRIVATE ToggleShowItemLevel(char** argv, int argc)
{
	waitingForItemPickup = !waitingForItemPickup;

	if(waitingForItemPickup)
	{
		server->GameInfof("Waiting for item pickup to cursor...");
	}
	else
	{
		server->GameInfof("No longer waiting for item pick to cursor");
	}

	return TRUE;
}

BOOL PRIVATE ShowColors(char** argv, int argc)
{
	server->GameStringf("�c1 1 - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c2 2 - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c3 3 - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c4 4 - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c5 5 - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c6 6 - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c7 7 - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c8 8 - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c9 9 - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c; ; - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c: : - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c0 0 - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c/ / - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c( ( - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c++ - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");
	server->GameStringf("�c- - - abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+1234567890-=");

	return TRUE;
}

BOOL PRIVATE ReloadItemDefs(char** argv, int argc)
{
	server->GamePrintInfo("Reloading item definitions...");

	if(!itemWatcher.LoadItems())
	{
		server->GamePrintError("There was an error loading the item files");
	}

	return TRUE;
}

////////////////////////////////////////////
//
//               EXPORTS
//
/////////////////////////////////////////////


CLIENTINFO
(
	0,1,
	"",
	"",
	"Gold picker",
	""
)

MODULECOMMANDSTRUCT ModuleCommands[]=
{
	{
		"help",
		OnGameCommandHelp,
		"help�c0 List commands available in this module.\n"
		"<command> help�c0 Shows detailed help for <command> in this module."
	},
	{
		"on",
		Enable,
		"Enable pick"
	},
	{
		"off",
		Disable,
		"Diable pick"
	},
	{
		"toggle",
		Toggle,
		"Toggle pick"
	},
	{
		"mute",
		Mute,
		"Mute/unmute pick"
	},
	{
		"unmute",
		Mute,
		"Mute/unmute pick"
	},
	{
		"radius",
		Radius,
		"Set radius, default = 4"
	},
	{
		"goldspeed",
		GoldSpeed,
		"Set gold pickup speed, default = 1. 3 risks disconnects, above will disconnect."
	},
	{
		"min",
		MinGold,
		"Set minimum gold to pickup, default = 50"
	},
	{
		"lvl",
		ToggleShowItemLevel,
		"Shows the item level"
	},
	{
		"colors",
		ShowColors,
		"Displays sample colors"
	},
	{
		"reload",
		ReloadItemDefs,
		"Reloads the item definitions"
	},
	{
		"townpick",
		SetTownPickup,
		"Sets town pickit on or off. Args: 1|0"
	},
	{
		"items",
		Items,
		"Toggles picking of items"
	},
	{NULL}
};

VOID EXPORT OnGameLeave(THISGAMESTRUCT* thisgame)
{
	itemWatcher.OnGameLeave();
}

VOID EXPORT OnGameJoin(THISGAMESTRUCT* thisgame)
{
	itemWatcher.OnGameJoin();
}

BOOL EXPORT OnClientStart()
{
	if(!itemWatcher.LoadItems())
	{
		server->GameErrorf("Failed to load item tables. Do you have pickItems.txt?");
		server->GameErrorf(" in the plugin directory?");
		return FALSE;
	}

	enabled = true;

	return TRUE;
}

int ticksLeft = 3;
DWORD EXPORT OnGameTimerTick()
{
	if(enabled)
	{
		itemWatcher.OnTick();
	}

	return 0;
}

VOID EXPORT OnUnitMessage(UINT nMessage, LPCGAMEUNIT lpUnit, WPARAM wParam, LPARAM lParam)
{
	if(nMessage == UM_DESTROY)
	{
		if(lpUnit->dwUnitType == UNIT_TYPE_ITEM)
		{
			itemWatcher.OnItemDestroy(lpUnit->dwUnitID);
		}
	}
}

#include "ItemStatNames.cpp"
void DumpItemInfo(const ITEM& item)
{
	char chatBuff[128];
	char itemColor[4];

	if (false)
	{
		server->GameStringf("STATS:");
		GAMEUNIT unit;
		unit.dwUnitID = item.dwItemID;
		unit.dwUnitType = UNIT_TYPE_ITEM;

		for (size_t i = 0; i < sizeof(StatNames)/sizeof(StatNames[0]); i++)
		{
			auto statValue = server->GetUnitStat(&unit, i);
			if (statValue != 0)
			{
				server->GameStringf(" [%d] %s = %d", i, StatNames[i], statValue);
			}
		}
	}

	switch(item.iQuality)
	{
		case ITEM_QUALITY_MAGIC:
			strcpy_s(itemColor, 4, "�c3");
			break;
		case ITEM_QUALITY_RARE:
			strcpy_s(itemColor, 4, "�c9");
			break;
		case ITEM_QUALITY_CRAFT:
			strcpy_s(itemColor, 4, "�c8");
			break;
		default:
			return;
	}

	server->GameStringf("%s%s�c0 affixes:", itemColor, server->GetItemName(item.szItemCode));

	for(int i = 0; i < 3; i++)
	{
		if(item.wPrefix[i] != 0)
		{
			if(item.wPrefix[i] > ITEM_PREFIX_COUNT)
			{
				server->GameStringf("Prefix too large: %d", item.wPrefix[i]);
			}
			else
			{
				sprintf(chatBuff, "  �c;Prefix�c0 %d: %s - %s",item.wPrefix[i], Prefix[item.wPrefix[i]], PrefixDetails[item.wPrefix[i]]);
				server->GamePrintString(chatBuff);
			}
		}
	}
	for(int i = 0; i < 3; i++)
	{
		if(item.wSuffix[i] != 0)
		{
			if(item.wSuffix[i] > ITEM_SUFFIX_COUNT)
			{
				server->GameStringf("Suffix too large: %d", item.wSuffix[i]);
			}
			else
			{
				sprintf(chatBuff, "  �c:Suffix�c0 %d: %s - %s", item.wSuffix[i], Suffix[item.wSuffix[i]], SuffixDetails[item.wSuffix[i]]);
				server->GamePrintString(chatBuff);
			}
		}
	}


}
DWORD EXPORT OnGamePacketBeforeSent(BYTE* aPacket, DWORD aLen)
{
	if(aPacket[0] == 0x68)
	{
		itemWatcher.OnGameLeave();
	}

	return aLen;
}

VOID EXPORT OnGamePacketAfterReceived(BYTE* aPacket, DWORD aLen)
{   

	if(enabled && (aPacket[0] == 0x9c || aPacket[0] == 0x9d))
	{
		ITEM item;
		if (!server->ParseItem(aPacket, aLen, item))
		{
			return;
		}

		if(aPacket[1] == ITEM_ACTION_FROM_STORAGE || aPacket[1] == ITEM_ACTION_PICK_UP || aPacket[1] == ITEM_ACTION_TO_CURSOR)
		{
			if(waitingForItemPickup)
			{
				server->GameStringf("%s: Level %d", item.szItemCode, item.iLevel);
				DumpItemInfo(item);
			}
		}
		else
		{
			itemWatcher.OnItemAction(item);
		}
	}
}
