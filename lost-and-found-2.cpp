#include <bits/stdc++.h>
using namespace std;
struct User {
    string username;
    string salt;
    string hash;
};

string generateSalt() {
    srand(time(0) ^ clock());
    return to_string(rand()) + "_" + to_string(rand());
}
string strongHash(const string& password, const string& salt) {
    const long long MOD = 1e9+7;
    const long long B1 = 91138233LL;
    const long long B2 = 97266353LL;

    long long h1 = 0, h2 = 0;
    string s = password + "#" + salt;

    for (int round = 0; round < 5000; round++) {
        for (char c : s) {
            h1 = (h1 * B1 + c + round) % MOD;
            h2 = (h2 * B2 + c + round * 7) % MOD;
        }
        h1 ^= (h2 << 1);
        h2 ^= (h1 >> 1);
    }
    return to_string(h1) + "_" + to_string(h2);
}

void signup(map<string, User>& users) {
    string u, p;
    cout << "Choose username: ";
    cin >> u;
    cout << "Choose password: ";
    cin >> p;

    string salt = generateSalt();
    string hash = strongHash(p, salt);

    users[u] = {u, salt, hash};
    cout << "Signup successful!\n";
}

bool login(map<string, User>& users) {
    string u, p;
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;

    if (!users.count(u)) return false;
    return strongHash(p, users[u].salt) == users[u].hash;
}
struct Item {
    string name, desc, category, location;
    set<string> tokens;
};

set<string> tokenize(string s) {
    for (char& c : s) {
        if (ispunct(c)) c = ' ';
        c = tolower(c);
    }
    stringstream ss(s);
    set<string> t;
    string w;
    while (ss >> w) t.insert(w);
    return t;
}

double jaccard(const set<string>& a, const set<string>& b) {
    if (a.empty() || b.empty()) return 0.0;
    int inter = 0;
    for (auto& x : a) if (b.count(x)) inter++;
    return (double)inter / (a.size() + b.size() - inter);
}

double similarity(Item& L, Item& F) {
    double s1 = jaccard(L.tokens, F.tokens);
    double s2 = (L.category == F.category) ? 1.0 : 0.0;
    double s3 = (L.location == F.location) ? 1.0 : 0.0;
    return 0.6 * s1 + 0.25 * s2 + 0.15 * s3;
}
vector<int> hungarian(const vector<vector<double>>& cost) {
    int n = cost.size(), m = cost[0].size();
    int N = max(n, m);

    vector<vector<double>> a(N, vector<double>(N, 1.0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            a[i][j] = cost[i][j];

    vector<double> u(N + 1), v(N + 1);
    vector<int> p(N + 1), way(N + 1);

    for (int i = 1; i <= N; i++) {
        p[0] = i;
        int j0 = 0;
        vector<double> minv(N + 1, 1e18);
        vector<bool> used(N + 1, false);

        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            double delta = 1e18;

            for (int j = 1; j <= N; j++) {
                if (!used[j]) {
                    double cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta) delta = minv[j], j1 = j;
                }
            }

            for (int j = 0; j <= N; j++) {
                if (used[j]) u[p[j]] += delta, v[j] -= delta;
                else minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    vector<int> match(n, -1);
    for (int j = 1; j <= N; j++)
        if (p[j] <= n && j <= m)
            match[p[j] - 1] = j - 1;

    return match;
}

int main() {
    map<string, User> users;

    cout << "1. Signup\n2. Login\nChoice: ";
    int ch;
    cin >> ch;
    if (ch == 1) signup(users);
    if (!login(users)) {
        cout << "Authentication failed.\n";
        return 0;
    }

    int n, m;
    cout << "\nNumber of LOST items: ";
    cin >> n;
    vector<Item> lost(n);
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "\nLost Item " << i + 1 << endl;
        getline(cin, lost[i].name);
        getline(cin, lost[i].desc);
        getline(cin, lost[i].category);
        getline(cin, lost[i].location);
        lost[i].tokens = tokenize(lost[i].desc);
    }

    cout << "\nNumber of FOUND items: ";
    cin >> m;
    vector<Item> found(m);
    cin.ignore();

    for (int i = 0; i < m; i++) {
        cout << "\nFound Item " << i + 1 << endl;
        getline(cin, found[i].name);
        getline(cin, found[i].desc);
        getline(cin, found[i].category);
        getline(cin, found[i].location);
        found[i].tokens = tokenize(found[i].desc);
    }

    vector<vector<double>> cost(n, vector<double>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cost[i][j] = 1.0 - similarity(lost[i], found[j]);

    vector<int> match = hungarian(cost);

    cout << "\n===== OPTIMAL LOST ↔ FOUND MATCHES =====\n";
    for (int i = 0; i < n; i++) {
        if (match[i] != -1) {
            cout << lost[i].name << "  <-->  "
                 << found[match[i]].name << "\n";
        }
    }
    return 0;
}
