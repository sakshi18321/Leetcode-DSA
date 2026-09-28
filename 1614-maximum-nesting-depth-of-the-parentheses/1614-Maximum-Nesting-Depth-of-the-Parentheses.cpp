class Solution {
public:
    int maxDepth(string s) {
        int count = 0;
        int maxDepth = 0;

        for(int i = 0; i < s.length(); i++) {

            if(s[i] == '(') {
                count++;
            }
            else if(s[i] == ')') {
                count--;
            }

            if(count > maxDepth) {
                maxDepth = count;
            }
        }

        return maxDepth;
    }
};