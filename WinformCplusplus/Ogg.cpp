#include <iostream>

class Ogg
{
public:
	Ogg();
	~Ogg();

	bool OpenFile(std::string file);


private:
	FILE* file = NULL;
};

Ogg::Ogg()
{
}

Ogg::~Ogg()
{
}

bool Ogg::OpenFile(std::string filename)
{
	file = fopen(filename.c_str(), "r+");
	if (file)
		return false;

	// On ouvre un flux ogg-vorbis à partir du fichier que l'on vient d'ouvrir
	int Error = ov_open(file, &Stream, NULL, 0);
	if (Error < 0)
		return false;

}