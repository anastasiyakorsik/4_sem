#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

const int N = 3;

class MusicPlayer {
public: 
	MusicPlayer() {
		for (int i = 0; i < N; i++)
			music.push_back(new sf::Music);
	}

	~MusicPlayer() {
		for (int i = 0; i < N; i++)
			delete music[i];
	}

	std::vector <sf::Music*> music; 

	void SetMusic(const std::vector<std::string>& musicFiles) {
		for (int i = 0; i < N; i++)
			music[i]->openFromFile(musicFiles[i]);
	}

	void Play() {
		if (cur_song < N && (cur_song == 0 || music[cur_song - 1]->getStatus() == sf::Music::Stopped)) {
			std::cout << "New Song: " << music[cur_song]->getDuration().asSeconds() << "\n";
			music[cur_song]->play();
			cur_song++;
		}
	}
	int cur_song = 0;
};

int main()
{
	std::vector<std::string> files({"ringtone.ogg", "sound1.ogg", "s3.ogg" });

	MusicPlayer buffer;
	buffer.SetMusic(files);

	sf::RenderWindow window(sf::VideoMode(400, 400), "Sound");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		buffer.Play();

		window.display();
		window.clear();
	}
	
}