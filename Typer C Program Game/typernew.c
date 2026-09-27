#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

//Nama kelompok: Mamang racing
//Valent Steve Asman 2802411235
//Chandra Nafiadi Sovian 2802385741
//Delyanis Nazwa Ghiffarini 2802566445

int i, j, k, sentinel, retry, correctAnswers, leaderboardWPM, topWPM[5], question[10][15], backToMainMenu = 0, wpm;
float timeTaken, points, minutes, leaderboardScore, topScore[5];
char dump[30], putLeaderboard, topNickname[5][30], USERNAME[30];
clock_t startTime, endTime;

char answer[100][25];
char words[100][20] = 
{ //tiap baris berisi 10 kata
"mango", "apple", "banana", "pear", "grape", "lemon", "melon", "orange", "live", "story",
"make", "door", "then", "like", "some", "watch", "dream", "hope", "many", "down", 
"from", "city", "learn", "might", "should", "must", "have", "look", "face", "with", 
"fear", "right", "what", "name", "think", "quick", "high", "sign", "swim", "mean", 
"will", "more", "until", "stop", "bold", "smile", "help", "that", "soon", "both", 
"about", "alert", "array", "begin", "birth", "blame", "craft", "civil", "claim", "daily", 
"delay", "death", "equal", "error", "found", "forth", "guard", "grind", "guess", "haunt", 
"hide", "index", "inbox", "image", "jolly", "judge", "jiggy", "known", "knock", "limbo", 
"lucky", "music", "match", "nexus", "night", "other", "occur", "prize", "proxy", "queue", 
"quake", "roast", "razor", "stand", "spike", "trash", "trick", "umbra", "venom", "woken"
};
	
char hardWords[100][25] =
{ //tiap baris berisi 10 kata
"paraphrase", "artificial", "website", "digital", "developer", "environment", "sustainability", "diagnosis", "description", "summary", 
"important", "courageous", "impossible", "beautiful", "adventure", "important", "different", "available", "yesterday", "familiar", 
"wonderful", "intensity", "general", "journey", "history", "problem", "contract", "activity", "friendly", "dangerous", 
"mysterious", "confidence", "potential", "discovery", "appropriate", "absolute", "dashboard", "supportive", "audience", "encourage", 
"prominent", "patience", "creative", "optimistic", "negative", "original", "official", "exclusive", "generous", "evidence", 
"abyssal", "badland", "caffeine", "backroom", "crescent", "dyspathy", "dazzling", "exotic", "enlargement", "franchise", 
"feminine", "geography", "giveaway", "highway", "hypnosis", "international", "injustice", "jewelry", "knockoff", "ketchup",  
"luminous", "luckily", "mayhem", "malevolent", "nothingness", "network", "operation", "overclock", "persistent", "pickaxe", 
"quantity", "quality", "redirect", "requirement", "scratch", "strength", "undercover", "utility", "variation", "vanquish", 
"wheelie", "wayback", "xylophone", "xerograph", "yesterday", "zoologist", "ferrymen", "mesmerized", "flabbergasted", "interstellar"
};


