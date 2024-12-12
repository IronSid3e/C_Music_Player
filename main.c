#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void listMP3Files(const char *directory) {
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        printf("Could not open directory: %s\n", directory);
        return;
    }

    printf("Music List :\n");
    while ((entry = readdir(dp)) != NULL) {
        if (strstr(entry->d_name, ".mp3") != NULL) {
            printf("- %s\n", entry->d_name);
        }
    }

    closedir(dp);
}

void playMusic(const char *filename) {
    char command[256];
    snprintf(command, sizeof(command), "start .\\musics\\%s.mp3", filename);
    system(command);
}

int main() {
    char choice;
    char musicFile[256];
    char musicPATH[256];
    char musicName[256];

    while (1) {
        printf("\n----------Music Player---------\n");
        printf("\n1) Music List\n2) Add New Music\n3) Play Music\n4) Stop Music\nQ) Quit\nYour choice: ");
        scanf(" %c", &choice);

        if (choice == '1') {
            listMP3Files(".\\musics");
            
        } else if (choice == '2') {
            printf("Enter the PATH of the music you want to add: ");
            scanf(" %s", &musicPATH);
            printf("Enter the name of the music you want to add: ");
            scanf(" %s", &musicName);
            char destination[512];
            snprintf(destination, sizeof(destination), ".\\musics\\%s", musicName);
            if (rename(musicPATH, destination) == 0) {
                printf("Music added successfully to the musics folder.\n");
            } else {
                printf("Failed to add music to the musics folder.\n");
            }

        } else if (choice == '3') {
            printf("Enter the name of the music you want to play: ");
            scanf(" %s", &musicFile);
            playMusic(musicFile);
        } else if (choice == '4') {
            system("taskkill /f /im microsoft.media.player.exe");
        } else if (choice == 'Q' || choice == 'q') {
            printf("Exiting program...\n");
             break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
