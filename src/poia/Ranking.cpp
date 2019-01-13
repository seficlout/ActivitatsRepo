#include "Ranking.h"



void Ranking::LoadTextures(Renderer * myRenderer)
{
	//button textures
	myRenderer->LoadTextureText("SUNSPIRE", { "EXIT", "bEXIT_h", blue });
	myRenderer->LoadTextureText("SUNSPIRE", exitButton.text);

	//Background
	myRenderer->LoadTexture("RankingB", "../../res/img/apps.53029.9007199266525955.8c4385ac-fc48-4b5c-89e7-f1d71f13d5a4.jpg");//nombre y path
	loaded = true;
}

void Ranking::UpdateScores() 
{
	std::ofstream fSalida("../../res/ranking.bin", std::ios::out | std::ios::binary |std::ios::app);

	std::string info = nameWinerPlayer;
	std::cout <<info << std::endl;

	size_t len = info.size();

	fSalida.write(reinterpret_cast<char*>(&len), sizeof(size_t));
	fSalida.write(info.c_str(), info.size());


	fSalida.write(reinterpret_cast<char*>(&newMaxPuntuation), sizeof(newMaxPuntuation));

	
	fSalida.close();

}

void Ranking::LoadScores()
{
	std::ifstream fEntrada("../../res/ranking.bin", std::ios::in | std::ios::binary);
	std::string loadedName;
	int loadedScore;
	size_t len;
	if (fEntrada) {

		while (true) {

			fEntrada.read(reinterpret_cast<char*>(&len), sizeof(size_t));
			if (fEntrada.eof()) break;
			char* temp = new char[len + 1];
			fEntrada.read(temp, len);

			temp[len] = '\0';

			loadedName = temp;

			std::cout << loadedName;
			delete[] temp;

			fEntrada.read(reinterpret_cast<char*>(&loadedScore), sizeof(loadedScore));

			std::cout << loadedScore << std::endl;
			aRanking.push_back(std::make_pair(loadedScore, loadedName));
		}
		SortScores();
		fEntrada.close();
	}

	

}

bool Ranking::sortbysec(const std::pair<int, std::string> &a, const std::pair<int, std::string> &b)
{
	return (a.second < b.second);
}

void Ranking::SortScores() 
{
	int count = 0;
	std::sort(aRanking.begin(), aRanking.end());
	for (std::vector<std::pair<int, std::string>>::reverse_iterator it = aRanking.rbegin(); it != aRanking.rend(); it++)
	{
		// "first" and "second" are used to access 
		// 1st and 2nd element of pair respectively 
		std::cout << it->second << ":" << it->first << std::endl;
		if (count == 9) 
		{
			break;
		}
		count++;
	}
}



Ranking::Ranking()
{
	exitButton= Button({ "EXIT", "bEXIT", yellow }, { (SCREEN_WIDTH / 3) + 50, (SCREEN_HEIGHT / 5) + 400, buttonSize.x, buttonSize.y }, "bEXIT", "bEXIT_h");
	//newMaxPuntuation = -1;
}


Ranking::~Ranking()
{
}

void Ranking::Update(Controller * inputs)
{
	if (exitButton.collision(inputs->mousePos) && inputs->mouse) sceneName = MENU;
	/*if (loadedR == true) {
		UpdateScores();
		LoadScores();
	}
	loadedR = false;*/
}

void Ranking::Draw(Renderer * myRenderer)
{
	if (!loaded) LoadTextures(myRenderer);
	myRenderer->PushImage("RankingB", { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	myRenderer->PushImage(exitButton.buttonId, { exitButton.bRect.x ,  exitButton.bRect.y,  exitButton.bRect.w,  exitButton.bRect.h });

}