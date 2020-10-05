#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
#pragma warning(disable:4996)

int main()
{
	char input[100] = { 0 };	//Size input
	int LandValue = 0; //���� ��
	int X;	//���� X (����)
	int Y;	//���� Y (����)
	int i, j = 0;
	int **Map = NULL;	//Land
	int x = 0;	//Queue�� ��ǥ X
	int y = 0;	//Queue�� ��ǥ Y
	//�������Ϲ״밢���� ��ǥ�� ���� ���� �迭
	int dx[8] = { 0, 0, -1, 1 ,1 ,1,-1,-1 };
	int dy[8] = { 1, -1, 0, 0 ,1 ,-1,1,-1 };
	int OverLap = 0;

	queue<pair<int, int>> Queue;
	//���� Size�� �Է¹޴´�.
	cout << "Size of total lan X,Y: ";
	cin.getline(input, sizeof(input));
	Y = atoi(strtok(input, " "));	//����
	X = atoi(strtok(NULL, " "));	//����

	//���� Size�� �Է¹��� �� ����ó��
	while (1)
	{
		if (X == 0 || Y == 0) {
			cout << "Size�� ��Ȯ�� ���ڷ� �ٽ� �Է��ϼ��� X,Y: ";
			cin.getline(input, sizeof(input));
			X = atoi(strtok(input, " "));
			Y = atoi(strtok(NULL, " "));
		}
		else break;
	}

	//���� ũ�⸦ ����, �����Ҵ� �޴ºκ�
	Map = new int*[X];
	for (i = 0; i < X; i++)
	{
		Map[i] = new int[Y];
	}

	//���� ������ ���� �� ���� ���� ��ȣ�� ���� �� ����ó��
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			while (1) {
				cin >> Map[i][j];

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "��� �Է� �Ͻ� ���� -1�� 1���̿� ���ڷ� �ٽ� �Է��ϼ���." << endl;
					continue;
				}

				if (Map[i][j] >= -1 && Map[i][j] <= 1)break;

				if (Map[i][j] < -1 || Map[i][j] > 1) {
					cout << "��� �Է� �Ͻ� ���� -1�� 1���̿� ���ڷ� �ٽ� �Է��ϼ���." << endl;
					continue;
				}
			}
		}
	}

	//���� ���
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			cout << Map[i][j] << "\t";
		}
		cout << endl;
	}


	//���� ������ 1�� ��� �����ϸ鼭 1���� Queue�� ��ǥ�� ����
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			if (Map[i][j] == 1) Queue.push(make_pair(i, j));
		}
	}
	//Queue�� 1�� ���� ��ǥ�� �����ϴµ� 1���� ť�� ����ִٸ� ������ �ȵ� ���̹Ƿ� �ѱ����� ����.
	if (Queue.empty()) cout << "There are no Korean soldiers." << endl;
	//Queue�� 1�� ���� ��ǥ�� �����ϴµ� Queue Size�� ����� ũ��� ���ٸ� ��� 1�̹Ƿ� ������ ���� ����.
	else if (Queue.size() == X*Y) cout << "There is no land to occupy." << endl;
	
	//Queue�� ���� �ʾҴٸ� ����
	else {
		//Queue�� �� ���� while���� ����
		while (!Queue.empty()) {

			x = Queue.front().first;	//Queue front�� ����Ű�� ù��° �ڷ���
			y = Queue.front().second;	//Queue front�� ����Ű�� �ι�° �ڷ���
			Queue.pop(); //�ش� Queue front�� ����

			//�������� �� �밢���� �����ϱ⶧���� for���� 8�� ����
			for (int k = 0; k < 8; k++) {
				int nx = x + dx[k];
				int ny = y + dy[k]; //�������� �� �밢���� ��ǥ���� Ȯ��
				
				if (nx < 0 || nx > X - 1 || ny < 0 || ny > Y - 1) continue; //���̻� �� �� ���� Size�� ��� �ٽ� while���� ����
				//�������Ϲ״밢���� ��ǥ���� 0 �ϰ�� ����
				if (Map[nx][ny] == 0) {
					Queue.push(make_pair(nx, ny)); //�ش���ǥ�� Queue�� ����
					Map[nx][ny] = Map[x][y] + 1;   //�ش���ǥ�� �´�� �ִ� ��ǥ���� 1�� �����ش�.
				}
			}
			
		}
		for (i = 0; i < X; i++) {
			for (j = 0; j < Y; j++) {
				if (Map[i][j] == 0) OverLap++;
			}
		}
		//����ó��
		if (OverLap >= 1) {
			cout << "Because when soldiers are surrounded by empty land, they can not occupy the land of Japanese soldiers." << endl;
		}
		else {
			//�����־ �������� ���� ��� ����ó��
			if (Map[x][y] - 1 == 0) cout << "Because when soldiers are surrounded by empty land, they can not occupy the land of Japanese soldiers." << endl;
			//�ѱ����� ���� ���� �ϴµ����� �ɸ� Date���
			else cout << "The date when Korean soldiers occupied all the land of Japanese soldiers: " << Map[x][y] - 1 << endl;
		}
	}
	//2���� �迭�� �����Ҵ� �޾ұ� ������ �����Ҵ��� ����
	if (Map) {
		for (i = 0; i < X; i++) {
			delete[] Map[i];
			Map[i] = NULL;
		}
		delete[] Map;
	}
	return 0;
}