#ifndef ENUM_COLLECTION_H
#define ENUM_COLLECTION_H

namespace Enums
{
	enum LogEnum { EMenu, EStart, EGameOver, EGameEnd };
	enum PrintEnum { EBattlePrint, EStatusPrint, EShopRoomPrint, ERestRoomPrint, EBuffDebuffRoomPrint };
	//SetConsoleTextAttribute에서 색상을 16가지 사용하고, 여기에 사용될 인덱스는 텍스트상에서 해당 알파벳으로 전환해서 가져왔음
	enum ImageColor { a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p };
	//PrintLog() 사용시, 두 번째 인자로 해당 값 전달해주면 해당 이미지 출력됨. 아직 이미지 없는 경우 JustString으로
	enum EnumPrintLog { ECharacter, EGoblin, EOrc, ETroll, EWolf, ESlime, EGoblinRider, ETwinHeadTroll, ETreant, EDragon, EJustString };
}

#endif