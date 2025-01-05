#include "Player/LinkStateItem.hpp"
#include "Item/ItemManager.hpp"
#include "Player/EquipBomb.hpp"
#include "Player/EquipHammer.hpp"
#include "Player/EquipItem.hpp"
#include "Player/EquipScoop.hpp"
#include "Player/PlayerControl.hpp"
#include "Save/AdventureFlags.hpp"

extern unk32 func_ov000_020cf01c(s32 *param1);
extern void func_ov000_020cf9dc(s32 param1, s32 param2, s32 param3);
extern void func_ov014_0213ec64(s32 param1);
extern void func_ov014_0211fd04(s32 *param1);
extern void func_ov000_020b7e6c(s32 *param1);

extern s32 *data_027e103c;
extern s32 *data_027e1098;

THUMB void LinkStateItem::vfunc_00() {}

ARM LinkStateId LinkStateItem::GetId() {
    return 1;
}

ARM s32 LinkStateItem::IsHammerEquipped() {
    switch (this->mEquipId) {
        case 8: return 0;
        default: return -1;
    }
}

ARM void LinkStateItem::OnStateLeave(s32 param1) {
    EquipItem *pEVar1;
    LinkStateMove *pLVar2;
    s32 iVar3;
    unk32 *puVar4;

    LinkStateBase::OnStateLeave(param1);

    switch (this->mEquipId) {
        case 7:
            /* bombchu */
            iVar3 = func_ov000_020cf01c(data_027e103c);
            if (*(u8 *) (iVar3 + 0xe0) == '\0') {
                func_ov014_0213ec64((s32) GetEquipBombchu());
            }
            func_ov014_0211fd04(data_027e1098);
            break;
        case 0: break;
        case 1: break;
        case 2: break;
        case 4: EquipBomb::StopUsing(this, param1); break;
        case 5: break;
        case 6: EquipRope::StopUsing(this); break;
        case 8: EquipHammer::StopUsing(this); break;
        case 9:
        case 10:
            iVar3                                    = (int) (data_027e103c);
            *(unk8 *) ((s16 *) data_027e103c + 0x15) = 0;
            func_ov000_020cf9dc(iVar3, 0, 0);
            break;
        case 3: EquipScoop::StopUsing(this); break;
    }

    if (this->mEquipId != -1) {
        pEVar1 = this->GetEquipItem(this->mEquipId);
        pEVar1->vfunc_1c();
    }

    switch (this->mEquipId) {
        case -1:
        case 0: break;
        case 1: break;
        case 9:
        case 10: this->EquipItem_vfunc_28(); break;
        default:
            this->EquipItem_vfunc_28();
            if (param1 != 4 && param1 != 2) {
                pLVar2          = this->GetLinkStateMove();
                pLVar2->mUnk_14 = true;
            }
    }

    this->mNextEquip = -1;

    puVar4 = (unk32 *) this + 20;
    for (; puVar4 != (unk32 *) this + 22; puVar4++) {
        func_ov000_020b7e6c(puVar4);
    }
    if (gPlayerControl->mUnk_80 != false) {
        gPlayerControl->StopFollowing();
    }
    this->mUnk_25[1] = 0;
    return;
}

ARM EquipBombchu *LinkStateItem::GetEquipBombchu() {
    return (EquipBombchu *) ItemManager::GetEquipItemUnchecked(7);
}

ARM LinkStateMove *LinkStateItem::GetLinkStateMove() {
    return (LinkStateMove *) GetLinkState(0);
}

ARM bool LinkStateItem::func_ov00_020abf70() {
    return gAdventureFlags->func_ov00_02097b9c(this->mUnk_5c);
}

ARM bool LinkStateItem::vfunc_28() {
    return this->mUnk_5c < 0;
}
