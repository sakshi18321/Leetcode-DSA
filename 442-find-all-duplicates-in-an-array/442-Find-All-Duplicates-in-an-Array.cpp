class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {

        int n = nums.size();
        vector<int> dupl;

        for(int i = 0; i < n; i++) {

            int count = 0;

            for(int j = 0; j < n; j++) {
                if(nums[i] == nums[j]) {
                    count++;
                }
            }

            if(count > 1) {

                bool already = false;

                for(int k = 0; k < dupl.size(); k++) {
                    if(dupl[k] == nums[i]) {
                        already = true;
                        break;
                    }
                }

                if(!already) {
                    dupl.push_back(nums[i]);
                }
            }
        }

        return dupl;
    }
};