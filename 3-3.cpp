#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
#pragma warning(disable:4996)

int main()
{
	char input[100] = { 0 };	//Size input
	int LandValue = 0; //땅의 값
	int X;	//땅의 X (가로)
	int Y;	//땅의 Y (세로)
	int i, j = 0;
	int **Map = NULL;	//Land
	int x = 0;	//Queue의 좌표 X
	int y = 0;	//Queue의 좌표 Y
	//동서남북및대각선의 좌표를 보기 위한 배열
	int dx[8] = { 0, 0, -1, 1 ,1 ,1,-1,-1 };
	int dy[8] = { 1, -1, 0, 0 ,1 ,-1,1,-1 };
	int OverLap = 0;

	queue<pair<int, int>> Queue;
	//땅의 Size를 입력받는다.
	cout << "Size of total lan X,Y: ";
	cin.getline(input, sizeof(input));
	Y = atoi(strtok(input, " "));	//세로
	X = atoi(strtok(NULL, " "));	//가로

	//땅의 Size를 입력받을 때 예외처리
	while (1)
	{
		if (X == 0 || Y == 0) {
			cout << "Size를 정확한 숫자로 다시 입력하세요 X,Y: ";
			cin.getline(input, sizeof(input));
			X = atoi(strtok(input, " "));
			Y = atoi(strtok(NULL, " "));
		}
		else break;
	}

	//땅의 크기를 설정, 동적할당 받는부분
	Map = new int*[X];
	for (i = 0; i < X; i++)
	{
		Map[i] = new int[Y];
	}

	//땅의 소유와 가질 수 없는 땅의 번호를 설정 및 예외처리
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			while (1) {
				cin >> Map[i][j];

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "방금 입력 하신 열을 -1과 1사이에 숫자로 다시 입력하세요." << endl;
					continue;
				}

				if (Map[i][j] >= -1 && Map[i][j] <= 1)break;

				if (Map[i][j] < -1 || Map[i][j] > 1) {
					cout << "방금 입력 하신 열을 -1과 1사이에 숫자로 다시 입력하세요." << endl;
					continue;
				}
			}
		}
	}

	//땅을 출력
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			cout << Map[i][j] << "\t";
		}
		cout << endl;
	}


	//땅의 정보가 1일 경우 수행하면서 1값을 Queue에 좌표를 삽입
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			if (Map[i][j] == 1) Queue.push(make_pair(i, j));
		}
	}
	//Queue에 1인 값에 좌표를 삽입하는데 1값이 큐가 비어있다면 삽입이 안된 것이므로 한국땅이 없다.
	if (Queue.empty()) cout << "There are no Korean soldiers." << endl;
	//Queue에 1인 값에 좌표를 삽입하는데 Queue Size가 행렬의 크기와 같다면 모두 1이므로 점령할 땅이 없다.
	else if (Queue.size() == X*Y) cout << "There is no land to occupy." << endl;
	
	//Queue가 비지 않았다면 수행
	else {
		//Queue가 빌떄 까지 while문을 수행
		while (!Queue.empty()) {

			x = Queue.front().first;	//Queue front가 가리키는 첫번째 자료형
			y = Queue.front().second;	//Queue front가 가리키는 두번째 자료형
			Queue.pop(); //해당 Queue front를 삭제

			//동서남북 및 대각선을 봐야하기때문에 for문을 8번 진행
			for (int k = 0; k < 8; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k]; //동서남북 및 대각선의 좌표값을 확인
				
				if (nx < 0 || nx > X - 1 || ny < 0 || ny > Y - 1) continue; //더이상 갈 수 없는 Size일 경우 다시 while문을 수행
				//동서남북및대각선의 좌표값이 0 일경우 수행
				if (Map[nx][ny] == 0) {
					Queue.push(make_pair(nx, ny)); //해당좌표를 Queue에 삽입
					Map[nx][ny] = Map[x][y] + 1;   //해당좌표를 맞대고 있는 좌표값에 1을 더해준다.
				}
			}
			
		}
		for (i = 0; i < X; i++) {
			for (j = 0; j < Y; j++) {
				if (Map[i][j] == 0) OverLap++;
			}
		}
		//예외처리
		if (OverLap >= 1) {
			cout << "Because when soldiers are surrounded by empty land, they can not occupy the land of Japanese soldiers." << endl;
		}
		else {
			//막혀있어서 진행하지 못한 경우 예외처리
			if (Map[x][y] - 1 == 0) cout << "Because when soldiers are surrounded by empty land, they can not occupy the land of Japanese soldiers." << endl;
			//한국군이 땅을 점령 하는데까지 걸린 Date출력
			else cout << "The date when Korean soldiers occupied all the land of Japanese soldiers: " << Map[x][y] - 1 << endl;
		}
	}
	//2차원 배열을 동적할당 받았기 때문에 동적할당을 해제
	if (Map) {
		for (i = 0; i < X; i++) {
			delete[] Map[i];
			Map[i] = NULL;
		}
		delete[] Map;
	}
	return 0;
}