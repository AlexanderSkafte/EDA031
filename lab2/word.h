#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>

class Word {
public:
	/* Creates a word w with the sorted trigrams t */
	Word(const std::string& w, const std::vector<std::string>& t);
	
	/* Returns the word */
	std::string get_word() const { return w_; }

	/* Returns the trigrams */
	std::vector<std::string> get_trigrams() const { return t_; }

	/* Returns how many of the trigrams in t that are present
	 in this word's trigram vector */
	unsigned int get_matches(const std::vector<std::string>& t) const;

	/* Returns the unique trigrams for the std::string contained in Word */
	std::vector<std::string> unique_trigrams() const;

	/* static method */
	static std::vector<std::string> unique_trigrams(const std::string& word);

private:
	std::string w_;
	std::vector<std::string> t_;
};

#endif
