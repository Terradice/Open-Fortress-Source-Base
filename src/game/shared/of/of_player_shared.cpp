// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFPlayerShared
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_weapon_base.h"
#include "of_shareddefs.h"
#include "of_player_shared.h"
#include "of_gamerules.h"
#include "of_item.h"

#ifdef CLIENT_DLL
	#include "c_of_player.h"
#else
	#include "of_player.h"
#endif

// Data Tables
#ifdef CLIENT_DLL

BEGIN_PREDICTION_DATA_NO_BASE(COFPlayerShared)
	DEFINE_PRED_FIELD(m_nPlayerState, FIELD_INTEGER, FTYPEDESC_INSENDTABLE),
END_PREDICTION_DATA()

#else

#endif

//OFSTATUS: INCOMPLETE
COFPlayerShared::COFPlayerShared()
{
	field_0x324 = 0.0;
	m_bAllowedToPickUpFlag = true;
	m_nPlayerState = TF_STATE_ACTIVE;
}

//OFSTATUS: INCOMPLETE
COFPlayerShared::~COFPlayerShared()
{
}

//OFSTATUS: INCOMPLETE
float COFPlayerShared::GetCritMult()
{
	float flCritCalc = field_0x324 * 0.003921569;

	flCritCalc = clamp(flCritCalc, 0, 1.0);

	return (flCritCalc * 3.0) + 1.0;
}

/*
bool COFPlayerShared::InCond(ETFCond eCond) const
{
	char cVar1;
	uint *puVar2;

	if ((int)eCond < 32) //0x20)
	{
		cVar1 = CTFConditionList::InCond((CTFConditionList *)&this->field_0xe0, eCond);
		if (cVar1 != '\0')
		{
			return true;
		}
		puVar2 = &this->field_0xcc;
	}
	else
	{
		if ((int)eCond < 0x80)
		{
			if ((int)eCond < 0x60)
			{
				if ((int)eCond < 0x40)
				{
					puVar2 = &this->field_0xd0;
					eCond = eCond - 0x20;
				}
				else
				{
					puVar2 = &this->field_0xd4;
					eCond = eCond - 0x40;
				}
			}
			else
			{
				puVar2 = &this->field_0xd8;
				eCond = eCond - 0x60;
			}
		}
		else
		{
			puVar2 = &this->field_0xdc;
			eCond = eCond - 0x80;
		}
	}
	return (*puVar2 >> (eCond & 0x1f) & 1) != 0;
}
*/

//OFSTATUS: INCOMPLETE
// OFTODO: condition system is needed to even finish this
bool COFPlayerShared::CanAttack(int iFlags)
{
	return true;
	/*
	int *piVar1;
	char cVar2;
	int iVar3;
	int iVar4;
	bool bVar5;
	byte local_11;

	if (this[0x23dc] == (CTFPlayer)0x0)
	{
		bVar5 = true;
		if (this[0x1e54] == (CTFPlayer)0x0)
		{
			piVar1 = *(int **)PTR__g_pGameRules_00e340a8;
			if ((*(float *)(this + 0x1c78) < (*PTR__gpGlobals_00e34080)->curtime ||
				*(float *)(this + 0x1c78) == (*PTR__gpGlobals_00e34080)->curtime) ||
				(((byte)this[0x1a8c] & 1) != 0)) {
				local_11 = 1;
				cVar2 = CTFConditionList::InCond((CTFConditionList *)(this + 0x1a98), 4);

				if (cVar2 == '\0')
				{
					local_11 = ((byte)this[0x1a84] & 0x10) >> 4;
				}

				if (((param_1 & 1U) == 0) && (local_11 != 0))
				{
					return false;
				}
			}
			else
			{
				if ((param_1 & 1U) == 0)
				{
					return false;
				}
			}
			if (this[0x1c24] == (CTFPlayer)0x0)
			{
				cVar2 = CTFConditionList::InCond((CTFConditionList *)(this + 0x1a98), 7);
				if (cVar2 == '\0')
				{
					if (((byte)this[0x1a84] & 0x80) == 0)
					{
						cVar2 = CTFConditionList::InCond((CTFConditionList *)(this + 0x1a98), 0xe);
						if (cVar2 == '\0')
						{
							if (((byte)this[0x1a85] & 0x40) == 0)
							{
								if (piVar1[0xdd] == 5) 
								{
									iVar3 = (**(code **)(*piVar1 + 700))(piVar1);
									iVar4 = CBaseEntity::GetTeamNumber((CBaseEntity *)this);
									if (iVar3 != iVar4)
									{
										return false;
									}
								}
								if (((byte)this[0x1a8e] & 4) == 0)
								{
									iVar3 = CAttributeManager::AttribHookValue<int>
										(0, "no_attack", (CBaseEntity *)this, (CUtlVector *)0x0, true);
									bVar5 = iVar3 == 0;
								}
								else
								{
									bVar5 = false;
								}
							}
							else
							{
								bVar5 = false;
							}
						}
						else {
							bVar5 = false;
						}
					}
					else {
						bVar5 = false;
					}
				}
				else {
					bVar5 = false;
				}
			}
			else {
				bVar5 = false;
			}
		}
	}
	else {
		bVar5 = false;
	}
	return bVar5;
	*/
}

