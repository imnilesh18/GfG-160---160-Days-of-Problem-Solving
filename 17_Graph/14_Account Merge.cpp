/*
 * Account Merge
 *
 * Difficulty: HardAccuracy: 53.56%Submissions: 41K+Points: 8Average Time: 40m
 *
 * Given a list of accounts of size n where each element accounts [ i ] is a list of strings, where the first element account [ i ][ 0 ]  is a name, and the rest of the elements are emails representing emails of the account.
 * Geek wants you to merge these accounts. Two accounts belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts have the same name.
 * After merging the accounts, return the accounts in the following format: The first element of each account is the name, and the rest of the elements are emails in sorted order.
 *
 * Note: Accounts themselves can be returned in any order.
 *
 * Example 1:
 * Input:
 * n = 4
 * accounts [ ] =
 * [["John","johnsmith@mail.com","john_newyork@mail.com"],
 * ["John","johnsmith@mail.com","john00@mail.com"],
 * ["Mary","mary@mail.com"],
 * ["John","johnnybravo@mail.com"]]
 * Output:
 * [["John","john00@mail.com","john_newyork@mail.com", "johnsmith@mail.com"],
 * ["Mary","mary@mail.com"],
 * ["John","johnnybravo@mail.com"]]
 * Explanation:
 * The first and second John's are the same person as they have the common email "johnsmith@mail.com". The third John and Mary are different people as none of their email addresses are used by other accounts.We could return these arrays in any order, for example, the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
 *
 * Example 2:
 * Input:
 * n = 5
 * accounts [ ] =
 * [["Gabe","Gabe00@m.co","Gabe3@m.co","Gabe1@m.co"],
 * ["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],
 * ["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],
 * ["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],
 * ["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
 * Output:
 * [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],
 * ["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],
 * ["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],
 * ["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],
 * ["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]
 * Explanation:
 * We don't have any common emails in any of the users. We just sorted the emails of each person and we return a array of emails.(The details can be returned in any order).
 * Your Task:
 * You don't need to read or print anything. Your task is to complete the function accountsMerge() which takes a list of lists of strings representing accounts[][] as a parameter and returns a list of lists of strings denoting the details after merging.
 *
 * Expected Time Complexity: O(n*m*logn) - where n is the size of accounts and m is the size of the number of strings for a name.
 * Expected Auxiliary Space: O(n*m) - where n is the size of accounts and m is the size of the number of strings for a name.
 *
 * Constraints:
 * 1 <= n <= 1000
 * 2 <= accounts[ i ].size <= 10
 * 1 <= accounts[ i ][ j ].size <= 30
 * accounts[i][0] consists of English letters.
 */

/************************************************************ C++ ************************************************/

class DisjointSet {
    vector<int> parent, size;
public:
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    int findParent(int node) {
        if (node == parent[node]) {
            return node;
        }
        return parent[node] = findParent(parent[node]);
    }
    void unionBySize(int u, int v) {
        int par_u = findParent(u);
        int par_v = findParent(v);

        if (par_u == par_v) {
            return;
        }
        if (size[par_u] < size[par_v]) {
            parent[par_u] = par_v;
            size[par_v]  += size[par_u];
        } else {
            parent[par_v] = par_u;
            size[par_u]  += size[par_v];
        }
    }
};

class Solution {
public:
    vector<vector<string> > accountsMerge(vector<vector<string> >& accounts) {
        int         n = accounts.size();
        DisjointSet ds(n);
        unordered_map<string, int> emailToIndex;

        // Build union-find structure using common emails
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string email = accounts[i][j];
                if (emailToIndex.find(email) == emailToIndex.end()) {
                    emailToIndex[email] = i;
                } else {
                    ds.unionBySize(i, emailToIndex[email]);
                }
            }
        }

        // Group emails by their ultimate parent index
        vector<vector<string> > mergedEmails(n);
        for (auto& p : emailToIndex) {
            string email = p.first;
            int    node  = ds.findParent(p.second);
            mergedEmails[node].push_back(email);
        }

        // Construct the final merged accounts list,
        // sort the emails and attach the account name at index 0.
        vector<vector<string> > mergedAccounts;
        for (int i = 0; i < n; i++) {
            if (mergedEmails[i].empty()) {
                continue;
            }
            sort(mergedEmails[i].begin(), mergedEmails[i].end());
            vector<string> account;
            account.push_back(accounts[i][0]); // name
            for (auto& email : mergedEmails[i]) {
                account.push_back(email);
            }
            mergedAccounts.push_back(account);
        }
        return mergedAccounts;
    }
};

/************************************************************ JAVA ************************************************/

class Solution {
    // Helper class for union-find (disjoint set)
    static class DS {
        int[] parent;
        int[] size;

        DS(int n) {
            parent = new int[n];
            size   = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                size[i]   = 1;
            }
        }
        int findParent(int node) {
            if (parent[node] == node) {
                return node;
            }
            return parent[node] = findParent(parent[node]);
        }
        void unionBySize(int u, int v) {
            int parU = findParent(u);
            int parV = findParent(v);

            if (parU == parV) {
                return;
            }
            if (size[parU] < size[parV]) {
                parent[parU] = parV;
                size[parV]  += size[parU];
            } else {
                parent[parV] = parU;
                size[parU]  += size[parV];
            }
        }
    }

    static ArrayList<ArrayList<String> > accountsMerge(ArrayList<ArrayList<String> > accounts) {
        int n  = accounts.size();
        DS  ds = new DS(n);
        HashMap<String, Integer> emailToIndex = new HashMap<>();

        // Build union-find structure for accounts sharing common emails
        for (int i = 0; i < n; i++) {
            ArrayList<String> account = accounts.get(i);
            for (int j = 1; j < account.size(); j++) {
                String email = account.get(j);
                if (!emailToIndex.containsKey(email)) {
                    emailToIndex.put(email, i);
                } else {
                    ds.unionBySize(i, emailToIndex.get(email));
                }
            }
        }

        // Group emails belonging to the same component using a TreeSet to keep them sorted
        ArrayList<TreeSet<String> > mergedEmails = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            mergedEmails.add(new TreeSet<>());
        }
        for (Map.Entry<String, Integer> entry : emailToIndex.entrySet()) {
            String email = entry.getKey();
            int    node  = ds.findParent(entry.getValue());
            mergedEmails.get(node).add(email);
        }

        // Prepare the final result by adding the account name and the sorted emails
        ArrayList<ArrayList<String> > result = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (mergedEmails.get(i).isEmpty()) {
                continue;
            }
            ArrayList<String> mergedAccount = new ArrayList<>();
            // Add the account name as the first element
            mergedAccount.add(accounts.get(i).get(0));
            // Add all sorted emails from the TreeSet
            mergedAccount.addAll(mergedEmails.get(i));
            result.add(mergedAccount);
        }
        return result;
    }
}
