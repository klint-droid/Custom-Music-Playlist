#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Song{
    char title[50];
    char artist[50];
    int duration;
    struct Song* next;
}Song;

Song *front = NULL;
Song *rear = NULL;

void displayPlaylist();
void addSong(char *title, char*artist, int duration);
void playNext();
void viewPlaylist();
int isEmpty();
int totalDuration();

int main(){
    int choice, songNumber;

    int duration[10] = {247, 200, 257, 431, 355, 390, 263, 215, 243, 240};
    char *titles[10] = {
        "Something Just Like This", "Blinding Lights", "Counting Stars", 
        "Hey Jude", "Bohemian Rhapsody", "Hotel California", 
        "Perfect", "Shallow", "Let It Be", "Shape of You"
    };
    char *artists[10] = {
        "The Chainsmokers & Coldplay", "The Weeknd", "OneRepublic", 
        "The Beatles", "Queen", "The Eagles", 
        "Ed Sheeran", "Lady Gaga & Bradley Cooper", "The Beatles", "Ed Sheeran"
    };

    printf("Welcome to the Music Playlist Manager!\n");
    displayPlaylist();

    do
    {
        printf("\nMenu\n");
        printf("1. Add Song to PlayList\n");
        printf("2. View Current Playlist\n");
        printf("3. Play Next Song\n");
        printf("4. View total duration of Playlist\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter song number to add (1-10): ");
                scanf("%d", &songNumber);
                if(songNumber < 1 || songNumber > 10){
                    printf("Invalid song number. Please choose between 1 and 10.\n");
                }
                else{
                    addSong(titles[songNumber - 1], artists[songNumber - 1], duration[songNumber - 1]);  
                }
                break;
            case 2:
                viewPlaylist();
                break;
            case 3:
                playNext();
                break;
            case 4:
                int total = totalDuration();
                printf("Total duration of playlist: %d sec\n", total);
                int min = total / 60;
                int sec = total % 60;
                printf("Which is approximately %d minutes and %d seconds.\n", min, sec);
                break;
            case 5:
                printf("Exiting the Music Playlist Manager. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (choice != 5);
    

    return 0;
}

void displayPlaylist(){
    printf("\n--- Initial Song Library ---\n");
    printf("[1] Something Just Like This (The Chainsmokers & Coldplay) - 247 sec\n");
    printf("[2] Blinding Lights (The Weeknd) - 200 sec\n");
    printf("[3] Counting Stars (OneRepublic) - 257 sec\n");
    printf("[4] Hey Jude (The Beatles) - 431 sec\n");
    printf("[5] Bohemian Rhapsody (Queen) - 355 sec\n");
    printf("[6] Hotel California (The Eagles) - 390 sec\n");
    printf("[7] Perfect (Ed Sheeran) - 263 sec\n");
    printf("[8] Shallow (Lady Gaga & Bradley Cooper) - 215 sec\n");
    printf("[9] Let It Be (The Beatles) - 243 sec\n");
    printf("[10] Shape of You (Ed Sheeran) - 240 sec\n");
    printf("-----------------------------\n");
}

void addSong(char *title, char *artist, int duration){
    Song* newsong = (Song*)malloc(sizeof(Song));
    strcpy(newsong->title,title);
    strcpy(newsong->artist,artist);
    newsong->duration = duration;
    newsong->next = NULL;

    if(rear == NULL){
        front = rear = newsong;
    }else{
        rear->next = newsong;
        rear = newsong;
    }
    printf("Song added: %s by %s\n", title, artist);
}

void playNext(){
    if(isEmpty()){
        printf("No songs avaialable in the playlist. Add some somgs first\n");
        return;
    }
    Song *temp = front;
    printf("Now playing: %s by %s\n", temp->title, temp->artist);
    printf("-> Dequeued and Played: %s (%s)\n.", temp->title, temp->artist);
    front = front->next;
    if(front == NULL){
        rear = NULL;
    }
    free(temp);
}

void viewPlaylist(){
    if(isEmpty()){
        printf("No songs available in the playlist. Add some songs first\n");
        return;
    }
    printf("\n--- Current Playlist (Next Up is Song 1)---\n");
    Song *temp = front;
    int count = 1;
    while(temp != NULL){
        printf("[%d] %s by %s - %d sec\n", count, temp->title, temp->artist, temp->duration);
        temp = temp->next;
        count++;
    }
    printf("------------------------\n");
}

int isEmpty(){
    return front == NULL;
}

int totalDuration(){
    int total = 0;
    Song *temp = front;
    while(temp != NULL){
        total += temp->duration;
        temp = temp->next;
    }
    return total;
}