// OFSTATUS: COMPLETE
bool COFPlayerShared::IsAllowedToPickUpFlag() const
{
	// attributes stuff
	return m_bAllowedToPickUpFlag;
}

//=========================================================
// Non-COFPlayerShared Functions
//=========================================================

void COFPlayer::SetItem(COFItem *pItem)
{
	m_hItem = pItem;

	#ifdef GAME_DLL

	if (!pItem)
	{
		//RemoveGlowEffect();
	}
	else
	{
		//AddGlowEffect();

		if (pItem->GetItemID() == OF_ITEM_FLAG)
		{
			//RemoveInvisibility();
		}
	}

	#endif
}

bool COFPlayer::HasItem() const
{
	return (m_hItem != NULL);
}

COFItem *COFPlayer::GetItem() const
{
	return m_hItem;
}

COFWeaponBase *COFPlayer::GetActiveOFWeapon() const
{
	return dynamic_cast< COFWeaponBase* >(GetActiveWeapon());
}

COFWeaponBase *COFPlayer::Weapon_OwnsThisID(int iWeaponID) const
{
	for (int i = 0; i < MAX_WEAPONS; i++)
	{
		COFWeaponBase* pWeapon = dynamic_cast<COFWeaponBase*>(GetWeapon(i));
		if (pWeapon && pWeapon->GetWeaponID() == iWeaponID)
		{
			return pWeapon;
		}
	}
	
	return NULL;
}

void COFPlayer::SetOffHandWeapon(COFWeaponBase *pWeapon)
{
	m_hOffHandWeapon = pWeapon; // Server: 0x20c8, Client: 0x1c0c

	if (m_hOffHandWeapon)
	{
		m_hOffHandWeapon->Deploy();
	}
}

void COFPlayer::HolsterOffHandWeapon()
{
	if (m_hOffHandWeapon)
	{
		m_hOffHandWeapon->Holster(NULL);
	}
}

// this is called "TeamFortress_SetSpeed" but cmon, who wants to type all that out
// filled with conditions, attributes, and my guess econ weapons, also passtime
// ive placed "TeamFortress_CalculateMaxSpeed in here as everything else in TeamFortress_SetSpeed is the above
void COFPlayer::SetSpeedOF()
{
	float flMaxSpeed = 0.0;

	// this will never happen as the game will just crash before this can even execute
	//if (!OFGameRules()) SetMaxSpeed(0.0);

	// field_0xb0c = m_afPhysicsFlags
	if (IsObserver())
	{
		if (GetObserverMode() == OBS_MODE_ROAMING)
		{
			SetMaxSpeed(GetPlayerClassData(OF_CLASS_SCOUT)->m_flMaxSpeed);
		}

		SetMaxSpeed(flMaxSpeed);
		return;
	}

	// CanPlayerMove is filled with matchmaking
	// instead just check if we've restarted the round, if so, ya get frozen
	if (m_Class.m_iClass == OF_CLASS_UNDEFINED || OFGameRules()->InRoundRestart())
	{
		SetMaxSpeed(1.0);
		return;
	}

	flMaxSpeed = GetPlayerClassData(m_Class.m_iClass)->m_flMaxSpeed;

	// OFTODO: conditions + spy disguising
	/*
	if (m_Shared.InCond(TF_COND_DISGUISED) && !m_Shared.InCond(TF_COND_STEALTHED))
	{
		flMaxSpeed = GetPlayerClassData(m_nDisguiseClass)->m_flMaxSpeed; // 0x1abc - 6584 = 260 = m_nDisguiseClass
	}

	// mvm checks here, heck you
	if (m_Shared.InCond(TF_COND_AIMING))
	{
		int iClass = (m_Class.m_iClass);

		switch (iClass)
		{
		// minigun aiming/firing
		case OF_CLASS_HEAVY:
			flMaxSpeed = 110.0;
			break;
		// sniper rifle scope
		case OF_CLASS_SNIPER:
			flMaxSpeed = 80.0;
			break;
		}
	}
	*/

	SetMaxSpeed(flMaxSpeed);
}

// why is g_TFClassViewVectors hardcoded along a vector? and when only the z would be the only thing you'd be changing????
// instead ill add it to the class data
Vector &COFPlayer::GetClassEyeHeight()
{
	static Vector vecClassHeight = Vector(0.0, 0.0, GetPlayerClassData(m_Class.m_iClass)->m_iEyeHeight);
	return vecClassHeight;
}

void COFPlayer::RemoveDisguise()
{
	//if (m_Shared.InCond(TF_COND_DISGUISING) || m_Shared.InCond(TF_COND_DISGUISED))
	//{
	//	m_Shared.RemoveDisguise();
	//}
}

// empty on purpose
void COFPlayer::SetAnimation(PLAYER_ANIM playerAnim)
{
}