#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define BUFFER_SIZE 110

/*database file*/
char *db = "database";
/*Structure which holds all the information of a song*/
struct song
{
	char *song_title;
	char *artist_name;
	char *album_title;
	int release_year;
	char *genre;
	int length;
};

int count = 0; // to maintain number of songs/records in the memory

/*Declarations of all methods for operating on the database*/
void deallocate(struct song **);
struct song** load_database();
void save_database(struct song**);
struct song** add_song(struct song**);
void list_by_genre(struct song**, char *);
void list_by_album_artist(struct song**, char *, char *);
void list_by_artist(struct song**, char *);
void list_by_year(struct song**, int);


/* Main function which provides menu to user and calls other functions to operate on the database*/
int main()
{
	int choice, year;
	char artist[20], genre[20], album[20];
	/*Load the information from the database and assign to song structure pointer*/
	struct song **s = load_database();
	printf("\n\nSongs databse loaded successfully\n\n");
	while(1)
	{
		printf("1. Add a song to the Album\n");
		printf("2. Save the songs to the database\n");
		printf("3. list all songs by artist\n");
		printf("4. list all songs by Album & artist\n");
		printf("5. list all songs released by year\n");
		printf("6. list all songs by Genre\n");
		printf("7. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1: s = add_song(s);/*function call to add a song*/
				break;
			case 2: save_database(s);/*function call to save the database to a file*/
				break;
			case 3: printf("Enter artist name: ");
				scanf("%s", artist);
				list_by_artist(s, artist);/*list all the database songs by artist name provided by user*/
				break;
			case 4: printf("Enter album name: ");
				scanf("%s", album);
				printf("Enter artist name: ");
				scanf("%s", artist);
				list_by_album_artist(s, album, artist);/*list all the database songs by artist name and album title provided by user*/
				break;
			case 5: printf("Enter the year: ");
				scanf("%d", &year);
				list_by_year(s, year);/*list all the database songs by released year provided by user*/
				break;
			case 6: printf("Enter the genre: ");
				scanf("%s", genre);
				list_by_genre(s, genre);/*list all the database songs by genre name provided by user*/
				break;
			case 7: deallocate(s);/*deallocates the structure pointer and releases memory*/
				exit(0);
			default: printf("Invalid choice\n");
		}
	}
	return 0;
}
/*function used to release the memory when the program ends and whenever necessary*/
void deallocate(struct song **s)
{
	if(s != NULL)
	{
	int i = 0;
	/*loop through the whole addresses and frees the ememory*/
	for(; i<count; i++)
	{
		free(s[i]->song_title);
		free(s[i]->artist_name);
		free(s[i]->album_title);
		free(s[i]->genre);
		free(s[i]);
	}
	free(s);
	}
}

/*Save the whole songs from the main memory to the databse*/
void save_database(struct song **s)
{
	if(s != NULL)
	{
	FILE *fp = fopen(db,"w");
	char buffer[120];
	int i;
	for(i=0; i<count; i++)
	{
		sprintf(buffer, "%s,%s,%s,%d,%s,%d\n", s[i]->song_title, s[i]->artist_name, s[i]->album_title, s[i]->release_year, s[i]->genre, s[i]->length);
		fputs(buffer, fp);
	}
	fclose(fp);
	}
}

/*opens the database file and loads to main memory for all operations*/
struct song** load_database(){
	FILE *fp = fopen(db,"r");
	if(fp == NULL)
	{
		return NULL;
	}
	char c;
	char buf[BUFFER_SIZE];
	int i;
	for (c = getc(fp); c != EOF; c = getc(fp))
	{
		if (c == '\n')
			count = count + 1;
	}
	fclose(fp);
	/*Allocates memory based on the count of records in database*/	
	struct song **s = (struct song **)malloc(count * sizeof(struct song));
	for(i=0; i<count; i++)
	{
		s[i] = (struct song*)malloc(sizeof(struct song));
	}
	fp = fopen(db, "r");
	i=0;
    	while(i < count)
	{
		fgets(buf, BUFFER_SIZE, fp);
		s[i]->song_title = strdup(strtok(buf, ","));
		s[i]->artist_name = strdup(strtok(NULL, ","));
		s[i]->album_title = strdup(strtok(NULL, ","));
		char *r  = strtok(NULL, ",");
		s[i]->release_year = atoi(r);
		s[i]->genre = strdup(strtok(NULL, ","));
		char *t = strtok(NULL, ",");
		s[i]->length = atoi(t);
		//printf("%s   %s   %s   %d   %s   %d\n", s[i]->song_title, s[i]->artist_name, s[i]->album_title, s[i]->release_year, s[i]->genre, s[i]->length);
		i++;
	}
	fclose(fp);
	return s;
}

