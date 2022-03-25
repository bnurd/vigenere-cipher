#include <iostream>

using namespace std;

class Crypt
{
public:
	Crypt(char *alphabet, char *cipher)
	{

		// inputs from client
		this->alphabet = alphabet;
		this->cipherWord = cipher;

		// prepare vigenere table
		generateVigenereTable();
	}

	Crypt()
	{

		// default values
		char tempAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		tempAlphabet[std::strlen(tempAlphabet)] = '\0';

		char *temp = tempAlphabet;
		this->alphabet = temp;

		generateVigenereTable();
	}

	char *encodeVigenere(char *text)
	{

		// cipher text to char array
		int count = 0;
		text[strlen(text)] = '\0';

		char cipherArray[100];
		for (int i = 0; i < strlen(text); i++)
		{
			cipherArray[i] = text[i];
		}

		cipherArray[strlen(text)] = '\0';

		while (count < strlen(text))
		{
			for (int j = 0; j < strlen(this->cipherWord); j++)
			{
				if (count >= strlen(text))
					break;
				cipherArray[count] = this->cipherWord[j];
				count++;
			}
		}

		char *encodedText = text;

		for (int i = 0; i < strlen(text); i++)
		{
			int cipherLetter = getIndex(text[i]) + 1; // line
			int textLetter = getIndex(cipherArray[i]);

			encodedText[i] = vigenere[cipherLetter][textLetter];
		}
		return encodedText;
	}

	char *decodeVigenere(char *encodedText)
	{

		// generate char array
		int count = 0;
		encodedText[strlen(encodedText)] = '\0';

		char cipherArray[100];
		for (int i = 0; i < strlen(encodedText); i++)
		{
			cipherArray[i] = encodedText[i];
		}

		cipherArray[strlen(encodedText)] = '\0';

		while (count < strlen(encodedText))
		{
			for (int j = 0; j < strlen(this->cipherWord); j++)
			{
				if (count >= strlen(encodedText))
					break;
				cipherArray[count] = this->cipherWord[j];
				count++;
			}
		}

		char *decodedText = encodedText;

		for (int i = 0; i < strlen(encodedText); i++)
		{
			int line = getIndex(cipherArray[i]);
			int column = 0;
			char letter;

			for (int j = 0; j < strlen(alphabet); j++)
			{
				if (vigenere[line][j] == encodedText[i])
				{
					column = j;
					letter = alphabet[j - 1];
					break;
				}
			}

			decodedText[i] = letter;
		}

		// line index encoded[i] decode alphabet index letter
		return decodedText;
	}

	void printTable()
	{
		for (int i = 0; i < strlen(alphabet); i++)
		{
			for (int j = 0; j < strlen(alphabet); j++)
			{
				cout << vigenere[i][j] << " ";
			}
			cout << endl;
		}
	}

private:
	char *alphabet;
	char *cipherWord;

	// vigenere table
	char vigenere[100][100];

	void generateVigenereTable()
	{
		vigenere[0][0] = '-';
		for (int i = 0; i < strlen(alphabet) + 1; i++)
		{
			for (int j = 0; j < strlen(alphabet) + 2; j++)
			{
				if (i == 0)
					vigenere[i][j + 1] = alphabet[j + i];
				else
					vigenere[i][j] = alphabet[j + i];
			}
			int letterIndex = 0;
			for (int k = strlen(alphabet) - i; k < strlen(alphabet); k++)
			{
				vigenere[i][k] = alphabet[letterIndex];
				letterIndex++;
			}
		}
	}

	int getIndex(char letter)
	{
		for (int i = 0; i < strlen(alphabet); i++)
		{
			if (letter == alphabet[i])
			{
				return i;
			}
		}
		return 0;
	}
};

int main()
{
	cout << "-- VIGENERE CIPHER --" << endl;

	// for table
	char alphabet[] = "ABCDEFGHIJKLMNOPRSTUVWXYZ";

	// key
	char key[] = "CIPHER";

	// text
	char text[] = "VIGENERE";

	// end of text
	text[strlen(text)] = '\0';

	// assign properties and generate vigenere table
	Crypt crypt(alphabet, key);

	cout << "Input Text : " << text << endl;
	cout << "Key : " << key << endl << endl;

	// encode
	char *encodedText = crypt.encodeVigenere(text);

	cout << "Encoded Text --- : " << encodedText << endl;
	cout << "Decoded Text --- : " << crypt.decodeVigenere(encodedText) << endl;

	cout << endl
		 << "------------- RESULT CHECK -------------" << endl;

	crypt.printTable();

	// wait process
	int a;
	cin >> a;
	return 0;
}
