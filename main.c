#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

#define MAX_LINE 256

int capacity = 5;
int items = 0;
HANDLE mutex;


// Função para importar data para os arrays + inicialização
void read_data() {

	system("cls");
	printf(" ***  Spotify da Wish  ***\n\n");

	//Inicializar todas as matrizes com 0, \0
	initialization();

	// Preencher matriz de utilizadores
	FILE* file_users = fopen("utilizadores.txt", "r");
	if (file_users == NULL) { printf(" Erro: Abrir ficheiro utilizador    - LEITURA\n"); }
	else {
		printf(" Sucesso: Abrir ficheiro utilizador - LEITURA\n");
		i = 0;
		while (fgets(line, sizeof(line), file_users)) {
			line[strcspn(line, "\n")] = '\0';
			switch (i % 4) {
			case 0: { sscanf(line, "%4d", &users[i / 4].id); break; }
			case 1: { strcpy(users[i / 4].name, line); break; }
			case 2: { strcpy(users[i / 4].email, line); break; }
			case 3: { strcpy(users[i / 4].password, line); break; }
			} i++;
		} fclose(file_users);
	}

	// Preencher matriz de conteudos
	FILE* file_contents = fopen("conteudos.txt", "r");
	if (file_contents == NULL) { printf(" Erro: Abrir ficheiro conteudo      - LEITURA\n"); }
	else {
		printf(" Sucesso: Abrir ficheiro conteudo   - LEITURA\n");
		i = 0;
		while (fgets(line, sizeof(line), file_contents)) {
			line[strcspn(line, "\n")] = '\0';
			switch (i % 5) {
			case 0: { sscanf(line, "%4d %4d %4d %4d", &contents[i / 5].id, &contents[i / 5].day, &contents[i / 5].month, &contents[i / 5].year);    break; }
			case 1: { strcpy(contents[i / 5].title, line); break; }
			case 2: { strcpy(contents[i / 5].type, line); break; }
			case 3: { strcpy(contents[i / 5].author, line); break; }
			case 4: { strcpy(contents[i / 5].genre, line); break; }
			} i++;
		} fclose(file_contents);
	}

	// Preencher matriz de playlists
	FILE* file_playlists = fopen("playlists.txt", "r");
	if (file_playlists == NULL) { printf(" Erro: Abrir ficheiro playlist      - LEITURA\n"); }
	else {
		printf(" Sucesso: Abrir ficheiro playlist   - LEITURA\n");
		i = 0;
		while (fgets(line, sizeof(line), file_playlists)) {
			line[strcspn(line, "\n")] = '\0';
			switch (i % 4) {
			case 0: { sscanf(line, "%4d %4d", &playlists[i / 4].id, &playlists[i / 4].id_owner); break; }
			case 1: { strcpy(playlists[i / 4].name, line); break; }
			case 2: { strcpy(playlists[i / 4].type, line); break; }
			case 3: {
				char* ptr = line; // Apontador que aponta o array line
				for (j = 0; j < LIM; j++) {
					sscanf(ptr, "%4d", &playlists[i / 4].content_id[j]);
					ptr += 4; // mover o apontador 4 "chars" para a frente
				} break;
			}
			} i++;
		} fclose(file_playlists);
	}

	printf(" Inicializacao completa!\n\n");
	printf(" ********** ~o~ **********\n\n ");
	sleep(WAIT);
	system("cls");
}
/* -------------------------------------------- Guardar Informações ---------------------------------------------------*/

int main(int argc, char* argv[])
{
	mainErrorHandeling(argc, argv);

	system("cls");
	printf(" ***  Spotify da Wish  ***\n\n");

	FILE* file = fopen(filePath, "r");
	if (!file) {
		printf("Erro a abrir ficheiro: %s\n", filePath);
		return 1;
	}

	DWORD* threadIDWorker = (DWORD*)malloc(sizeof(DWORD) * nWorkers);
	DWORD threadIDMonitor;
	HANDLE* threadHWorker = (HANDLE*)malloc(sizeof(HANDLE) * nWorkers);
	HANDLE threadHMonitor;

	mutexRead = CreateMutex(NULL, FALSE, NULL);
	if (mutexRead == NULL) {
		printf("Create read mutex failed!\n");
		exit(1);
	}

	mutexWrite = CreateMutex(NULL, FALSE, NULL);
	if (mutexWrite == NULL) {
		printf("Create write mutex failed!\n");
		exit(1);
	};

	semaphoreRead = CreateSemaphore(NULL, maxOrders, maxOrders, NULL);
	if (semaphoreRead == NULL) {
		printf("Create read semaphore failed!\n");
		exit(1);
	};

	semaphoreWrite = CreateSemaphore(NULL, 0, maxOrders, NULL);
	if (semaphoreWrite == NULL) {
		printf("Create write semaphore failed!\n");
		exit(1);
	};

DWORD WINAPI producer(LPVOID T)
{
	int* threadID;
	threadID = (int*)T;
	while (1) {
		WaitForSingleObject(mutex, INFINITE);
		if (items < capacity) {
			items++;
			printf("\n Stored Box: %d\t\t ThreadID: %d", items, threadID);
			ReleaseMutex(mutex);
			Sleep(1000);
		}
		else {
			printf("\n Max capacity.\t\t ThreadID: %d", threadID);
			ReleaseMutex(mutex);
			Sleep(1000);
		}

	for (int i = 0; i < nWorkers; i++) {
		threadHWorker[i] = CreateThread(NULL, 0, worker, (LPVOID)list, 0, &threadIDWorker[i]);
		if (threadHWorker[i] == NULL) return 0;
	}

DWORD WINAPI consumer(LPVOID T)

	while (fscanf(file, "%d;%49[^;];%d;%f", &idTemp, nameTemp, &qtdTemp, &priceTemp) == 4)
	{
		Order* newOrder = (Order*)malloc(sizeof(Order));
		if (newOrder == NULL) {
			printf("Erro de memoria\n");
			break;
		}

int main(int argc, char* argv[])
{

	int i;

	DWORD threadIDConsumer[NCONS], threadIDProducer[NPROD];
	HANDLE threadHConsumer[NCONS], threadHProducer[NPROD];

		newOrder->next = list;
		list = newOrder;

	for (i = 0; i < NPROD; i++) {
		threadHProducer[i] = CreateThread(NULL, 0, producer, (LPVOID)i, 0, &threadIDProducer[i]);
		if (threadHProducer[i] == NULL) return 0;
	}
	for (i = 0; i < NCONS; i++) {
		threadHConsumer[i] = CreateThread(NULL, 0, consumer, (LPVOID)i, 0, &threadIDConsumer[i]);
		if (threadHConsumer[i] == NULL) return 0;
	}

	for (i = 0; i < NCONS; i++) {
		WaitForSingleObject(threadHConsumer[i], INFINITE);
	}

	for (i = 0; i < NPROD; i++) {
		WaitForSingleObject(threadHProducer[i], INFINITE);
	}

	for (i = 0; i < NCONS; i++) {
		CloseHandle(threadHConsumer[i]);
	}

	for (i = 0; i < NPROD; i++) {
		CloseHandle(threadHProducer[i]);
	}

	return 0;
}