/*funcation to add a new song to database when issued option save will save the information to database file*/
struct song** add_song(struct song** s)
{
	char song[20], artist[20], album[20], genre[20];
	int year, length, i;
	printf("Enter song title: ");
	scanf("%s", song);
	printf("Enter artist name: ");
	scanf("%s", artist);
	printf("Enter album title: ");
	scanf("%s", album);
	printf("Enter release year: ");
	scanf("%d", &year);
	printf("Enter genre: ");
	scanf("%s", genre);
	printf("Enter length: ");
	scanf("%d", &length);
	
	struct song **temp = (struct song**)malloc((count+1) * sizeof(struct song));
	for(i=0; i<count+1; i++)
	{
               	temp[i] = (struct song*)malloc(sizeof(struct song));
        }
	for(i=0; i<count; i++)
	{
		temp[i]->song_title = strdup(s[i]->song_title);
	        temp[i]->artist_name = strdup(s[i]->artist_name);
                temp[i]->album_title = strdup(s[i]->album_title);
	        temp[i]->release_year = s[i]->release_year;
                temp[i]->genre = strdup(s[i]->genre);
	        temp[i]->length = s[i]->length;
        }
		temp[i]->song_title = strdup(song);
	        temp[i]->artist_name = strdup(artist);
                temp[i]->album_title = strdup(album);
	        temp[i]->release_year = year;
                temp[i]->genre = strdup(genre);
	        temp[i]->length = length;
		deallocate(s);
		count++;
	return temp;
}

/*Function to list all the songs by Genre*/
void list_by_genre(struct song** s, char *genre)
{
	if(s != NULL)
	{
		int i;
		printf("Genre:===> %s\n", genre);
		for(i=0; i<count; i++)
		{
			if(strncmp(s[i]->genre, genre, strlen(genre)) == 0)
				printf("\tSong Title   :   %s\n\tArtist Name   :   %s\n\tYear    :   %d\n\tAlbum Title   :   %s\n\tLength   :   %d\n\n", s[i]->song_title, s[i]->artist_name, s[i]->release_year, s[i]->album_title, s[i]->length);
		}
	}
}

/*function call to list all the songs by artist name and album title*/
void list_by_album_artist(struct song** s, char *album, char *artist)
{
	if(s != NULL)
	{
		int i;
		printf("Artist Name:===> %s\tAlbum Title:===> %s\n", artist, album);
		for(i=0; i<count; i++)
		{
			if((strncmp(s[i]->artist_name, artist, strlen(artist)) == 0) && (strncmp(s[i]->album_title, album, strlen(album)) == 0))
				printf("\tSong Title   :   %s\n\tYear    :   %d\n\tGenre   :   %s\n\tLength   :   %d\n\n", s[i]->song_title, s[i]->release_year, s[i]->genre, s[i]->length);
		}
	}
}

/*function call to display all the songs by artist name*/
void list_by_artist(struct song** s, char *artist)
{
	if(s != NULL)
	{
		int i;
		printf("Artist Name:===> %s\n", artist);
		for(i=0; i<count; i++)
		{
			if(strncmp(s[i]->artist_name, artist, strlen(artist)) == 0)
				printf("\tSong Title   :   %s\n\tYear    :   %d\n\tAlbum Title   :   %s\n\tGenre   :   %s\n\tLength   :   %d\n\n", s[i]->song_title, s[i]->release_year, s[i]->album_title, s[i]->genre, s[i]->length);
		}
	}
}

/*function call to display all the songs by released year*/
void list_by_year(struct song** s, int year)
{
	if(s !=NULL)
	{
		int i;
		printf("Year:==> %d\n", year);
		for(i=0; i<count; i++)
		{
			if(s[i]->release_year == year)
				printf("\tSong Title   :   %s\n\tArtist Name   :   %s\n\tAlbum Title   :   %s\n\tGenre   :   %s\n\tLength   :   %d\n\n", s[i]->song_title, s[i]->artist_name, s[i]->album_title, s[i]->genre, s[i]->length);
		}
	}
}
