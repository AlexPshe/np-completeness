#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct ConvertILPToSat {
    vector< vector<int> > A;
    vector<int> b;
    int m;
    int n;

    ConvertILPToSat(int n, int m) : A(n, vector<int>(m)), b(n), m(m), n(n)
    {}

    void printEquisatisfiableSatFormula() {
        vector<vector<int>> answer;
        int flag = 0; // submission does not exist

        for (int i = 0; i < n; i++){
            vector<int> ind; // index of coordinats
            for (int j = 0; j < m; j++) {
                if (ind.size() == 3)
                    break;
                if (A[i][j] != 0) {
                    ind.push_back(j);
                }
            }

            // if all coeffs are zeroes
            if (ind.size() == 0 && b[i] < 0) {
                flag = 1;
                break;
            }

            if (ind.size() == 1){
                if (A[i][ind[0]] > b[i])
                    answer.push_back({ind[0], 1});
                if (0 > b[i])
                    answer.push_back({ind[0], 0});
            }

            if (ind.size() == 2){
                if(A[i][ind[0]] > b[i])
                    answer.push_back({ind[0], 1, ind[1], 0});
                if(A[i][ind[0]] + A[i][ind[1]] > b[i])
                    answer.push_back({ind[0], 1, ind[1], 1});
                if(A[i][ind[1]] > b[i])
                    answer.push_back({ind[0], 0, ind[1], 1});
                if(0 > b[i])
                    answer.push_back({ind[0], 0, ind[1], 0});
            }

            if (ind.size() == 3){
                if(A[i][ind[0]] > b[i])
                    answer.push_back({ind[0], 1, ind[1], 0, ind[2], 0});
                if(A[i][ind[1]] > b[i])
                    answer.push_back({ind[0], 0, ind[1], 1, ind[2], 0});
                if(A[i][ind[2]] > b[i])
                    answer.push_back({ind[0], 0, ind[1], 0, ind[2], 1});
                if(A[i][ind[0]] + A[i][ind[1]] > b[i])
                    answer.push_back({ind[0], 1, ind[1], 1, ind[2], 0});
                if(A[i][ind[1]] + A[i][ind[2]] > b[i])
                    answer.push_back({ind[0], 0, ind[1], 1, ind[2], 1});
                if(A[i][ind[0]] + A[i][ind[2]] > b[i])
                    answer.push_back({ind[0], 1, ind[1], 0, ind[2], 1});
                if(A[i][ind[0]] + A[i][ind[1]] + A[i][ind[2]] > b[i])
                    answer.push_back({ind[0], 1, ind[1], 1, ind[2], 1});
                if(0 > b[i])
                    answer.push_back({ind[0], 0, ind[1], 0, ind[2], 0});
            }

        }

        // submission does not exist
        if (flag){
            cout << "2 1"<< endl;
            cout << "1 0"<< endl;
            cout << "-1 0"<< endl;
            return;
        }

        // the size of submission is infinity
        if(answer.size() == 0){
            cout << "1 1" << endl;
            cout << "1 -1 0" << endl;
            return;
        }

        // combain cnf
        cout << answer.size() << ' ' << m << endl;
        for (int i = 0; i < answer.size(); i++){
            for (int j = 0; j < answer[i].size(); j=j+2) {
                string sym = "";
                if (answer[i][j + 1] == 1)
                    sym = "-";
                cout << sym << answer[i][j] + 1 << ' ';
            }
            cout << " 0" << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertILPToSat converter(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> converter.A[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> converter.b[i];
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
