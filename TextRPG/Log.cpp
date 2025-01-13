#include "Log.h"

Log* Log::instance = nullptr;

Log* Log::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Log();
	}
	return instance;
}

//이미지 출력을 위해 알파벳을 인덱스로 전환시켜주는 메서드
int Log::CharToIndex(char c)
{
	return c - 'a';
}

//모니터 크기의 4분의 1 크기로 콘솔 창 크기를 설정하고 모니터 가운데로 띄워줌, 각 string타입 벡터에 이미지 텍스트 초기화(32X32 PNG파일을 0~15의 색상에 따라 알파벳으로 변환 -> 콘솔 색상 변환을 위해)
void Log::Initialize()
{
	//문자 크기로 콘솔 버퍼 크기 정하고 창 크기 설정해줌
	COORD bufferSize;
	bufferSize.X = bufferWidth;
	bufferSize.Y = bufferHeight;
	cout << bufferSize.X << ", " << bufferSize.Y << endl;
	SetConsoleScreenBufferSize(consoleHandle, bufferSize);
	SMALL_RECT windowSize = { 0, 0, bufferWidth - 1, bufferHeight - 1 };	//내부의 크기 조절
	SetConsoleWindowInfo(consoleHandle, true, &windowSize);

	MoveWindow(console, moniterScreenWidth / 4, moniterScreenHeight / 4, consoleWidth, consoleHeight, true);	//화면 가운데로 띄우고, 크기 조절

	this->playerData =
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaooggoaaaaaaaaaaaaaaaaa",
		"aaaaaaaaagoghhgoaaaaaaaaaaaaaaaa",
		"aaaaaaaaaoghhhhhaaaaaaaaaaaaaaaa",
		"aaaaaaaaagohahahaaaaaaaaaaaaaaaa",
		"aaaaaaaaagihihihaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaghihihaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaiiiaaaaaaaaaaaaaaapaa",
		"aaaaaaaaemmmiiimmeaaaaaaaaaappaa",
		"aaaaaaahemmeimieeehaaaaaaaapppaa",
		"aaaaaahiemeeeieeeehhaaaaaapppaaa",
		"aaaaaahiemmeememehhhaaaaapppaaaa",
		"aaaaaahiieeeeeemeihhaaaapppaaaaa",
		"aaaaaahiiaeeeeemeahhhaapppaaaaaa",
		"aaaaaahiiaeeeeemfaiihhhfpaaaaaaa",
		"aaaaaahiiaffngnnnaaaiihhaaaaaaaa",
		"aaaaaaiiaaefnnnfeaaaaiihaaaaaaaa",
		"aaaaaaiiammeeeemeeaanfaaaaaaaaaa",
		"aaaaaaihhmmeeeemeeaaaaaaaaaaaaaa",
		"aaaaaaaiiemmemeemeaaaaaaaaaaaaaa",
		"aaaaaaaiheemmmeemeaaaaaaaaaaaaaa",
		"aaaaaaaaibbbaaabbbaaaaaaaaaaaaaa",
		"aaaaaaaaabjbaaabjbaaaaaaaaaaaaaa",
		"aaaaaaaaabjbaaabjbaaaaaaaaaaaaaa",
		"aaaaaaaaabjbaaabjjaaaaaaaaaaaaaa",
		"aaaaaaaaajbbaaabbjaaaaaaaaaaaaaa",
		"aaaaaaaaajbbaaabbjaaaaaaaaaaaaaa",
		"aaaaaaaaameaaaaaemaaaaaaaaaaaaaa",
		"aaaaaaaameeaaaaaeemaaaaaaaaaaaaa",
		"aaaaaammmeeaaaaaeeemmaaaaaaaaaaa",
		"aaaaaaeeeeeaaaaaeeeeeaaaaaaaaaaa"
	};
	this->goblinData =
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaahaaahaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaheeeheaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaimmeieaaaaaaaaaaaaa",
		"aaaaaaaaaaaimemmmeeggaaaaaaaaaaa",
		"aaaaaaaaaaaammmmmmegaaaaaaaaaaaa",
		"aaaaaaaaaaaamoeeomeeaaaaaaaaaaaa",
		"aaaaaaaaaaaamemmmeeeaaaaaaaaaaaa",
		"aaaaaaaaaaaackkkccccaaaaaaaaaaaa",
		"aaaaaaaaaaaickaaakccaaaaaaaaaaaa",
		"aaaaaiiaaaiickaaakcaaaaaaaaaaaaa",
		"aaaaaiimeiiiickkkccaiiaaaaaaaaaa",
		"aaaaaiimmiaaicckccaiiiiaaaaaaaaa",
		"aaaaaaaaaaaaaiccccaiaiiaaaaaaaaa",
		"aaaaaaaaaaaaaaiccaiaaaeeaaaaaaaa",
		"aaaaaaaaaaaaagiaaigaaaiiiaaaaaaa",
		"aaaaaaaaaaaaaamggmeaaaiiiaaaaaaa",
		"aaaaaaaaaaaaaaimeeiaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaiimeeiiaaaaaaaaaaaa",
		"aaaaaaaaaaaaiiieeeiiiaaaaaaaaaaa",
		"aaaaaaaaaaaaiiaaaaaiiaaaaaaaaaaa",
		"aaaaaaaaaaaaameaaaemmaaaaaaaaaaa",
		"aaaaaaaaaaaaeeaaaaameaaaaaaaaaaa",
		"aaaaaaaaaaaiiiaaaaaiiiaaaaaaaaaa",
		"aaaaaaaaaaiiiaaaaaaiiiiaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->orcData =
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaiiiihiaaaaaaaaaaa",
		"aaaaaaaaaaaaaaiihhhiiiaaaaaaaaaa",
		"aaaaaaaaaaaaaaiihhiiiiiaaaaaaaaa",
		"aaaaaaaaaahhhhamiiiimaiihhhhaaaa",
		"aaaaaaaaaaaiiiiaaiiaaiiiiiaaaaaa",
		"aaaaaaaaaaaaipiiiipiiiiiiaaaaaaa",
		"aaaaaaaaaaaaaapmmmmpiiiaaaaaaaaa",
		"aaaaaaaaaaaaaiiiiiiimihhaaaaaaaa",
		"aaaaaaaaaaaiiiiiihiiiiihhaaaaaaa",
		"aaaaaaaaaaihhhhiiiiiihhihhaaaaaa",
		"aaaaaaaaaihiihhhhiihhhhihhhaaaaa",
		"aaaaaaaaihiiihhhhiihhhhihhhhaaaa",
		"aaaaaaaaihiiiiiiiiiiiiiiihhhaaaa",
		"aaaaaaaihhiihiiiiihiiiiiaiihiaaa",
		"aaaaaaahhiahihhhhhhhhhhiiaihiaaa",
		"aaaaaaahhiaihhhhhhhhhhhhiaihhaaa",
		"aaaaaahhhiaiihhhhhhhhhhhiaihhhaa",
		"aaaaahhhiaaihhhhhihhhhhiiaihhhaa",
		"aaaaahhiiaaaihhhhhhhhhiiaaaihhaa",
		"aaaaahiiaaaafffnhiihiinffaaiihaa",
		"aaaaaiiaaaaanffnfnnfnffnffaaiiaa",
		"aaaaaaaaaaafnifnffnffnfnnfaaaaaa",
		"aaaaaaaaaaafnhfnifnfnnhnhfaaaaaa",
		"aaaaaaaaaaanaihninnanihnhfaaaaaa",
		"aaaaaaaaaaaaahhhaananihhhaaaaaaa",
		"aaaaaaaaaaaaahhhiaaaaihhhaaaaaaa",
		"aaaaaaaaaaaaahhhiaaaaiihhaaaaaaa",
		"aaaaaaaaaaaahhhiiaaaaihhhaaaaaaa",
		"aaaaaaaaaaahhhihiaaaaiihhhaaaaaa",
		"aaaaaaaaaaaihiiiaaaaaaiiihaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->trollData =
	{
		"aaaaaaaaaaaaaaiihhaaaaaaaaaaaaaa",
		"aaaaaaanfaaaaihihihaaaaaaaaaaaaa",
		"aaaaaanfffaaaihhhhhaaaaaaaaaaaaa",
		"aaaaaannnfaaihaahaahaaaaaaaaaaaa",
		"aaaaanffffaaihhhhhhhaaaaaaaaaaaa",
		"aaaaannfffaaihhmmmmhhhaaaaaaaaaa",
		"aaaaanfnffhiiimmmmmmhihhiaaaaaaa",
		"aaaaanffffhiiimpeepmhihihhiaaaaa",
		"aaaahnnnfhhihiiiiiiiiiihhhhiaaaa",
		"aaahhhnnnhiiiiiiihhihhiihhhhiaaa",
		"aahhihnnfiaiihhhhhhhhhaiihhhhiaa",
		"aahhhinnfaiihhhhihhhhiaaaiiihhaa",
		"ahhhinnffaiihhhhihhhhiiaaahhhiaa",
		"ahhihnnnaaihiiiihhiiihiaaahhhhaa",
		"aihhhnnfaiihhhhhhhhhhiiaaaihhhaa",
		"aaihhhnfaiihhhhhhhhhhiiaaahhhiaa",
		"aaaihhhhaeihhhhhhhhhhhiaaiiihiaa",
		"aaaaihihaeeiihhhhhhhiieaiihhiaaa",
		"aaaaaiihaoeeiiiiaiiiieeaihhhiaaa",
		"aaaaanfaaooeemmiiiieeeoaaiiiaaaa",
		"aaaaafaagogoemmmmmmeeogoaaaaaaaa",
		"aaaaaaaaooogogoemmmgooooaaaaaaaa",
		"aaaaaaagogiogogogogoogogaaaaaaaa",
		"aaaaaaooooiooioooooiooioaaaaaaaa",
		"aaaaaaaoiogogigoigoigohaaaaaaaaa",
		"aaaaaaaaihhgiiioaoiihohhaaaaaaaa",
		"aaaaaaaaihhoiiaaaoiihhhiaaaaaaaa",
		"aaaaaaaiihhiiaaaaaiihiiaaaaaaaaa",
		"aaaaaaaiiihiiaaaaaaiihhaaaaaaaaa",
		"aaaaaaaihhhiaaaaaaaihihhhaaaaaaa",
		"aaaaaaaiiiiiaaaaaaaiiiiiiaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->wolfData =
	{
		"aaaaaaaaaaaahaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaahhaaaaaaaaaaaaaaaaaa",
		"ahaaaaaaaaahhiaaaaaaaaaaaaaaaaaa",
		"aihaaaaaaaahiaaaaaaaaaaaaaaaaaaa",
		"aaihaaaaaahiiaaaaaaaaaaaaaaaaaaa",
		"aaaihiiihhhiaaaaaaaaaaaaaaaaaaaa",
		"aaahihiiihhhaaaaaaaaaaaaaaaaaaaa",
		"aaahhiiihhhhhaaaaaaaaaaaaaaaaaaa",
		"aaahmhhhmmhhhaaaaaaaaaaaaaaaaaaa",
		"aaahhhihhhhhihaaaaaaaaaaaaaaaaaa",
		"aaahhiihhhhhhhhhaaaaaaaaaaaaaaaa",
		"aaaahhiihhhhhhhhhhaaaaaaaaaaaaaa",
		"aaaahiihhphihhhhhhhhaaaaaaaaaaaa",
		"aaaaipahmmhihhhhhhhhhaaaaaaaaaaa",
		"aaaaaaahmhiihhhhhhhhhhaaaaaaaaaa",
		"aaaaaihhhhihhhihhhhhhhhaaaaaaaaa",
		"aaaaaammiihhhhihhhhhhhhhaaaaaaaa",
		"aaaaaammhhhhhiihihhhhhhhhaaaaaaa",
		"aaaaaammihhhiihhihhhhhhhhhaaaaaa",
		"aaaaaamaihiiiihhiiihiihhhhaaaaaa",
		"aaaaaaaaihiiihhiiiiiiiihhhhaaaaa",
		"aaaaaaaaihaiihhiiiihiihhhhhaaaaa",
		"aaaaaaaahhhahhhiiihiihhhhhhaaaaa",
		"aaaaaaaahhhahhhiiihihhhhhhhaaaaa",
		"aaaaaaaahhhahhhaiihihhhhhhhaaiia",
		"aaaaaaahhhaaahhaiiihhhhhhhaaihhh",
		"aaaaaaahhhaaahhaiiiiiihhhhhihhah",
		"aaaaaaihhhaahhhhiiaaiihhaahhhaaa",
		"aaaaahhhhaaihhhhahhhhhhhaaaaaaaa",
		"aaaaahahaahhhhapahhhhhhaaaaaaaaa",
		"aaaaapapaapaapaaapapaapaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->slimeData =
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaakkkkkaaaaaaaaaaaaaa",
		"aaaaaaaaaaakkkkcckkkaaaaaaaaaaaa",
		"aaaaaaaaaakkkkclcdkkkaaaaaaaaaaa",
		"aaaaaaaaakkkkkccddkkkkaaaaaaaaaa",
		"aaaaaaaaakkkkkkddkkkkkkaaaaaaaaa",
		"aaaaaaaakkkkkkkkkkkkkkkaaaaaaaaa",
		"aaaaaaaakkkkkklckkkkkkkaaaaaaaaa",
		"aaaaaaaakcckkkcdkcckklckaaaaaaaa",
		"aaaaaaaklcckkkkkclcckccgaaaaaaaa",
		"aaaaaaakccdkkkkkcccdkkkkgaaaaaaa",
		"aaaaaakkkddkkkkkkddkgkkgkaaaaaaa",
		"aaaaaakkggkkkkcckkkkkcckgaaaaaaa",
		"aaaaakkkgkkkkkkckkkkccccgkaaaaaa",
		"aaaaakkkkkkkkggkkkkkcccdkkaaaaaa",
		"aaaakkkkkkkkglcggkkkkddgkggaaaaa",
		"aaakkckgkkkgllccgkgkkkkkkkgaaaaa",
		"aakkkcdgkkkgcccdkgggkkkkkkkkaaaa",
		"aakkkkkkkkkgggdgklcggkkkkkkgkaaa",
		"aaaakkkkkkggggkkkcdkgkkkkkggaaaa",
		"aaaaaaakkkggkkkkkggkkkkgaagaaaaa",
		"aaaaaaaakkggkgkkgkkkkkggaaaaaaaa",
		"aaaaaaaaakgaaggkggaaakgaaaaaaaaa",
		"aaaaaaaaaaaaaaggaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->goblinRiderData =
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaiaahaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaiccicaaaaaaaeaaaaaa",
		"aaaaaaaaaaaaiccccciiaaaamaaaaaaa",
		"aagaaaaaaaagacicccicaaamaaeaaaaa",
		"aaeaaaaaaaaeaocoiiccaamaaaaaaaaa",
		"aaagaaaaaagaaiiiicccaeaaaaiiihaa",
		"aaaaeaaaaeaaakcaccchiaaaiiihhiaa",
		"aaaaagaageaaakcaachiiaaiiihhiiaa",
		"aaaaieeeeiaeakcaachiaaaiiiiiiaaa",
		"aaaaieiiecgeeacccemaiaiihhhhaaaa",
		"aaaagghhggggeaaemeeiaihhhhiaaaaa",
		"aaaaoahiggogeehieeeaihhiiiihiiia",
		"aaaaggiiggggepieeeiiiiiiiihhhiaa",
		"aaaaagiiiggppiiiaiiiiiiiihiiiaaa",
		"aaaaaaiiiaapiaaiiaaiiiahhhhiaaaa",
		"aaaaaahahaaaaaeiaiahiidbaiaaaaaa",
		"aaaaaaaaaaaaaeiaaiaaidddbaaaaaaa",
		"aaaaaaaaaaaaeiaaaiaaahhhiaaaaaaa",
		"aaaaaaaaaaaiaaaaieagghhiiaaaaaaa",
		"aaaaaaaaaaaaaaaieaaoooccaaaaaaaa",
		"aaaaaaaaaaaaaiaeaaopgooggaaaaaaa",
		"aaaaaaaaaaaaaaaaaogoppgggaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaooggggaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->twinHeadTrollData =
	{
		"aaaaaaaaaaaahhhhaahhhhaaaanfaaaa",
		"aaaaaaanfaaihhhhhiihhhhaannnfaaa",
		"aaaaaannffahihiihihihihaannnnfaa",
		"aaaaaannnfhaahaahiaahaahafnnffaa",
		"aaaaanfnffhhhhhiihhhhhhhanffnfaa",
		"aaaaannfnfheeeehihheeeehhanfnfaa",
		"aaaaannfnfmmmemmihmmemmmhannnfaa",
		"aaaaannfffmpmmpmiimpmmpmhinffaaa",
		"aaaahnnnfhhhhhhhiihhhhhhiinnfaaa",
		"aaahhhnnnhiiiiiihhiiiiiihinnfaaa",
		"aahhihnnfiihhiihhhhhhhiiihnnfiaa",
		"aahhhinnfaihhhhhihhhhiiiannfhhaa",
		"ahhhinnffahihhhhihhhhiiaannfhiaa",
		"aihhhnnnaaihiiiihhiiiiiaannfhiaa",
		"aihhhnnfaihhhhhhhhhhhiiaaanfhiaa",
		"aaihhhnfaihhhhhhhhhhhiiaaanfhiaa",
		"aaaihhhhaaihhhhhhhhhhhiaainfhiaa",
		"aaaaihhhaaeihhhhhhhhiiaahhhhiaaa",
		"aaaaaihhageeiiihahiiiaaaihhhiaaa",
		"aaaaanfaaggeeeeiiiieeagaaiiiaaaa",
		"aaaaafaaggggeeeeeeeeegggaaaaaaaa",
		"aaaaaaaaggggogoeeeegggggaaaaaaaa",
		"aaaaaaagggiggogogogoggggaaaaaaaa",
		"aaaaaaggggigoioooooiggigaaaaaaaa",
		"aaaaaaagiggogigoigoigghiaaaaaaaa",
		"aaaaaaaaihhghiigaoiiighiaaaaaaaa",
		"aaaaaaaaihhohiaaaoiiihhhaaaaaaaa",
		"aaaaaaaihiihiaaaaaihhhhaaaaaaaaa",
		"aaaaaaaiihhhiaaaaaaiihhaaaaaaaaa",
		"aaaaaaaihhhhaaaaaaaihiihhaaaaaaa",
		"aaaaaaaiiiiiaaaaaaaiihhhhaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->treantData =
	{
		"aaaaaaaakkaakkkmaaaaaaaaaaaaaaaa",
		"aaaaaaaakkkkkkefmfeaaaaaaaaaaaaa",
		"aaaaaamkmekkmekefmkkaaaaaaaaaaaa",
		"aaaaamakekkkeekkmfmckkkaaaaaaaaa",
		"aaaaaaekkkkkkkkefmfekckkkkaaaaaa",
		"aaaaaefkkmmmmkkkefmekckkkooaaaaa",
		"aaaaaakkckkkkkafafcmkookccokaaaa",
		"aaaaaakkeccccckececccckkccookaaa",
		"aaaaaafkekccockkckkkkccokkkocaaa",
		"aaaaaaakkkccokccckkccccccocockaa",
		"aaaaaaakkcaackcckkkkcccccokkccaa",
		"aaaaaaakkcaaaaccckokkccccokkkkaa",
		"aaaaaaaokcaaackkckockkccaacckoaa",
		"aaaaaaaoccaaaakckkkcckccaaackoka",
		"aaaaaaaoccaaaackcckkccccaaaakock",
		"aaaaaaackkcaaaockckckcccaaaackka",
		"aaaaaaaakkcaaaokcccckcccaaaaccka",
		"aaaaaaakokcaaakkccccccccaaaackka",
		"aaaaaaakokcaaakccccackccaaaackka",
		"aaaaaakckcccaackcccaccccaaakckka",
		"aaaaakcccccaakkcccoackccaaakakca",
		"aaaackccaaaaakkcoccakkcaaaaoacck",
		"aaackccaaaaakkcoocaaakkcaaaoaoao",
		"aackkccaaaakkkccccaaakkckcaoaoao",
		"ackkckcaaaakcccccaaaaakkkaaoaoao",
		"akakckaaaaackcocaaaaaacckaaoaoao",
		"aoaoaoaaaaackccaaaaaaakckcaaaoao",
		"aoaoaoaaaaakcccaaaaaaackcccaaoao",
		"aoaoaoaaaaakckcaaaaaaackccaaaoao",
		"aaaoaoaaaakkkccaaaaaakckccaaaoaa",
		"aaaoaaaaaakkcccaaaaaakkkccaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	this->dragonData =
	{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aappphaaaaaaaaaaaaaaaaaaaaaaippa",
		"aaaaiiphhpiaaaaaaaaaaaihhppiiaaa",
		"aaaaaaaaiihpppaaaaapppiiaaaaaaaa",
		"aaaaaaaaaiphpiaaaaaaaaaaaaaaaaaa",
		"aaaaaaiiphihiiaaaahhphpidiiaaaaa",
		"aaaaihhiaiihphaahhphhphhpphiiiaa",
		"aahiiaaaiiiaaphhhhiiidhiipihaiia",
		"aaaaaaaiiaaaaabdhidbbbbdidphdaaa",
		"aaaaaaiiaaaaaaihidaaaaaabiiphaaa",
		"aaaaahaaaaaaaihiiaaaadaaadhhpdaa",
		"aaaaaaaaaahaaihidaaaaaiaaaihhdaa",
		"aaaaaaaaahiabiiiaaaaaaiaaahpiiaa",
		"aaaaaaaphiaaadidaaaaaaaaahhhdaaa",
		"aaaaaphhhpiiaaadaaaaaaaahphddaaa",
		"aaaapphffhpiiddaaaaaaaaphhiidaaa",
		"aaphphhfhhdhppipihhhhphhihdbaaaa",
		"appppphhhiidihpihhiihhhihdbaaaaa",
		"apaaaihidhibdhddddhdhdidbbaaaaaa",
		"aaaaaahdaaaaaadbiababdaaaaaaaaaa",
		"aaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaidaaaaadaaaaaaabaadaaaaaaaa",
		"aaaaabaaaaaaabibabbddbdbiaaaaaaa",
		"aaaaaaaaaaaaaibhaaaaaaiiidaaaaaa",
		"aaaaaaaaaaaaaaihpaaaaadhphaaaaaa",
		"aaaaaaaaaaaaaadiipaaaaahhiaaaaaa",
		"aaaaaaaaaaaabaabhipaaaihhdaaaaaa",
		"ahaaaaaaaaaidaaadihhiihiiaaaaaaa",
		"aaihaaaaaahidaaaadddiiibaaaaaaaa",
		"aaaihhphihiiaaaaaaabddaaaaaaaaaa",
		"aaaaaihididaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
}

const string& Log::GetLog()
{
	return this->log;
}

void Log::SetLog(string log)
{
	this->log = log;
}

//객체에서 전달된 문자열을 멤버 변수 log에 저장하고 출력
template<typename T>
void Log::PrintLog(string orderLog, const T& object)
{
	this->SetLog(orderLog);				//각 객체에서 SetLog를 직접 호출하기보단, PrintLog를 호출에서 Set과 출력이 동시에 이루어지도록 함

	/*if constexpr (is_same_v<T, Character>)	//참조 객체에 따라 Print 다르게 함
	{

	}
	else if constexpr (is_same_v<t, battlemanager>)
	{

	}*/
	cout << this->log;
}

//게임 시작 메뉴 출력
void Log::PrintStartMenu(int caseNumber)
{
	switch (caseNumber)
	{
	case LogEnum::Menu:
		cout << "게임 메뉴" << endl;
		cout << "1. 게임시작" << endl;
		cout << "2. 게임종료" << endl;
		break;
	case LogEnum::Start:
		cout << "게임이 시작됩니다." << endl;
	}
}

void Log::PrintInputError()
{
	cout << "잘못된 입력입니다. 다시 입력해 주세요." << endl;
}

void Log::PrintGameOver(int caseNumber)	//플레이어의 사망 경우와 게임의 종료에 대한 로그 출력
{
	switch (caseNumber)
	{
	case LogEnum::GameOver:
		cout << "사망하였습니다." << endl;
		cout << "새로운 게임을 시작하시겠습니까?" << endl;
		break;
	case LogEnum::GameEnd:
		cout << "게임을 종료합니다..." << endl;
		break;
	default:
		break;
	}
}

void Log::PrintBattle()
{

}

void Log::PrintStatus()
{

}

//이미지 Initialize 확인용 최종본에선 삭제 필요
void Log::TestPrint()
{
	int colorIndex = 0;
	vector<string> &data = treantData;
	for (int i = 0; i < data.size(); ++i)
	{
		for (int j = 0; j < IMAGE_SIDE_LENGTH; j++)	//IMAGE_SIDE_LENGTH 32
		{
			int colorIndex = this->CharToIndex(data[i][j]);		//알파벳을 인덱스로 변환
			if (colorIndex >= 0 && colorIndex <= NUMBER_OF_COLOR)	//NUMBER_OF_COLOR 16
			{
				SetConsoleTextAttribute(consoleHandle, colorIndex);	//색상에 해당하는 인덱스값을 넣어 콘솔 텍스트의 색상 변경
				cout << "■";	//각 색상에 맞는 도트 출력
			}
			
		}
		cout << "\n";	//줄 변경
	}
	SetConsoleTextAttribute(consoleHandle, 15);		//이미지 출력이 끝났으므로 다시 흰 색상(index:15)으로 변경
}