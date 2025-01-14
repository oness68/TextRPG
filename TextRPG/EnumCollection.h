#ifndef ENUM_COLLECTION_H
#define ENUM_COLLECTION_H

namespace Enums
{
	enum LogEnum { Menu, Start, GameOver, GameEnd };
	enum PrintEnum { BattlePrint, StatusPrint, ShopRoomPrint, RestRoomPrint, BuffDebuffRoomPrint};
	enum ImageColor {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p};	//SetConsoleTextAttribute에서 색상을 16가지 사용하고, 여기에 사용될 인덱스는 텍스트상에서 해당 알파벳으로 전환해서 가져왔음
}

#endif