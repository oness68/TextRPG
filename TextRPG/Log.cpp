#include "Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

vector<string> Log::PNGImageToData(string filePath)
{
	vector<string> data;
	string line;
	const char alphabet[] = "abcdefghijklmnop";		//색상 순서대로 알파벳으로 전환됨
	// PNG 파일 로딩
	int width, height, channels;
	unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, 3); // RGB 형식으로만 읽기
	if (!image) {
		std::cerr << "이미지 읽어오기 실패" << std::endl;
		exit(1);
	}

	//이미지를 픽셀별로 문자로 변환
	for (int y = 0; y < height; y++)
	{
		line += "\"";
		for (int x = 0; x < width; x++)
		{
			int pixelIndex = (y * width + x) * 3;	//3채널 RGB
			int r = image[pixelIndex + 0];
			int g = image[pixelIndex + 1];
			int b = image[pixelIndex + 2];

			//픽셀의 RGB값과 가장 가까운 색상 인덱스 찾기
			int closestColor = GetClosestColorIndex(r, g, b);

			line += alphabet[closestColor];
		}
		data.push_back(line);
		line = "";
	}
	return data;
}

// RGB 색상과 팔레트 색상 간의 유클리드 거리 계산
int Log::GetClosestColorIndex(int r, int g, int b) {
	int closestIndex = 0;
	int minDistance = INT_MAX;

	for (int i = 0; i < NUMBER_OF_COLOR; i++) {
		int dr = r - palette[i][0];
		int dg = g - palette[i][1];
		int db = b - palette[i][2];
		int distance = dr * dr + dg * dg + db * db;

		if (distance < minDistance) {
			minDistance = distance;
			closestIndex = i;
		}
	}
	return closestIndex;
}

//void Log::ProcessPNG(string filePath)
//{
//	// PNG 파일 로딩
//	int width, height, channels;
//	unsigned char* image = stbi_load(filePath.c_str(), &width, &height, &channels, 3); // RGB 형식으로만 읽기
//	if (!image) {
//		std::cerr << "이미지 읽어오기 실패" << std::endl;
//		return;
//	}
//}

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

	this->playerData = PNGImageToData("images/Player.png");
	this->goblinData = PNGImageToData("images/Goblin.png");
	this->orcData = PNGImageToData("images/Orc.png");
	this->trollData = PNGImageToData("images/Troll.png");
	this->wolfData = PNGImageToData("images/Wolf.png");
	this->slimeData = PNGImageToData("images/Slime.png");
	this->goblinRiderData = PNGImageToData("images/GoblinRider.png");
	this->twinHeadTrollData = PNGImageToData("images/TwinHeadTroll.png");
	this->treantData = PNGImageToData("images/Treant.png");
	this->dragonData = PNGImageToData("images/Dragon.png");
}

const string& Log::GetLog()
{
	return this->log;
}

void Log::SetLog(string log)
{
	this->log = log;
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

//void Log::PrintBattle(BattleManager& object)
//{
//	string monsterName;
//}

void Log::PrintStatus()
{
	this->PrintImage(playerData);
}

void Log::PrintImage(vector<string>& data)
{
	int colorIndex = 0;
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