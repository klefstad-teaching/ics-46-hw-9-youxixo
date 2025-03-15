#include "ladder.h"

int main()
{
    set<string> words_list;
    load_words(words_list, "src/words.txt");

    cout << "Enter start word: ";
    string begin_word;
    cin >> begin_word;

    for(auto &ch : begin_word)
    {
        ch = tolower(ch);
    }

    cout << "Enter end word: ";
    string end_word;
    cin >> end_word;

    for(auto &ch : end_word)
    {
        ch = tolower(ch);
    }

    vector<string> ladder = generate_word_ladder(begin_word, end_word, words_list);

    if(ladder.empty())
    {
        cout <<"No ladder found from \" " << begin_word
            << "\" to \"" << end_word << "\":\n";
        print_word_ladder(ladder);
    }
    else
    {
        cout << "Shortest Ladder from \"" << begin_word 
            << "\" to \"" << end_word << "\":\n";
        print_word_ladder(ladder);
    }

    return 0;
}