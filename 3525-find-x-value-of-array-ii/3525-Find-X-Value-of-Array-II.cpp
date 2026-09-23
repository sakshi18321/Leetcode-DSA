class Solution {
public:

    struct Node {
        int prod;
        array<int, 5> cnt;

        Node() {
            prod = 1;
            cnt.fill(0);
        }
    };

    int n, k;
    vector<Node> seg;

    Node mergeNode(const Node& A, const Node& B) {
        Node C;

        C.prod = (long long)A.prod * B.prod % k;

        // Prefixes completely inside A
        for (int r = 0; r < k; r++) {
            C.cnt[r] += A.cnt[r];
        }

        // Prefixes that contain all of A
        // and then take a prefix of B
        for (int r = 0; r < k; r++) {
            int rem = (long long)A.prod * r % k;
            C.cnt[rem] += B.cnt[r];
        }

        return C;
    }

    void build(int node, int l, int r,
               vector<int>& nums) {

        if (l == r) {
            int rem = nums[l] % k;

            seg[node].prod = rem;
            seg[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        seg[node] =
            mergeNode(seg[node * 2],
                      seg[node * 2 + 1]);
    }

    void update(int node, int l, int r,
                int idx, int val) {

        if (l == r) {
            seg[node] = Node();

            int rem = val % k;

            seg[node].prod = rem;
            seg[node].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid) {
            update(node * 2, l, mid, idx, val);
        }
        else {
            update(node * 2 + 1, mid + 1, r, idx, val);
        }

        seg[node] =
            mergeNode(seg[node * 2],
                      seg[node * 2 + 1]);
    }

    Node query(int node, int l, int r,
               int ql, int qr) {

        if (qr < l || r < ql) {
            return Node();
        }

        if (ql <= l && r <= qr) {
            return seg[node];
        }

        int mid = (l + r) / 2;

        if (qr <= mid) {
            return query(node * 2,
                         l, mid,
                         ql, qr);
        }

        if (ql > mid) {
            return query(node * 2 + 1,
                         mid + 1, r,
                         ql, qr);
        }

        Node left =
            query(node * 2,
                  l, mid,
                  ql, qr);

        Node right =
            query(node * 2 + 1,
                  mid + 1, r,
                  ql, qr);

        return mergeNode(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries) {

        this->k = k;
        this->n = nums.size();

        vector<int> ans;
        ans.reserve(queries.size());

        // Special case
        if (k == 1) {

            for (auto& q : queries) {

                int start = q[2];
                int x = q[3];

                // Every number % 1 == 0
                if (x == 0)
                    ans.push_back(n - start);
                else
                    ans.push_back(0);

                // Update doesn't matter for k = 1
            }

            return ans;
        }

        seg.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        for (auto& q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            nums[index] = value;

            update(1, 0, n - 1,
                   index, value);

            // Query nums[start ... n-1]
            Node res =
                query(1, 0, n - 1,
                      start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};