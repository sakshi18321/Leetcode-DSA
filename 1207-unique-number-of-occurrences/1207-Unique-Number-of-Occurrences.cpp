class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        vector<int> unique;

        for(int i = 0; i < arr.size(); i++){
            bool found = false;

            for(int j = 0; j < unique.size(); j++){
                if(arr[i] == unique[j]){
                    found = true;
                    break;
                }
            }
            if(!found) unique.push_back(arr[i]);
        }

        for(int i = 0; i < unique.size();i++){
            int c1 = 0;

            for(int k = 0; k < arr.size(); k++){
                if(arr[k] == unique[i]) c1++;
            }

            for(int j = i + 1; j < unique.size(); j++){
                int c2 = 0;

                for(int k = 0; k < arr.size(); k++){
                    if(arr[k] == unique[j]) c2++;
                }
                if (c1 == c2) return false;
            }
        }


        return true;
    }
};