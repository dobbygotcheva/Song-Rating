#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <Windows.h>

using namespace std;

class Song {
public:
    string title;
    string artist;
    int duration;
    int views;
    string filePath;
    int artistPopularity;

    Song(const string& title, const string& artist, int duration, int views, const string& filePath,int artistPopularity)
        : title(title), artist(artist), duration(duration), views(views), filePath(filePath), artistPopularity(artistPopularity) {}

    virtual void play() {
        cout << "Playing a song: " << title << " by " << artist << endl;
        PlaySound(TEXT(filePath.c_str()), NULL, SND_SYNC);
    }

    virtual double calculateRating() = 0; // Pure virtual function
};

class FavoriteSong : public Song {
public:
    FavoriteSong(const string& title, const string& artist, int duration, int views, const string& filePath,int artistPopularity, int likes)
        : Song(title, artist, duration, views, filePath, artistPopularity), likes(likes) {}

    void play() override {
        cout << "Playing favorite song: " << title << " by " << artist << endl;
        PlaySound(TEXT(filePath.c_str()), NULL, SND_SYNC);
    }

    double calculateRating() override {
    if (views > 0) {
        double likesRatio = static_cast<double>(likes) / views;
        double artistPopularityFactor = 0.0;

        // Determine artist popularity factor based on some criteria
        if (artistPopularity > 0 && artistPopularity <= 100) {
            artistPopularityFactor = 0.2;
        } else if (artistPopularity > 100 && artistPopularity <= 500) {
            artistPopularityFactor = 0.4;
        } else if (artistPopularity > 500 && artistPopularity <= 1000) {
            artistPopularityFactor = 0.6;
        } else if (artistPopularity > 1000) {
            artistPopularityFactor = 0.8;
        }

        // Calculate the overall rating
        double rating = likesRatio + artistPopularityFactor;

        return rating;
    } else {
        return 0.0; // No views, so the rating is 0.0
    }
}

private:
    int likes;
};

class HatedSong : public Song {
public:
    HatedSong(const string& title, const string& artist, int duration, int views, const string& filePath,int artistPopularity, int dislikes)
        : Song(title, artist, duration, views, filePath, artistPopularity), dislikes(dislikes) {}

    void play() override {
        cout << "Playing hated song: " << title << " by " << artist << endl;
        PlaySound(TEXT(filePath.c_str()), NULL, SND_SYNC);
    }

    double calculateRating() override {
    if (views > 0) {
        double rating = static_cast<double>(dislikes) / views;
        double artistPopularityFactor = 0.0; // Initialize with a default value

        // Calculate the artist popularity factor based on some criteria
        if (artistPopularity >= 80) {
            artistPopularityFactor = 1.2;
        } else if (artistPopularity >= 60) {
            artistPopularityFactor = 1.1;
        } else if (artistPopularity >= 40) {
            artistPopularityFactor = 1.05;
        } else {
            artistPopularityFactor = 1.0;
        }

        // Apply the artist popularity factor to the rating
        rating *= artistPopularityFactor;

        return rating;
    } else {
        return 0.0; // Return 0 if views are zero
    }
    }

private:
    int dislikes;
};

class HappyFavouriteSong : public FavoriteSong {
public:
    HappyFavouriteSong(const string& title, const string& artist, int duration, int views, const string& filePath, int artistPopularity, int likes)
        : FavoriteSong(title, artist, duration, views, filePath, artistPopularity, likes) {}

};

class SadFavourteSong : public FavoriteSong {
public:
    SadFavourteSong(const string& title, const string& artist, int duration, int views, const string& filePath, int artistPopularity, int likes)
        : FavoriteSong(title, artist, duration, views, filePath, artistPopularity, likes) {}

};

class TerribleHatedSong : public HatedSong {
public:
    TerribleHatedSong(const string& title, const string& artist, int duration, int views, const string& filePath, int artistPopularity, int dislikes)
        : HatedSong(title, artist, duration, views, filePath, artistPopularity, dislikes) {}

};

class NotSoBadHatedSong : public HatedSong {
public:
    NotSoBadHatedSong(const string& title, const string& artist, int duration, int views, const string& filePath, int artistPopularity, int dislikes)
        : HatedSong(title, artist, duration, views, filePath, artistPopularity, dislikes) {}

};

void insertionSort(vector<Song*>& songList) {
    int n = songList.size();
    for (int i = 1; i < n; ++i) {
        Song* key = songList[i];
        int j = i - 1;
        while (j >= 0 && songList[j]->views < key->views) {
            songList[j + 1] = songList[j];
            --j;
        }
        songList[j + 1] = key;
    }
}

int main() {
    vector<Song*> songList;

    // Create objects of various classes
    songList.push_back(new FavoriteSong("Klavier", "Rammstein", 240, 5000, "C:\\Users\\dobri\\OneDrive\\Desktop\\FDS\\mp\\Klavier.wav", 1300, 200000));
    songList.push_back(new FavoriteSong("Ich will", "Rammstein", 180, 3000, "C:\\Users\\dobri\\OneDrive\\Desktop\\FDS\\mp\\Rammstein-Ich-Will-_Official-Video_.wav", 1300, 300000));
    songList.push_back(new HatedSong("Geschlechtsverkehr", "Rammstein", 320, 10000, "C:\\Users\\dobri\\OneDrive\\Desktop\\FDS\\mp\\Rammstein-Sex-_Official-Lyric-Video_.wav", 12, 600));
    songList.push_back(new HappyFavouriteSong("Mein Land", "Rammstein", 180, 500, "C:\\Users\\dobri\\OneDrive\\Desktop\\FDS\\mp\\Mein Land.wav", 800, 5000));
    songList.push_back(new SadFavourteSong("Diamant", "Rammstein", 220, 1000, "C:\\Users\\dobri\\OneDrive\\Desktop\\FDS\\mp\\Diamant.wav", 600, 1500));
    songList.push_back(new TerribleHatedSong("Pussy", "Rammstein", 120, 200, "C:\\Users\\dobri\\OneDrive\\Desktop\\FDS\\mp\\Pussy.wav", 30, 3000));
    songList.push_back(new NotSoBadHatedSong("Du Hast", "Rammstein", 300, 3000, "C:\\Users\\dobri\\OneDrive\\Desktop\\FDS\\mp\\Du Hast.wav", 200, 1000));

    cout << "Song List:" << endl;
    for (const auto& song : songList) {
        cout << "Title: " << song->title << ", Artist: " << song->artist << ", Views: " << song->views << endl;
    }

    cout << endl;

    insertionSort(songList);

    cout << "Sorted Song List (by views):" << endl;
    for (const auto& song : songList) {
        cout << "Title: " << song->title << ", Artist: " << song->artist << " Rating: " << song->calculateRating() << ", Views: " << song->views << endl;
    }

    // Shuffle the song list
    srand(static_cast<unsigned int>(time(nullptr)));
    random_shuffle(songList.begin(), songList.end());

    // Play a random song
    if (!songList.empty()) {
        songList.front()->play();
    }

    // Cleanup
    for (const auto& song : songList) {
        delete song;
    }

    return 0;
}
