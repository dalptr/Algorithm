class Solution {
public:
    static string minWindow(const string &s, const string &t) {
        vector<int> char_index[128];
        int char_count_in_t[128] = {0};
        for (char c: t) {
            ++char_count_in_t[c];
        }
        string unique_chars_in_t;
        for (char c = 'A'; c <= 'z'; ++c) {
            if (char_count_in_t[c] != 0) unique_chars_in_t += c;
        }
        int min_length = INT_MAX, start = 0;
        for (int i = 0, end = int(s.size()); i < end; ++i) {
            const char c = s[i];
            char_index[c].push_back(i);
            int farthest_index = INT_MAX;
            for (char p: unique_chars_in_t) {
                const int len = int(char_index[p].size());
                if (len < char_count_in_t[p]) goto skip;
                int first_appear_index = char_index[p][len - char_count_in_t[p]];
                if (i - first_appear_index >= min_length) goto skip;
                farthest_index = min(farthest_index, first_appear_index);
            }
            min_length = i - farthest_index + 1;
            start = farthest_index;
            skip:;
        }
        return min_length == INT_MAX ? "" : s.substr(start, min_length);
    }
};
