class Solution {
public:
    int calculate(string s) {
        long long result = 0;
        long long num = 0;
        int sign = 1;
        stack<int> st;

        for (int i = 0; i < s.size(); i++) {

            if (isdigit(s[i])) {
                num = 0;

                while (i < s.size() && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }

                i--;
                result += sign * num;
            }

            else if (s[i] == '+') {
                sign = 1;
            }

            else if (s[i] == '-') {
                sign = -1;
            }

            else if (s[i] == '(') {
                st.push(result);
                st.push(sign);

                result = 0;
                sign = 1;
            }

            else if (s[i] == ')') {
                int prevSign = st.top();
                st.pop();

                int prevResult = st.top();
                st.pop();

                result = prevResult + prevSign * result;
            }
        }

        return result;
    }
};