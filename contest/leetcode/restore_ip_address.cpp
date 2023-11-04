class Solution {
public:
    static constexpr char DELIMITER = '.';
    static constexpr int MAX_OCTET_VALUE = 255;
    static constexpr int MAX_OCTET_SIZE = 3;
    static constexpr int OCTET_PER_IP = 4;

    static inline bool isValidOctet(const std::string &octet) {
        if (octet.size() > MAX_OCTET_SIZE) return false;
        if (octet.size() > 1 && octet[0] == '0') return false; // leading zero
        if (stoi(octet) > MAX_OCTET_VALUE) return false;
        return true;
    }

    static bool isValidIP(const std::string &ip) {
        int numberOfOctets = 0;
        std::string octet;
        for (char c: ip) {
            if (c == DELIMITER) {
                if (!isValidOctet(octet)) return false;
                ++numberOfOctets;
                octet.clear();
            } else {
                octet.push_back(c);
            }
        }
        if (!octet.empty()) {
            if (!isValidOctet(octet)) return false;
            ++numberOfOctets;
        }
        return numberOfOctets == OCTET_PER_IP;
    }

    static vector<string> restoreIpAddresses(const string &s) {
        const int n = (int) s.size(), dotSize = n - 1;
        if (n < 4 || n > 12) return {};
        bool dots[dotSize];
        fill_n(dots, dotSize, false);
        dots[dotSize - 1] = dots[dotSize - 2] = dots[dotSize - 3] = true;
        vector<string> answer;
        do {
            string ip;
            for (int i = 0; i < dotSize; ++i) {
                ip += s[i];
                if (dots[i]) ip += '.';
            }
            ip.push_back(s.back());
            if (isValidIP(ip)) answer.push_back(ip);
        } while (next_permutation(dots, dots + dotSize));
        return answer;
    }
};
