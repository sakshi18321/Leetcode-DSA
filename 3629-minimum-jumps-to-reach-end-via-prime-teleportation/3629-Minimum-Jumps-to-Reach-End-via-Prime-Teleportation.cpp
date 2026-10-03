class Solution {
public:
    bool isPrime(int x) {
        if (x < 2) return false;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) return false;
        }
        return true;
    }

    int minJumps(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;

        unordered_map<int, vector<int>> mp;

        for (int i = 0; i < n; i++) {
            int x = nums[i];

            for (int p = 2; p * p <= x; p++) {
                if (x % p == 0) {
                    mp[p].push_back(i);

                    while (x % p == 0)
                        x /= p;
                }
            }

            if (x > 1)
                mp[x].push_back(i);
        }

        vector<int> dist(n, -1);
        queue<int> q;

        dist[0] = 0;
        q.push(0);

        unordered_set<int> usedPrime;

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            if (i == n - 1)
                return dist[i];

            // Adjacent jumps
            if (i + 1 < n && dist[i + 1] == -1) {
                dist[i + 1] = dist[i] + 1;
                q.push(i + 1);
            }

            if (i - 1 >= 0 && dist[i - 1] == -1) {
                dist[i - 1] = dist[i] + 1;
                q.push(i - 1);
            }

            // Prime teleportation
            int p = nums[i];

            if (isPrime(p) && !usedPrime.count(p)) {
                usedPrime.insert(p);

                for (int j : mp[p]) {
                    if (dist[j] == -1) {
                        dist[j] = dist[i] + 1;
                        q.push(j);
                    }
                }
            }
        }

        return -1;
    }
};