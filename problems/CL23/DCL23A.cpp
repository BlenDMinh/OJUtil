#include<bits/stdc++.h>
using namespace std;

const int MAX = 202000;
int phi[MAX + 1];

void calc_phi() {
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= MAX; i++)
        phi[i] = i - 1;
    for (int i = 2; i <= MAX; i++)
        for (int j = 2 * i; j <= MAX; j += i)
              phi[j] -= phi[i];
}

long long ff(int x, int y) {
    int ans = phi[x];
    int last = ans;
    for ( int i = 1; i < y; i++) {
        ans = 2 * phi[ans];
        if (ans == last) {
            break;
        }
        last = ans;
    }
    return ans;
}

long long fff(int x, int y) {
    return x + y;
}

int n;
// int x = gia_tri_x ;
// int y = gia_tri_y ;
// int z = bieu_thuc_z ;

string crop(string s, int l, int r) {
    return s.substr(l, r - l + 1);
}

int get_int(string s) {
    if(s[s.size() - 1] == ';') {
        s = crop(s, 8, s.size() - 2);
    } else {
        s = crop(s, 8, s.size() - 1);
    }
    return stoi(s);
}

int find_comma(string s) {
    int cnt = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') {
            cnt++;
        }
        if(s[i] == ')') {
            cnt--;
        }
        if(s[i] == ',' && cnt == 0) {
            return i;
        }
    }
    return -1;
}

long long process(string command, int x, int y) {
    while(command[0] == ' ') {
        command = crop(command, 1, command.size() - 1);
    }
    while(command[command.size() - 1] == ' ') {
        command = crop(command, 0, command.size() - 2);
    }
    if(command[0] == 'x') {
        return x;
    }
    if(command[0] == 'y') {
        return y;
    }
    // cout << command << " " << x << " " << y << endl;
    int c = 0;
    while(command[c] == 'f') {
        c++;
    }
    if(c == 3) {
        command = crop(command, c + 1, command.size() - 2);
        int m = find_comma(command);
        long long res_l = process(crop(command, 0, m - 1), x, y);
        long long res_r = process(crop(command, m + 1, command.size() - 1), x, y);
        return fff(res_l, res_r);
    } else if(c == 2) {
        command = crop(command, c + 1, command.size() - 2);
        int m = find_comma(command);
        long long res_l = process(crop(command, 0, m - 1), x, y);
        long long res_r = process(crop(command, m + 1, command.size() - 1), x, y);
        return ff(res_l, res_r);
    } else {
        command = crop(command, c + 1, command.size() - 2);
        long long res = process(command, x, y);
        return phi[res];
    }
}

int main() {
    calc_phi();
    string num;
    getline(cin, num);
    n = stoi(num);
    for(int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        int x = get_int(s);
        getline(cin, s);
        int y = get_int(s);
        getline(cin, s);
        if(s[s.size() - 1] == ';') {
            s = crop(s, 8, s.size() - 2);
        } else {
            s = crop(s, 8, s.size() - 1);
        }
        cout << process(s, x, y) << endl;
    }
}