int login(){ //Masuk ke akun yang sudah ada
	FILE *filePengguna;
	int i;
	char ch;
	filePengguna = fopen ("datapemain.txt", "r");
	if (filePengguna == NULL){
		printf("Failed to load user data.\n");
		exit(1);
	}
	char usernameData[25], password[25], passwordData[25];
	int passwordSalah = 0, usernameSalah = 0, usernameTidakAda = 0;
	printf("\nLogin\n");
	inputUsername:
	printf("Username : ");
	scanf("%s", USERNAME); getchar();
	
	while (!feof(filePengguna)){ //Searching untuk username yang ada di datapemain.txt
		fscanf(filePengguna, "%s %s\n", usernameData, passwordData);
		if (strcmp(USERNAME, usernameData) == 0){
			usernameTidakAda = 0;
			inputPassword:
			i = 0;
			printf("Password : ");
			while (1) {
		        ch = getch();
		        if (ch == '\r') {
		            password[i] = '\0';
		            break;
		        } else if (ch == '\b' && i > 0) { 
		            printf("\b \b");
		            i--;
		        } else if (ch != '\b') {
		            password[i++] = ch;
		            printf("*");
		        }
	    	}

			if (strcmp(password, passwordData) == 0){
				fclose(filePengguna);
				return 1;
			}
			else {
				passwordSalah++;
				if (passwordSalah >= 5) break;
				printf("\n\nPassword is wrong\n\n", password);
				goto inputPassword;
			}
		}
		else {
			usernameTidakAda = 1;
		}
	}
	fclose(filePengguna);
	if (usernameTidakAda == 1){
		usernameSalah++;
		printf("\nUsername not found\n\n");
		if (usernameSalah >= 5) return 0;
		filePengguna = fopen ("datapemain.txt", "r");
		goto inputUsername;
	}
	return 0;
}
void signup(){ //Membuat akun baru
	FILE *filePengguna;
	char ch;
	int i;
	filePengguna = fopen ("datapemain.txt", "r");
	if (filePengguna == NULL){
		printf("Failed to load user data.\n");
		exit(1);
	}
	fclose(filePengguna);
	char password[25], konfirmasiPassword[25], email[40], usernameData[25], dump1[25], dump2[40];
	int panjangPassword;
	printf("\nSignup\n");
	
	inputUsername:
	filePengguna = fopen ("datapemain.txt", "r");
	printf("Username : ");
	scanf("%s", USERNAME); getchar();
	
	while (!feof(filePengguna)){  //Searching untuk mencari jika ada username yang sama di datapemain.txt
		fscanf(filePengguna, "%s %s %s\n", usernameData, dump1, dump2);
		if (strcmp(USERNAME, usernameData) == 0){
			printf("\nUsername is already taken\n\n");
			fclose(filePengguna);
			goto inputUsername;
		}
	}
	fclose(filePengguna);
	
	inputPassword:
	i = 0;
	printf("Password : ");
	while (1) {
        ch = getch();
        if (ch == '\r') {
	        password[i] = '\0';
	        break;
        } 
		else if (ch == '\b' && i > 0) { 
	        printf("\b \b");
		    i--;
		} 
		else if (ch != '\b') {
		    password[i++] = ch;
		    printf("*");
		    }
	}
	
	panjangPassword = strlen(password);
	if (panjangPassword < 6){
		printf("\n\nPassword must contain at least 6 character\n\n");
		goto inputPassword;
	}
	i = 0;
	printf("\nConfirm Password (re-enter password) : ");
	while (1) {
        ch = getch();
        if (ch == '\r') {
	        konfirmasiPassword[i] = '\0';
	        break;
        } 
		else if (ch == '\b' && i > 0) { 
	        printf("\b \b");
		    i--;
		} 
		else if (ch != '\b') {
		    konfirmasiPassword[i++] = ch;
		    printf("*");
		    }
	}
	
	if (strcmp(password, konfirmasiPassword) != 0) {
		printf("\n\nPassword doesn't match'\n\n");
		goto inputPassword;
	}
	
	filePengguna = fopen("datapemain.txt", "a");
	fprintf(filePengguna, "%s %s\n", USERNAME, password);
	
	fclose(filePengguna);
}
void leaderboard(char *leaderboardFile){ //Memuat leaderboard
	FILE *f1;
	f1 = fopen(leaderboardFile, "r");
	if (f1 == NULL){
		printf("Failed to Load Leaderboard\n");
		return;
	}
	int rank = 0;
	char nickname[30];
	float score;
	float wpm;
	printf("---------------------------------------------\n");
	printf("%-6s | %-15s | %-10s | %s\n", "Rank", "Nickname", "Points", "WPM");
	printf("-------+-----------------+------------+------\n");
	while (!feof(f1)){
		rank++;
		if (rank > 5){
			break;
		}
		printf("%-7d", rank);
		fscanf(f1, "%s %f %f", nickname, &score, &wpm);
		printf("| %-15s | %-10.3f | %.0f\n", nickname, score, wpm);
	}
	printf("---------------------------------------------\n");
	fclose(f1);
	retry2:
	printf("\n");
	printf("1. Return to Main Menu\n");
	printf("2. Return to Leaderboard\n");
	printf("Enter a Number : ");
	scanf("%d", &retry);
	switch(retry){
		case 1:
			printf("\n");
			backToMainMenu = 1;
			return;
		case 2:
			return;
		default:
			printf("Please Input a Valid Number\n");
			goto retry2;
	}
	
}
void leaderboardAdd(char *leaderboardNew) { //Menulis ulang isi leaderboard (update)
	FILE *f1;
	if (f1 == NULL){
		printf("Failed to Load Leaderboard\n");
		return;
	}
	f1 = fopen(leaderboardNew, "w");
	for (i = 0; i < 5; i++){
		fprintf(f1,"%s %.3f %d\n", topNickname[i], topScore[i], topWPM[i]);
	}
	fclose(f1);
	f1 = fopen(leaderboardNew, "r");
	int rank = 0;
	char nickname[30];
	float score;
	float wpm;
	printf("%-6s %-15s %-10s %s\n", "Rank", "Nickname", "Points", "WPM");
	while (!feof(f1)){
		rank++;
		if (rank > 5){
			break;
		}
		printf("%-7d", rank);
		fscanf(f1, "%s %f %f", nickname, &score, &wpm);
		printf("%-15s %-10.3f %.0f\n", nickname, score, wpm);
	}
	fclose(f1);
}
void swapScore(float *a, float *b){
	float temp = *a;
	*a = *b;
	*b = temp;
}
void swapWPM(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void swapNickname(int swap1, int swap2){
	char temp[50];
	strcpy(temp, topNickname[swap1]);
	strcpy(topNickname[swap1], topNickname[swap2]);
	strcpy(topNickname[swap2], temp);
}
void swapFloatPVP(float *a, float *b){
	float temp = *a;
	*a = *b;
	*b = temp;
}
void sort() { //Bubble sort secara descending
  	for (i = 0; i < 5 - 1; i++) { 
        for (j = 0; j < 5 - i - 1; j++) { 
            if (topScore[j] < topScore[j + 1]) {
                swapScore(&topScore[j], &topScore[j + 1]);
                swapWPM(&topWPM[j], &topWPM[j + 1]);
                swapNickname(j, j + 1);
            }
        }
    }
}
void classicMode(){
	int pointHigher = 1;
	retry:
	system("cls");
	printf("Classic Mode: Survive 5 Rounds!\n");
	printf("Press Enter to Start");
    while (getchar() != '\n'); // Tunggu sampai pengguna menekan Enter
    printf("\n");
    srand(time(NULL));
    clock_t startTime = clock();
    correctAnswers = 0;
    for (i = 0; i < 5; i++){ //Batasan i di sini untuk jumlah soal
    	for (j = 0; j < 10; j++){ //Batasan j di sini untuk jumlah kata yang bakal muncul di 1 soal
    	question[i][j] = rand() % 100;
    	printf("%s", words[question[i][j]]);
    	if (j != 9){
    		printf(" ");
		}
    	}
    	printf("\n");
    	for (j = 0; j < 10; j++){ //Sama kaya j di atas, ini untuk input jawaban sama cek jawaban
    		scanf("%s", &answer[j]);
    		if (strcmp(answer[j], words[question[i][j]]) == 0){
    			correctAnswers+=1;
			}
		}
		printf("\n");
	}
	clock_t endTime = clock();
	timeTaken = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	points = (correctAnswers * 20) - (timeTaken * 8);
	minutes = timeTaken / 60.000;
	wpm = correctAnswers / minutes;
	printf("Time taken : %.3f seconds\n", timeTaken);
	printf("Correct answers : %d\n", correctAnswers);
	if (points <= 0){
		printf("You failed! Retype accurately and be faster!\n");
	}
	else {
		printf("Your wpm: %d\n", wpm);
		printf("Points earned: %.3f\n", points);
		char *leaderboardFile = "classicleaderboard.txt";
		FILE *f1;
		f1 = fopen(leaderboardFile, "r");
		for (i = 0; i < 5; i++){
			fscanf(f1, "%s %f %d\n", dump, &leaderboardScore, &leaderboardWPM);
			if (strcmp(dump, USERNAME) == 0){
				if (points > leaderboardScore){
					pointHigher = 1;
					break;
				}
				else {
					pointHigher = 0;
					break;
				}
			}
		}
		if (i == 5) i--;
		fclose(f1);
		if (points > leaderboardScore && pointHigher == 1){
			printf("\nYour points are among the top player\n");
			printf("Do you want to input your points to the leaderboard (Y/N)? ");
			scanf(" %c", &putLeaderboard);
			if (putLeaderboard == 'Y' || putLeaderboard == 'y'){
				f1 = fopen(leaderboardFile, "r");
				strcpy(topNickname[i], USERNAME);
				topScore[i] = points;
				topWPM[i] = wpm;
				int oldIndex = i;
				i = 0;
				while (!feof(f1)){
					if(i == oldIndex) {
						i++;
						continue;
					}
					fscanf(f1, "%s %f %d", topNickname[i], &topScore[i], &topWPM[i]);
					i++;
				}
				fclose(f1);
				sort();
				printf("\n\nLeaderboard has been updated\n");
				leaderboardAdd(leaderboardFile);
			}
		}
	}
	retry2:
	printf("\n1. Play again\n");
	printf("0. Return to menu\n");
	printf("Enter a number: ");
	scanf("%d", &retry); getchar();
	switch (retry){
		case 1 :
			goto retry;
			break;
		case 0 :
			printf("\n");
			break;
		default :
			printf("\nPlease input a valid number\n\n");
			goto retry2;
	}
}
void blitzMode(){
	int pointHigher = 1;
	retry:
	system("cls");
	printf("Blitz Mode: Be the Fastest!\n");
	printf("Press Enter to Start");
    while (getchar() != '\n'); // Tunggu sampai pengguna menekan Enter
    printf("\n");
    srand(time(NULL));
    clock_t startTime = clock();
    correctAnswers = 0;
    for (i = 0; i < 1; i++){ //Batasan i di sini untuk jumlah soal
    	for (j = 0; j < 10; j++){ //Batasan j di sini untuk jumlah kata yang bakal muncul di 1 soal
    	question[i][j] = rand() % 100;
    	printf("%s", words[question[i][j]]);
    	if (j != 9){
    		printf(" ");
		}
    	}
    	printf("\n");
    	for (j = 0; j < 10; j++){ //Sama kaya j di atas, ini untuk input jawaban sama cek jawaban
    		scanf("%s", &answer[j]);
    		if (strcmp(answer[j], words[question[i][j]]) == 0){
    			correctAnswers+=1;
			}
		}
		printf("\n");
	}
	clock_t endTime = clock();
	timeTaken = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	points = (correctAnswers * 100) - (timeTaken * 40);
	minutes = timeTaken / 60.000;
	wpm = correctAnswers / minutes;
	printf("Time taken : %.3f seconds\n", timeTaken);
	printf("Correct answers : %d\n", correctAnswers);
	if (points <= 0){
		printf("You failed! Retype accurately and be faster!\n");
	}
	else {
		printf("Your wpm: %d\n", wpm);
		printf("Points earned: %.3f\n", points);
		char *leaderboardFile = "blitzleaderboard.txt";
		FILE *f1;
		f1 = fopen(leaderboardFile, "r");
		for (i = 0; i < 5; i++){
			fscanf(f1, "%s %f %d\n", dump, &leaderboardScore, &leaderboardWPM);
			if (strcmp(dump, USERNAME) == 0){
				if (points > leaderboardScore){
					pointHigher = 1;
					break;
				}
				else {
					pointHigher = 0;
					break;
				}
			}
		}
		if (i == 5) i--;
		fclose(f1);
		if (points > leaderboardScore && pointHigher == 1){
			printf("\nYour points are among the top player\n");
			printf("Do you want to input your points to the leaderboard (Y/N)? ");
			scanf(" %c", &putLeaderboard);
			if (putLeaderboard == 'Y' || putLeaderboard == 'y'){
				f1 = fopen(leaderboardFile, "r");
				strcpy(topNickname[i], USERNAME);
				topScore[i] = points;
				topWPM[i] = wpm;
				int oldIndex = i;
				i = 0;
				while (!feof(f1)){
					if(i == oldIndex) {
						i++;
						continue;
					}
					fscanf(f1, "%s %f %d", topNickname[i], &topScore[i], &topWPM[i]);
					i++;
				}
				fclose(f1);
				sort();
				printf("\n\nLeaderboard has been updated\n");
				leaderboardAdd(leaderboardFile);
			}
		}
	}
	retry2:
	printf("\n1. Play again\n");
	printf("0. Return to menu\n");
	printf("Enter a number: ");
	scanf("%d", &retry); getchar();
	switch (retry){
		case 1 :
			goto retry;
			break;
		case 0 :
			printf("\n");
			break;
		default :
			printf("\nPlease input a valid number\n\n");
			goto retry2;
	}
}
void hardMode(){
	int pointHigher = 1;
	retry:
	system("cls");
	printf("Hard Mode: Survive 5 Rounds!\n");
	printf("Press Enter to Start");
    while (getchar() != '\n'); // Tunggu sampai pengguna menekan Enter
    printf("\n");
    srand(time(NULL));
    clock_t startTime = clock();
    correctAnswers = 0;
    for (i = 0; i < 5; i++){ //Batasan i di sini untuk jumlah soal
    	for (j = 0; j < 10; j++){ //Batasan j di sini untuk jumlah kata yang bakal muncul di 1 soal
    	question[i][j] = rand() % 100;
    	printf("%s", hardWords[question[i][j]]);
    	if (j != 9){
    		printf(" ");
		}
    	}
    	printf("\n");
    	for (j = 0; j < 10; j++){ //Sama kaya j di atas, ini untuk input jawaban sama cek jawaban
    		scanf("%s", &answer[j]);
    		if (strcmp(answer[j], hardWords[question[i][j]]) == 0){
    			correctAnswers+=1;
			}
		}
		printf("\n");
	}
	clock_t endTime = clock();
	timeTaken = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	points = (correctAnswers * 20) - (timeTaken * 4);
	minutes = timeTaken / 60.000;
	wpm = correctAnswers / minutes;
	printf("Time taken : %.3f seconds\n", timeTaken);
	printf("Correct answers : %d\n", correctAnswers);
	if (points <= 0){
		printf("You failed! Retype accurately and be faster!\n");
	}
	else {
		printf("Your wpm: %d\n", wpm);
		printf("Points earned: %.3f\n", points);
		char *leaderboardFile = "hardleaderboard.txt";
		FILE *f1;
		f1 = fopen(leaderboardFile, "r");
		for (i = 0; i < 5; i++){
			fscanf(f1, "%s %f %d\n", dump, &leaderboardScore, &leaderboardWPM);
			if (strcmp(dump, USERNAME) == 0){
				if (points > leaderboardScore){
					pointHigher = 1;
					break;
				}
				else {
					pointHigher = 0;
					break;
				}
			}
		}
		if (i == 5) i--;
		fclose(f1);
		if (points > leaderboardScore && pointHigher == 1){
			printf("\nYour points are among the top player\n");
			printf("Do you want to input your points to the leaderboard (Y/N)? ");
			scanf(" %c", &putLeaderboard);
			if (putLeaderboard == 'Y' || putLeaderboard == 'y'){
				f1 = fopen(leaderboardFile, "r");
				strcpy(topNickname[i], USERNAME);
				topScore[i] = points;
				topWPM[i] = wpm;
				int oldIndex = i;
				i = 0;
				while (!feof(f1)){
					if(i == oldIndex) {
						i++;
						continue;
					}
					fscanf(f1, "%s %f %d", topNickname[i], &topScore[i], &topWPM[i]);
					i++;
				}
				fclose(f1);
				sort();
				printf("\n\nLeaderboard has been updated\n");
				leaderboardAdd(leaderboardFile);
			}
		}
	}
	retry2:
	printf("\n1. Play again\n");
	printf("0. Return to menu\n");
	printf("Enter a number: ");
	scanf("%d", &retry); getchar();
	switch (retry){
		case 1 :
			goto retry;
			break;
		case 0 :
			printf("\n");
			break;
		default :
			printf("\nPlease input a valid number\n\n");
			goto retry2;
	}
}
void infiniteMode(){
	retry:
	system("cls");
	printf("Infinite Mode: Test Your Endurance!\n");
	printf("Press (x) to Stop\n");
	printf("Press Enter to Start");
    while (getchar() != '\n'); // Tunggu sampai pengguna menekan Enter
    printf("\n");
    srand(time(NULL));
    clock_t startTime = clock();
    correctAnswers = 0;
    do {
    	sentinel = 0;
    	i = 0;
    	for (j = 0; j < 10; j++){ //Batasan j di sini untuk jumlah kata yang bakal muncul di 1 soal
    	question[i][j] = rand() % 100;
    	printf("%s", words[question[i][j]]);
    	if (j != 9){
    		printf(" ");
		}
    	}
    	printf("\n");
    	for (j = 0; j < 10; j++){ //Sama kaya j di atas, ini untuk input jawaban sama cek jawaban
    		scanf("%s", &answer[j]);
    		if (strcmp(answer[j], words[question[i][j]]) == 0){
    			correctAnswers+=1;
			}
			else if (strcmp(answer[j], "x") == 0) {
				sentinel = 1;
				break;
			}
		}
		i++;
		printf("\n");
	} while (sentinel != 1);
	clock_t endTime = clock();
	timeTaken = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	points = (correctAnswers * 10) - (timeTaken * 2);
	minutes = timeTaken / 60.000;
	wpm = correctAnswers / minutes;
	printf("Time taken : %.3lf seconds\n", timeTaken);
	printf("Correct answers : %d\n", correctAnswers);
	if (points <= 0){
		printf("You failed! Retype accurately and be faster!\n");
	}
	else {
		printf("Your wpm: %d\n", wpm);
		printf("Points earned: %.3lf\n", points);
	}
	retry2:
	printf("\n1. Play again\n");
	printf("0. Return to menu\n");
	printf("Enter a number: ");
	scanf("%d", &retry); getchar();
	switch (retry){
		case 1 :
			goto retry;
			break;
		case 0 :
			printf("\n");
			break;
		default :
			printf("\nPlease input a valid number\n\n");
			goto retry2;
	}
}
void customMode(){ 
	int amountOfRounds, amountOfWords, difficulty;
	retry:
	system("cls");
	printf("Custom Mode: Create Your Own Game!\n");
    srand(time(NULL));
    roundsQuestion :
    printf("How many rounds do you want (max 10 rounds) : ");
    scanf("%d", &amountOfRounds); getchar();
    if (amountOfRounds < 1 || amountOfRounds > 10){
    	printf("Please input only number between 1 and 10\n");
    	goto roundsQuestion;
	}
	wordsQuestion :
	printf("How many words do you want each round (max 15 words) : ");
	scanf("%d", &amountOfWords); getchar();
	if (amountOfWords < 1 || amountOfWords > 15){
		printf("Please input only number between 1 and 15\n");
		goto wordsQuestion;
	}
	difficultyMenu :
	printf("Choose a difficulty\n");
	printf("1. Normal\n");
	printf("2. Hard\n");
	printf("Enter a number : ");
	scanf("%d", &difficulty); getchar();
	switch (difficulty){
		case 1 :
			printf("\nCustom mode has been made\n", amountOfRounds);
			printf("Press Enter to Start");
		    while (getchar() != '\n'); // Tunggu sampai pengguna menekan Enter
		    printf("\n");
			startTime = clock();
    		correctAnswers = 0;
    		for (i = 0; i < amountOfRounds; i++){
    			for (j = 0; j < amountOfWords; j++){ //Batasan j di sini untuk jumlah kata yang bakal muncul di 1 soal
    			question[i][j] = rand() % 100;
    			printf("%s", words[question[i][j]]);
    			if (j != amountOfWords - 1){
    				printf(" ");
				}
    			}
    			printf("\n");
    			for (j = 0; j < amountOfWords; j++){ //Sama kaya j di atas, ini untuk input jawaban sama cek jawaban
    				scanf("%s", &answer[j]); getchar();
    				if (strcmp(answer[j], words[question[i][j]]) == 0){
    					correctAnswers+=1;
					}
				}
				printf("\n");
			}
			endTime = clock();
			timeTaken = (float)(endTime - startTime) / CLOCKS_PER_SEC;
			minutes = timeTaken / 60.000;
			wpm = correctAnswers / minutes;
			printf("Time taken : %.3lf seconds\n", timeTaken);
			printf("Correct answers : %d\n", correctAnswers);
			printf("Your wpm: %d\n", wpm);
			break;
			
		case 2 :
			printf("\nCustom mode has been made\n");
			printf("Press Enter to Start");
    		while (getchar() != '\n'); // Tunggu sampai pengguna menekan Enter
    		printf("\n");
			startTime = clock();
    		correctAnswers = 0;
    		for (i = 0; i < amountOfRounds; i++){ //Batasan i di sini untuk jumlah soal
    			for (j = 0; j < amountOfWords; j++){ //Batasan j di sini untuk jumlah kata yang bakal muncul di 1 soal
    			question[i][j] = rand() % 100;
    			printf("%s", hardWords[question[i][j]]);
    			if (j != amountOfWords - 1){
    				printf(" ");
				}
    			}
    			printf("\n");
    			for (j = 0; j < amountOfWords; j++){ //Sama kaya j di atas, ini untuk input jawaban sama cek jawaban
    				scanf("%s", &answer[j]); getchar();
    				if (strcmp(answer[j], hardWords[question[i][j]]) == 0){
    					correctAnswers+=1;
					}
				}
				printf("\n");
			}
			endTime = clock();
			timeTaken = (float)(endTime - startTime) / CLOCKS_PER_SEC;
			minutes = timeTaken / 60.000;
			wpm = correctAnswers / minutes;
			printf("Time taken : %.3lf seconds\n", timeTaken);
			printf("Correct answers : %d\n", correctAnswers);
			printf("Your wpm: %d\n", wpm);
			break;
			
		default :
			printf("Please input a valid number\n");
			goto difficultyMenu;
	}
	retry2:
	printf("\n1. Play again\n");
	printf("0. Return to menu\n");
	printf("Enter a number: ");
	scanf("%d", &retry); getchar();
	switch (retry){
		case 1 :
			goto retry;
			break;
		case 0 :
			printf("\n");
			break;
		default :
			printf("\nPlease input a valid number\n\n");
			goto retry2;
	}
}
void pvpMode(){
	int amountOfRounds, amountOfWords, difficulty, players;
	float timeTakenPVP[10], pointsPVP[10], minutesPVP[10], wpmPVP[10], correctAnswersPVP[10];
	clock_t startTimePVP[10], endTimePVP[10];
	retry:
	system("cls");
	printf("PvP Mode: Who's the Best?'\n");
    srand(time(NULL));
    playersQuestion :
    printf("Number of players (max 10 players) : ");
    scanf("%d", &players); getchar();
    if (players < 2 || players > 10){
    	printf("Please input only number between 2 and 10\n");
    	goto playersQuestion;
	}
	char playerName[10][11];
	for (i = 0; i < players; i++){
		printf("Player %d nickname (10 characters or less): ", i + 1);
		scanf("%s", &playerName[i]);
	}
    roundsQuestion :
    printf("How many rounds do you want (max 10 rounds) : ");
    scanf("%d", &amountOfRounds); getchar();
    if (amountOfRounds < 1 || amountOfRounds > 10){
    	printf("Please input only number between 1 and 10\n");
    	goto roundsQuestion;
	}
	wordsQuestion :
	printf("How many words do you want each round (max 15 words) : ");
	scanf("%d", &amountOfWords); getchar();
	if (amountOfWords < 1 || amountOfWords > 15){
		printf("Please input only number between 1 and 15\n");
		goto wordsQuestion;
	}
	difficultyMenu :
	printf("Choose a difficulty\n");
	printf("1. Normal\n");
	printf("2. Hard\n");
	printf("Enter a number : ");
	scanf("%d", &difficulty); getchar();
	switch (difficulty){
		case 1 :
			printf("\nPvP mode has been made\n");
			for (i = 0; i < players; i++){
				system("cls");
				printf("Player %d Turn (Press Enter to Start)", i + 1);
			    while (getchar() != '\n'); // Tunggu sampai pengguna menekan Enter
			    printf("\n");
				startTimePVP[i] = clock();
	    		correctAnswersPVP[i] = 0;
	    		for (j = 0; j < amountOfRounds; j++){ //Batasan i di sini untuk jumlah soal
	    			for (k = 0; k < amountOfWords; k++){ //Batasan j di sini untuk jumlah kata yang bakal muncul di 1 soal
	    			question[j][k] = rand() % 100;
	    			printf("%s", words[question[j][k]]);
	    			if (k != amountOfWords - 1){
	    				printf(" ");
					}
	    			}
	    			printf("\n");
	    			for (k = 0; k < amountOfWords; k++){ //Sama kaya j di atas, ini untuk input jawaban sama cek jawaban
	    				scanf("%s", &answer[k]);
	    				if (strcmp(answer[k], words[question[j][k]]) == 0){
	    					correctAnswersPVP[i]+=1;
						}
					}
					printf("\n");
				}
				endTimePVP[i] = clock();
				timeTakenPVP[i] = (float)(endTimePVP[i] - startTimePVP[i]) / CLOCKS_PER_SEC;
				pointsPVP[i] = (correctAnswersPVP[i] * 20) - (timeTakenPVP[i] * 8);
				minutesPVP[i] = timeTakenPVP[i] / 60.000;
				wpmPVP[i] = correctAnswersPVP[i] / minutesPVP[i];
				getchar();
			}
			system("cls");
			printf("Result\n");
			printf("------------------------------------------------------------------------\n");
			printf("%-4s | %-12s | %-10s | %-14s | %-13s | %-5s\n", "No", "Nickname", "Points", "Time(second)", "Correct Ans", "WPM");
			printf("------------------------------------------------------------------------\n");
			for (i = 0; i < players - 1; i++) { 
       			for (j = 0; j < players - i - 1; j++) { 
           			if (pointsPVP[j] < pointsPVP[j + 1]) {
                		char tempPVP[50];
						strcpy(tempPVP, playerName[j]);
						strcpy(playerName[j], playerName[j + 1]);
						strcpy(playerName[j + 1], tempPVP);
						swapFloatPVP(&pointsPVP[j], &pointsPVP[j + 1]);
						swapFloatPVP(&timeTakenPVP[j], &timeTakenPVP[j + 1]);
						swapFloatPVP(&correctAnswersPVP[j], &correctAnswersPVP[ j+ 1]);
    					swapFloatPVP(&wpmPVP[j], &wpmPVP[j + 1]);
            		}	
        		}
    		}
			for (i = 0; i < players; i++){
				printf("%-4d | %-12s | %-10.1f | %-14.3f | %-13.0f | %-5.0f\n", i + 1, playerName[i], pointsPVP[i], timeTakenPVP[i], correctAnswersPVP[i], wpmPVP[i]);
			}
			printf("------------------------------------------------------------------------\n");
			break;
			
		case 2 :
			printf("\nPvP mode has been made\n");
			for (i = 0; i < players; i++){
				system("cls");
				printf("Player %d Turn (Press Enter to Start)", i + 1);
			    while (getchar() != '\n'); // Tunggu sampai pengguna menekan Enter
			    printf("\n");
				startTimePVP[i] = clock();
	    		correctAnswersPVP[i] = 0;
	    		for (j = 0; j < amountOfRounds; j++){ //Batasan i di sini untuk jumlah soal
	    			for (k = 0; k < amountOfWords; k++){ //Batasan j di sini untuk jumlah kata yang bakal muncul di 1 soal
	    			question[j][k] = rand() % 100;
	    			printf("%s", hardWords[question[j][k]]);
	    			if (k != amountOfWords - 1){
	    				printf(" ");
					}
	    			}
	    			printf("\n");
	    			for (k = 0; k < amountOfWords; k++){ //Sama kaya j di atas, ini untuk input jawaban sama cek jawaban
	    				scanf("%s", &answer[k]);
	    				if (strcmp(answer[k], hardWords[question[j][k]]) == 0){
	    					correctAnswersPVP[i]+=1;
						}
					}
					printf("\n");
				}
				endTimePVP[i] = clock();
				timeTakenPVP[i] = (float)(endTimePVP[i] - startTimePVP[i]) / CLOCKS_PER_SEC;
				pointsPVP[i] = (correctAnswersPVP[i] * 20) - (timeTakenPVP[i] * 4);
				minutesPVP[i] = timeTakenPVP[i] / 60.000;
				wpmPVP[i] = correctAnswersPVP[i] / minutesPVP[i];
				getchar();
			}
			system("cls");
			printf("Result\n");
			printf("------------------------------------------------------------------------\n");
			printf("%-4s | %-12s | %-10s | %-14s | %-13s | %-5s\n", "No", "Nickname", "Points", "Time(second)", "Correct Ans", "WPM");
			printf("------------------------------------------------------------------------\n");
			for (i = 0; i < players - 1; i++) { 
       			for (j = 0; j < players - i - 1; j++) { 
           			if (pointsPVP[j] < pointsPVP[j + 1]) {
                		char tempPVP[50];
						strcpy(tempPVP, playerName[j]);
						strcpy(playerName[j], playerName[j + 1]);
						strcpy(playerName[j + 1], tempPVP);
						swapFloatPVP(&pointsPVP[j], &pointsPVP[j + 1]);
						swapFloatPVP(&timeTakenPVP[j], &timeTakenPVP[j + 1]);
						swapFloatPVP(&correctAnswersPVP[j], &correctAnswersPVP[ j+ 1]);
    					swapFloatPVP(&wpmPVP[j], &wpmPVP[j + 1]);
            		}	
        		}
    		}
			for (i = 0; i < players; i++){
				printf("%-4d | %-12s | %-10.3f | %-14.3f | %-13.0f | %-5.0f\n", i + 1, playerName[i], pointsPVP[i], timeTakenPVP[i], correctAnswersPVP[i], wpmPVP[i]);
			}
			printf("------------------------------------------------------------------------\n");
			break;
			
		default : 
			printf("\nPlease input a valid number!\n\n");
			goto difficultyMenu;
		}
	retry2:
	printf("\n1. Play again\n");
	printf("0. Return to menu\n");
	printf("Enter a number: ");
	scanf("%d", &retry); getchar();
	switch (retry){
		case 1 :
			goto retry;
			break;
		case 0 :
			printf("\n");
			break;
		default :
			printf("\nPlease input a valid number\n\n");
			goto retry2;
	}
} 

int main() {
	int menu, leaderboardMenu, opsiMasuk, loginToken;
	
	printf("||============================================================||\n");
	printf("||   ========    \\\\    //    ||===\\\\    ||=====    ||===\\\\    ||\n");
	printf("||      ||        \\\\  //     ||    ))   ||         ||    ))   ||\n");
	printf("||      ||         \\||/      ||===//    ||=====    ||=\\\\//    ||\n");
	printf("||      ||          ||       ||         ||         ||  \\\\     ||\n");
	printf("||      ||          ||       ||         ||=====    ||   \\\\    ||\n");
	printf("||============================================================||\n");
	menuMasuk:
	printf("Pick an option\n");
	printf("1. Login\n");
	printf("2. Signup\n");
	printf("Enter a number : ");
	scanf("%d", &opsiMasuk);
	while (opsiMasuk < 1 || opsiMasuk > 2){
		printf("\nPlease enter a valid number\n");
		printf("Enter a number : ");
		scanf("%d", &opsiMasuk);
	}
	if (opsiMasuk == 1) {
		loginToken = login();
		if (loginToken == 1){
			printf("\n\nLogin successful\n\n");
		}
		else {
			printf("\n\nFailed to login, please Signup if you don't have an account'\n\n");
			goto menuMasuk;
		}
	}
	else {
		signup();
		loginToken = 1;
		printf("\n\nAccount has been made\n\n");
	}
	Sleep (750);
	
	mainMenu:
	system("cls");
	printf("1. Classic Mode\n");
	printf("2. Blitz Mode\n");
	printf("3. Hard Mode\n");
	printf("4. Infinite Mode\n"); 
	printf("5. Custom Mode\n");
	printf("6. Player vs Player\n");
	printf("7. Leaderboard\n");
	printf("0. Exit\n");
	printf("Enter a number: ");
	scanf("%d", &menu); getchar();
	switch (menu){
		case 1 :
			classicMode();
			goto mainMenu;
			break;
		case 2 :
			blitzMode();
			goto mainMenu;
			break;
		case 3 :
			hardMode();
			goto mainMenu;
			break;
		case 4 :
			infiniteMode();
			goto mainMenu;
			break;
		case 5 : 
			customMode();
			goto mainMenu;
			break;
		case 6 :
			pvpMode();
			goto mainMenu;
			break;
		case 7 :
			leaderboardSection:;
			char *leaderboardFile;
			system("cls");
			printf("Global Leaderboard\n");
			printf("1. Classic Mode\n");
			printf("2. Blitz Mode\n");
			printf("3. Hard Mode\n");
			printf("0. Return to Main Menu\n");
			printf("Enter a number : ");
			scanf("%d", &leaderboardMenu);
			printf("\n");
			switch(leaderboardMenu){
				case 1 :
					system("cls");
					printf("Classic Mode Leaderboard\n");
					leaderboardFile = "classicleaderboard.txt";
					leaderboard(leaderboardFile);
					if (backToMainMenu == 1) {
						backToMainMenu = 0;
						goto mainMenu;
					}
					goto leaderboardSection;
				case 2 :
					system("cls");
					printf("Blitz Mode Leaderboard\n");
					leaderboardFile = "blitzleaderboard.txt";
					leaderboard(leaderboardFile);
					if (backToMainMenu == 1) {
						backToMainMenu = 0;
						goto mainMenu;
					}
					goto leaderboardSection;
				case 3 :
					system("cls");
					printf("Hard Mode Leaderboard\n");
					leaderboardFile = "hardleaderboard.txt";
					leaderboard(leaderboardFile);
					if (backToMainMenu == 1) {
						backToMainMenu = 0;
						goto mainMenu;
					}
					goto leaderboardSection;
				case 0 :
					goto mainMenu;
				default :
					printf("\nPlease Input a Valid Number\n");
					goto leaderboardSection;
			}
			break;
		case 0 :
			printf("\nGame ended, Thanks for playing!\n");
			exit(0);
		default :
			printf("\nPlease input a valid number\n\n");
			goto mainMenu;
	}
	return 0;
}

