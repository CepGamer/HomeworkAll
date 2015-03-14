#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

#ifdef WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

long long max (long long a, long long b) {
    return a > b ? a : b;
}

long long min (long long a, long long b) {
    return a < b ? a : b;
}

//struct state {
//    state(string _1, string _2) {
//        x1 = _1[0];
//        y1 = _1[1];
//        x2 = _2[0];
//        y2 = _2[1];
//    }
//    state(string str) {
//        x1 = str[0];
//        y1 = str[1];
//        x2 = str[2];
//        y2 = str[3];
//    }
//    string toString() {
//        string toRet;
//        toRet.push_back(x1);
//        toRet.push_back(y1);
//        toRet.push_back(x2);
//        toRet.push_back(y2);
//    }
//    bool operator ==(state other) {
//        return (this->x1 == other.x1) && (this->x2 == other.x2) &&
//                (this->y1 == other.y1) && (this->y2 == other.y2);
//    }
//    static vector<state> moveState(state cur) {
//        state n(cur.toString());
//        vector<state> toRet;
//
//
//    }
//    char x1, y1, x2, y2;
//};

bool applicable(string str) {
    for(int i = 0; i < 4; i++)
        if((str[i] < 'a' || str[i] > 'h') && (str[i] < '1' || str[i] > '8'))
            return false;
    return !(str[0] == str[2] && str[1] == str[3]);
}

vector<string> moveState (string state) {
    char a = state[0], b = state[1], c = state[2], d = state[3];
    vector<string> toRet;
    string toAdd;

    toAdd = state;
    toAdd[0] += 1; toAdd[1] += 2;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[0] += 2; toAdd[1] += 1;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[0] += 1; toAdd[1] -= 2;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[0] += 2; toAdd[1] -= 1;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    /// 4
    toAdd = state;
    toAdd[0] -= 1; toAdd[1] += 2;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[0] -= 2; toAdd[1] += 1;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[0] -= 1; toAdd[1] -= 2;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[0] -= 2; toAdd[1] -= 1;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    /// 8

    toAdd = state;
    toAdd[2] += 1; toAdd[3] += 2;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[2] += 2; toAdd[3] += 1;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[2] += 1; toAdd[3] -= 2;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[2] += 2; toAdd[3] -= 1;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    /// 12
    toAdd = state;
    toAdd[2] -= 1; toAdd[3] += 2;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[2] -= 2; toAdd[3] += 1;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[2] -= 1; toAdd[3] -= 2;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    toAdd = state;
    toAdd[2] -= 2; toAdd[3] -= 1;
    if (applicable(toAdd)) toRet.push_back(toAdd);

    return toRet;
}

pair<int,string> len[8][8][8][8];
int n, m;

void bfs (string state, string fin) {
    queue<string> queq;
    int ln;
    len[state[0] - 'a'][state[1] - '1'][state[2] - 'a'][state[3] - '1'] = pair<int, string>(0, state);
    queq.push(state);
    do {
        vector<string> moves;
        state = queq.front();
        queq.pop();
        if(state == fin)
            break;
        ln = len[state[0] - 'a'][state[1] - '1'][state[2] - 'a'][state[3] - '1'].first;

        moves = moveState(state);
        for (auto move : moves) {
            if ((len[move[0] - 'a'][move[1] - '1'][move[2] - 'a'][move[3] - '1'].first == -1) ||
                    (len[move[0] - 'a'][move[1] - '1'][move[2] - 'a'][move[3] - '1'].first > (ln + 1))) {
                len[move[0] - 'a'][move[1] - '1'][move[2] - 'a'][move[3] - '1'] = pair<int, string>(ln + 1, state);
                queq.push(move);
            }
        }
    } while (queq.size() > 0);
}

vector<string> algo(string state, string finState) {
    vector<string> toRet;
    string temp;
    bfs(state, finState);
    temp = finState;
    while(temp != state) {
        string str = len[temp[0] - 'a'][temp[1] - '1'][temp[2] - 'a'][temp[3] - '1'].second;
        if (str[0] != temp[0] || str[1] != temp[1])
            toRet.push_back("1 " + temp.substr(0, 2));
        else
            toRet.push_back("2 " + temp.substr(2, 2));
        temp = str;
    }
    return toRet;
}

int main()
{
    FILE *in, *out;
    long long i, k, x, l, r;
    char c, d;
    string stateBeg, stateFin;
    in = fopen("knight2.in", "r");
    out = fopen("knight2.out", "w");
    fscanf(in, "%d %d", &n, &m);

    for (i = 0; i < 8; i++)
        for(k = 0; k < 8; k++)
            for(l = 0; l < 8; l++)
                for(r = 0; r < 8; r++)
                    len[i][k][l][r] = pair<int, string>(-1, "");

    for(i = 0; i < 2; i++) {
        fscanf(in, "%c%c\n", &c, &d);
        stateBeg.push_back(c);
        stateBeg.push_back(d);
    }

    for(i = 0; i < 2; i++) {
        fscanf(in, "%c%c\n", &c, &d);
        stateFin.push_back(c);
        stateFin.push_back(d);
    }

    auto rt = algo(stateBeg, stateFin);
    for(i = 0; i < rt.size(); i++) {
        fprintf(out, "%s\n", rt[rt.size() - i - 1].data());
    }

    fclose(in);
    fclose(out);
    return 0;
}
