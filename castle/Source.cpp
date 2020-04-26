/*
ID: ruifanl1
TASK: castle
LANG: C++
*/

#include <fstream>

int M, N, squares[50][50], rooms[2500], numOfRooms = 0;
bool west[50][50], north[50][50], east[50][50], south[50][50];

void setWalls(int room, int x, int y) {
	if (room - 8 >= 0) {
		room -= 8;
		south[x][y] = true;
	}
	if (room - 4 >= 0) {
		room -= 4;
		east[x][y] = true;
	}
	if (room - 2 >= 0) {
		room -= 2;
		north[x][y] = true;
	}
	if (room - 1 >= 0) {
		room -= 1;
		west[x][y] = true;
	}
}

bool makeRoom(int x, int y, int roomNum) {
	if (squares[x][y] != 0) {
		return false;
	}
	squares[x][y] = roomNum;
	rooms[roomNum - 1]++;
	if (!north[x][y]) {
		makeRoom(x, y - 1, roomNum);
	}
	if (!east[x][y]) {
		makeRoom(x + 1, y, roomNum);
	}
	if (!south[x][y]) {
		makeRoom(x, y + 1, roomNum);
	}
	if (!west[x][y]) {
		makeRoom(x - 1, y, roomNum);
	}
	return true;
}

int main() {
	FILE* fin = fopen("castle.in", "r"), * fout = fopen("castle.out", "w");
	fscanf(fin, "%d %d\n", &M, &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			fscanf(fin, "%d", &squares[j][i]);
		}
	}
	fclose(fin);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			setWalls(squares[j][i], j, i);
			squares[j][i] = 0;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (makeRoom(j, i, numOfRooms + 1)) {
				numOfRooms++;
			}
		}
	}
	int largestRoom = 0;
	for (int i = 0; i < numOfRooms; i++) {
		if (largestRoom < rooms[i]) {
			largestRoom = rooms[i];
		}
	}

	fprintf(fout, "%d\n", numOfRooms);
	fprintf(fout, "%d\n", largestRoom);

	int x, y;
	char direction;
	for (int i = 0; i < M - 1; i++) {
		for (int j = N - 1; j >= 0; j--) {
			int room1 = squares[i][j] - 1;
			int room2 = squares[i][j - 1] - 1;
			if (room1 != room2) {
				int sum = rooms[room1] + rooms[room2];
				if (sum > largestRoom) {
					largestRoom = sum;
					x = i;
					y = j;
					direction = 'N';
				}
			}

			room2 = squares[i + 1][j] - 1;
			if (room1 != room2) {
				int sum = rooms[room1] + rooms[room2];
				if (sum > largestRoom) {
					largestRoom = sum;
					x = i;
					y = j;
					direction = 'E';
				}
			}
		}
	}
	for (int i = N - 1; i >= 0; i--) {
		int room1 = squares[M - 1][i] - 1;
		int room2 = squares[M - 1][i - 1] - 1;
		if (room1 != room2) {
			int sum = rooms[room1] + rooms[room2];
			if (sum > largestRoom) {
				largestRoom = sum;
				x = M - 1;
				y = i;
				direction = 'N';
			}
		}
	}
	for (int i = 0; i < M - 1; i++) {
		int room1 = squares[i][0] - 1;
		int room2 = squares[i + 1][0] - 1;
		if (room1 != room2) {
			int sum = rooms[room1] + rooms[room2];
			if (sum > largestRoom) {
				largestRoom = sum;
				x = i;
				y = 0;
				direction = 'E';
			}
		}
	}

	fprintf(fout, "%d\n", largestRoom);
	fprintf(fout, "%d %d %c\n", y + 1, x + 1, direction);
	fclose(fout);
}