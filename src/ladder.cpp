#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg << " (word1: " << word1 
        << ", word2: " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    if(d ==1)
    {
        return is_adjacent(str1, str2);
    }
    return false;
}

bool is_adjacent(const string& word1, const string& word2)
{
    int len1 = (int)word1.size();
    int len2 = (int)word2.size();

    if(abs(len1 - len2) > 1)
    {
        return false;
    }

    if(len1 == len2)
    {
        int mismatch_count =0;
        for(int i=0; i<len1; i++)
        {
            if(word1[i]!= word2[i])
            {
                mismatch_count++;
                if(mismatch_count > 1)
                {
                    return false;
                }
            }
        }
        return (mismatch_count == 1);
    }

    const string &longer = (len1 > len2)? word1 : word2;
    const string &shorter = (len1 > len2)? word2 : word1;

    int i = 0, j = 0;
    bool found_difference = false;
    while(i < (int)longer.size() && j < (int)shorter.size())
    {
        if(longer[i] != shorter[j])
        {
            if(found_difference)
            {
                return false;
            }
            found_difference = true;
            i++;
        }
        else
        {
            i++;
            j++;
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, 
                                    const string& end_word, 
                                    const set<string>& word_list)
{
    if(begin_word == end_word)
    {
        return {};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty())
    {
        auto current_ladder = ladder_queue.front();
        ladder_queue.pop();

        const string &last_word = current_ladder.back();

        for(auto &w : word_list)
        {
            if(!visited.count(w) && is_adjacent(last_word, w))
            {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(w);

                if(w == end_word)
                {
                    return new_ladder;
                }

                visited.insert(w);
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, 
                const string& file_name)
{
    ifstream in(file_name);
    if(!in.is_open())
    {
        cerr << "Error: unable to open file " << file_name << endl;
        return;
    }

    string w;
    while(in >> w)
    {
        for(auto &ch : w)
        {
            ch = tolower(ch);
        }
        word_list.insert(w);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.empty())
    {
        cout << "No word ladder found." << endl;
        return;
    }
    for(int i =0; i < (int)ladder.size(); i++)
    {
        cout << ladder[i];
        if(i + 1 < (int)ladder.size())
        {
            cout << " -> ";
        }
    }
    cout << endl;
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");

    auto ladder1 = generate_word_ladder("cat", "dog", word_list);
    cout << "car -> dog ladder size: " << ladder1.size() << endl;

    auto ladder2 = generate_word_ladder("marty", "curls", word_list);
    cout << "marty -> curls ladder size: " << ladder2.size() << endl;

    auto ladder3 = generate_word_ladder("code", "data", word_list);
    cout << "code -> data ladder size: " << ladder3.size() << endl;

    auto ladder4 = generate_word_ladder("work", "play", word_list);
    cout << "work -> play ladder size: " << ladder4.size() << endl;

    auto ladder5 = generate_word_ladder("sleep", "awake", word_list);
    cout << "sleep -> awake ladder size: " << ladder5.size() << endl;

    auto ladder6 = generate_word_ladder("car", "cheat", word_list);
    cout << "car -> cheat ladder size: " << ladder6.size() << endl;
}